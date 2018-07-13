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

namespace v = visualizer;

void AudioVisualizer::init()
{
	v::Visualizer::init();
}

AudioVisualizer::AudioVisualizer()
	: _visualizer(*v::Visualizer::create(800, 600))
{}

EventList AudioVisualizer::generate_events()
{
	std::vector<EventSpecification> targets = {
		BeatEventSpecification("input.wav", 0.f)
	};
	_event_list_builder.with_targets(targets);

	return _event_list_builder.build();
}

void AudioVisualizer::setup_objects()
{
	v::VectorGenerator pos_gen = v::VectorGenerator().with_stddev(glm::vec3(5.f, 5.f, 5.f));
	v::VectorGenerator size_gen = v::VectorGenerator(glm::vec3(0.05f, 0.05f, 0.05f)).with_stddev(glm::vec3(0.01f));
	v::VectorGenerator speed_gen = v::VectorGenerator().with_stddev(glm::vec3(1.f, 1.f, 1.f));
	v::ShapeGenerator shape_gen = v::ShapeGenerator(v::SphereSpecification(2), 1.f).with_shape(v::CubeSpecification(), 1.f);

	v::Creation creation = v::Creation(shape_gen)
		.with_quantity(2000)
		.with_position(pos_gen)
		.with_size(size_gen)
		.with_velocity(speed_gen);

	_visualizer.create_entities(creation);

	v::Query cube_query = v::Query().with_shape(v::ShapeType::CUBE);
	v::EntityGroup cubes = _visualizer.get_entities().query_group(cube_query);

	v::Movement cube_circle(new v::Circle(glm::vec3(), 5.f));
	v::Movement cube_drag(new v::SimpleDrag(0.3f));
	v::Movement cube_random(new v::RandomAcceleration(0.08f, 60));

	for (v::Movable* m : cubes)
	{
		m->add_movement(cube_circle);
		m->add_movement(cube_drag);
		m->add_movement(cube_random);
	}

	v::Query sphere_query = v::Query().with_shape(v::ShapeType::SPHERE);
	v::EntityGroup spheres = _visualizer.get_entities().query_group(sphere_query);

	v::Movement sphere_circle(new v::Circle(glm::vec3(0.f, 1.f, 0.f), 3.f));
	v::Movement sphere_drag(new v::SimpleDrag(0.2f));
	v::Movement sphere_random(new v::RandomAcceleration(0.18f, 30));

	for (v::Movable* m : spheres)
	{
		m->add_movement(sphere_circle);
		m->add_movement(sphere_drag);
		m->add_movement(sphere_random);
	}
}

void AudioVisualizer::run()
{
	while (!_visualizer.should_close())
	{
		_visualizer.tick();
		_visualizer.render();
	}

	_visualizer.close();
}
