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
	v::VectorGenerator pos_gen = v::VectorGenerator().with_stddev(glm::vec3(5.f, 5.f, 5.f));
	v::VectorGenerator size_gen = v::VectorGenerator(glm::vec3(0.05f, 0.05f, 0.05f)).with_stddev(glm::vec3(0.01f));
	v::VectorGenerator speed_gen = v::VectorGenerator().with_stddev(glm::vec3(1.f, 1.f, 1.f));
	float brightness = 0.05f;
	float color_var = 0.03f;
	v::VectorGenerator color_gen = v::VectorGenerator(glm::vec3(brightness, brightness, brightness*3)).with_stddev(glm::vec3(color_var*2, color_var, color_var));

	v::Creation creation = v::Creation(v::SphereSpecification(2), "main_spheres")
		.with_quantity(1000)
		.with_position(pos_gen)
		.with_size(size_gen)
		.with_velocity(speed_gen)
		.with_color(color_gen)
		.with_tag("background");

	visualizer->create_entities(creation);

	creation.with_shape(v::ShapeGenerator(v::CubeSpecification()));
	creation.with_group("main_cubes");

	visualizer->create_entities(creation);

	v::Query cube_query = v::Query().with_shape(v::ShapeType::CUBE);
	v::EntityReferences cubes = visualizer->query_entities(cube_query);

	v::GroupMovement cube_circle(v::Circle(glm::vec3(), 5.f));
	cube_circle.with_groups({"main_cubes"});
	v::Movement cube_drag(new v::SimpleDrag(0.2f));

	visualizer::Movement color_drag(new visualizer::SimpleColorDrag(0.1f));
	visualizer::Movement std_color(new visualizer::StdColor(0.04f));

	visualizer->add_group_movement(cube_circle);
	for (v::Movable* m : cubes)
	{
		m->add_movement(cube_drag);
		m->add_movement(color_drag);
		m->add_movement(std_color);
	}

	v::Query sphere_query = v::Query().with_shape(v::ShapeType::SPHERE);
	v::EntityReferences spheres = visualizer->query_entities(sphere_query);

	v::GroupMovement sphere_circle(v::Circle(glm::vec3(0.f, 1.f, 0.f), 3.f));
	sphere_circle.with_groups({"main_spheres"});
	v::Movement sphere_drag(new v::SimpleDrag(0.2f));

	visualizer->add_group_movement(sphere_circle);
	for (v::Movable* m : spheres)
	{
		m->add_movement(sphere_drag);
		m->add_movement(color_drag);
		m->add_movement(std_color);
	}

	v::Creation valence_arousal_debug_creation = v::Creation(v::SphereSpecification(2), "debug")
		.with_quantity(6)
		.with_size(glm::vec3(0.1f, 0.1f, 0.1f))
		.with_tag("va_debug");

	visualizer->create_entities(valence_arousal_debug_creation);
}

void play_song(const std::string& audio_path)
{
	std::string system_command = "cvlc " + audio_path + " --play-and-exit &>/dev/null &";
	system(system_command.c_str());
}

void AudioVisualizer::run(const InformationContainer& information_container)
{
	play_song("input.wav");

	std::optional<v::Visualizer> opt_visualizer = v::Visualizer::create(800, 600);
	if (!opt_visualizer)
	{
		std::cout << "ERROR: couldn't create visualizer" << std::endl;
	}
	v::Visualizer visualizer = *opt_visualizer;

	setup_handlers(&visualizer);
	setup_objects(&visualizer);

	while (!visualizer.should_close())
	{
		double current_time = visualizer.get_time();
		unsigned int frame_counter = static_cast<int>((current_time * 44100.0) / 1024.0);
		set_handler_frame_counter(frame_counter);

		EventList current_events = get_current_events(information_container.get_event_list(), current_time);

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
