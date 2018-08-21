#include "AudioVisualizer.hpp"

#include <visualizer/entity/creation/Creation.hpp>
#include <visualizer/entity/EntityBuffer.hpp>
#include <visualizer/shape/ShapeHeap.hpp>
#include <visualizer/entity/queries/Query.hpp>
#include <visualizer/entity/Movable.hpp>
#include <visualizer/shape/ShapeType.hpp>
#include <visualizer/entity/movement/Circle.hpp>
#include <visualizer/entity/movement/RandomAcceleration.hpp>
#include <visualizer/entity/movement/SimpleDrag.hpp>
#include <visualizer/entity/movement/SimpleColorDrag.hpp>
#include <visualizer/entity/movement/StdColor.hpp>
#include <visualizer/entity/movement/RandomColor.hpp>

namespace v = visualizer;

void AudioVisualizer::init()
{
	v::Visualizer::init();
}

AudioVisualizer::AudioVisualizer()
	: _event_index(0)
{}

void AudioVisualizer::setup_objects(visualizer::Visualizer* visualizer)
{
	v::ShapeGenerator shape_gen(v::SphereSpecification(2), 1.f);
	shape_gen.with_shape(v::CubeSpecification(), 1.f);

	v::VectorGenerator pos_gen = v::VectorGenerator().with_stddev(glm::vec3(5.f, 0.5f, 5.f));
	v::VectorGenerator size_gen = v::VectorGenerator(glm::vec3(0.05f, 0.05f, 0.05f)).with_stddev(glm::vec3(0.01f));
	v::VectorGenerator speed_gen = v::VectorGenerator().with_stddev(glm::vec3(1.f, 1.f, 1.f));

	v::Creation creation = v::Creation(shape_gen, "main1")
		.with_quantity(1000)
		.with_position(pos_gen)
		.with_size(size_gen)
		.with_velocity(speed_gen);

	visualizer->create_entities(creation);

	creation.with_group("main2");
	visualizer->create_entities(creation);

	v::Creation valence_arousal_debug_creation = v::Creation(v::SphereSpecification(2), "debug")
		.with_quantity(6)
		.with_size(glm::vec3(0.1f, 0.1f, 0.1f))
		.with_color(glm::vec3(0.4, 0.4, 0.4))
		.with_tag("va_debug");

	visualizer->create_entities(valence_arousal_debug_creation);
}

void play_song(const std::string& audio_path)
{
	std::string system_command = "cvlc " + audio_path + " --play-and-exit &>/dev/null &";
	system(system_command.c_str());
}

void AudioVisualizer::run(const InformationContainer& information_container, const std::string& audio_filename)
{
	std::optional<v::Visualizer> opt_visualizer = v::Visualizer::create(800, 600, "AudioVisualizer - " + audio_filename);
	if (!opt_visualizer)
	{
		std::cout << "ERROR: couldn't create visualizer" << std::endl;
		return;
	}
	v::Visualizer visualizer = *opt_visualizer;

	setup_handlers(&visualizer);
	setup_objects(&visualizer);

	play_song(audio_filename);

	while (!visualizer.should_close())
	{
		double current_time = visualizer.get_time();
		unsigned int frame_counter = static_cast<int>((current_time * 44100.0) / 1024.0);
		set_handler_frame_counter(frame_counter);

		EventList current_events = get_current_events(information_container.get_event_list(), current_time);

		_compositor.update(&(visualizer.get_entities()), _handlers, information_container, current_events, frame_counter);

		handle_events(current_events, information_container.get_pool());

		visualizer.tick();
		visualizer.render();
	}

	system("pkill vlc");

	visualizer.close();
}

void AudioVisualizer::add_handlers(const HandlerList& handler_list)
{
	_handlers.insert(_handlers.end(), handler_list.cbegin(), handler_list.cend());
}

void AudioVisualizer::handle_events(const EventList& event_list, const essentia::Pool& pool)
{
	for (Handler& h: _handlers)
	{
		for (const Event& event : event_list)
		{
			std::visit([&event](auto& handler) { std::visit(handler, event.get_event()); }, h);
		}

		std::visit([&pool](auto& handler) { handler.update(pool); }, h);
	}
}

void AudioVisualizer::setup_handlers(visualizer::Visualizer* visualizer)
{
	for (Handler& h : _handlers)
		std::visit([&visualizer](auto& handler) { handler.set_visualizer(visualizer); }, h);
}

void AudioVisualizer::set_handler_frame_counter(unsigned int frame_counter)
{
	for (Handler& h : _handlers)
		std::visit([frame_counter](auto& handler) { handler.set_frame_counter(frame_counter); }, h);
}

EventList AudioVisualizer::get_current_events(const EventList& event_list, double current_time)
{
	EventList el;
	for (unsigned int i = _event_index; i < event_list.size(); i++)
	{
		if (event_list[i].get_time() < current_time)
		{
			el.push_back(event_list[i]);
			_event_index = i+1;
		} else break;
	}

	return el;
}
