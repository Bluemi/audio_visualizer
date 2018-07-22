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

EventList AudioVisualizer::generate_events()
{
	std::vector<EventSpecification> targets = {
		//TickEventSpecification(0.f),
		BeatEventSpecification()
	};
	EventListBuilder event_list_builder("input.wav");
	event_list_builder.with_targets(targets);

	return event_list_builder.build();
}

void AudioVisualizer::setup_objects(visualizer::Visualizer* visualizer)
{
	v::VectorGenerator pos_gen = v::VectorGenerator().with_stddev(glm::vec3(5.f, 5.f, 5.f));
	v::VectorGenerator size_gen = v::VectorGenerator(glm::vec3(0.05f, 0.05f, 0.05f)).with_stddev(glm::vec3(0.01f));
	v::VectorGenerator speed_gen = v::VectorGenerator().with_stddev(glm::vec3(1.f, 1.f, 1.f));
	float brightness = 0.05f;
	float color_var = 0.03f;
	v::VectorGenerator color_gen = v::VectorGenerator(glm::vec3(brightness, brightness, brightness*3)).with_stddev(glm::vec3(color_var*2, color_var, color_var));
	v::ShapeGenerator shape_gen = v::ShapeGenerator(v::SphereSpecification(2), 1.f).with_shape(v::CubeSpecification(), 1.f);

	v::Creation creation = v::Creation(shape_gen)
		.with_quantity(2000)
		.with_position(pos_gen)
		.with_size(size_gen)
		.with_velocity(speed_gen)
		.with_color(color_gen);

	visualizer->create_entities(creation);

	v::Query cube_query = v::Query().with_shape(v::ShapeType::CUBE);
	v::EntityGroup cubes = visualizer->get_entities().query_group(cube_query);

	v::Movement cube_circle(new v::Circle(glm::vec3(), 5.f));
	v::Movement cube_drag(new v::SimpleDrag(0.2f));

	visualizer::Movement color_drag(new visualizer::SimpleColorDrag(0.1f));
	visualizer::Movement std_color(new visualizer::StdColor(0.04f));

	for (v::Movable* m : cubes)
	{
		m->add_movement(cube_circle);
		m->add_movement(cube_drag);
		m->add_movement(color_drag);
		m->add_movement(std_color);
	}

	v::Query sphere_query = v::Query().with_shape(v::ShapeType::SPHERE);
	v::EntityGroup spheres = visualizer->get_entities().query_group(sphere_query);

	v::Movement sphere_circle(new v::Circle(glm::vec3(0.f, 1.f, 0.f), 3.f));
	v::Movement sphere_drag(new v::SimpleDrag(0.2f));

	for (v::Movable* m : spheres)
	{
		m->add_movement(sphere_circle);
		m->add_movement(sphere_drag);
		m->add_movement(color_drag);
		m->add_movement(std_color);
	}
}

void play_song(const std::string& audio_path)
{
	std::string system_command = "cvlc " + audio_path + " --play-and-exit &>/dev/null &";
	system(system_command.c_str());
}

void AudioVisualizer::run(const EventList& event_list)
{
	play_song("input.wav");

	std::optional<v::Visualizer> opt_visualizer = *v::Visualizer::create(800, 600);
	if (!opt_visualizer)
	{
		std::cout << "ERROR: couldn't create visualizer" << std::endl;
	}
	v::Visualizer visualizer = *opt_visualizer;

	setup_objects(&visualizer);

	float b = 0.02f;
	float v = 0.02f;
	visualizer::Movement sphere_random_color(new visualizer::RandomColor(visualizer::VectorGenerator(glm::vec3(b*3, -b, -b)).with_stddev(glm::vec3(v, v, v))));
	visualizer::Movement cube_random_color(new visualizer::RandomColor(visualizer::VectorGenerator(glm::vec3(b*3, b*3, -b)).with_stddev(glm::vec3(v, v, v))));

	while (!visualizer.should_close())
	{
		EventList current_events = get_current_events(event_list, visualizer.get_time());

		if (current_events.size())
		{
			v::Movement r_acc(new v::RandomAcceleration(.1f));
			for (auto it = visualizer.get_entities().begin(); it != visualizer.get_entities().end(); ++it)
			{
				(*it).add_movement(r_acc);
				if ((*it).get_shape_specification() == visualizer::ShapeType::CUBE)
				{
					(*it).add_movement(cube_random_color);
				} else {
					(*it).add_movement(sphere_random_color);
				}
			}
		}

		visualizer.tick();
		visualizer.render();
	}

	system("pkill vlc");

	visualizer.close();
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
