#include <iostream>

#include <visualizer/Visualizer.hpp>
#include <visualizer/entity/creation/Creation.hpp>
#include <visualizer/entity/creation/VectorGenerator.hpp>
#include <visualizer/entity/creation/ShapeGenerator.hpp>
#include <visualizer/entity/EntityBuffer.hpp>
#include <visualizer/shape/ShapeSpecification.hpp>
#include <visualizer/shape/ShapeHeap.hpp>
#include <visualizer/entity/queries/Query.hpp>
#include <visualizer/entity/Movable.hpp>
#include <visualizer/shape/ShapeType.hpp>
#include <visualizer/entity/movement/Circle.hpp>
#include <visualizer/entity/movement/RandomAcceleration.hpp>
#include <visualizer/entity/movement/SimpleDrag.hpp>

#include <glm/glm.hpp>

int main() {
	visualizer::Visualizer::init();
	visualizer::Visualizer visualizer = *visualizer::Visualizer::create(800, 600);
	visualizer.init();

	visualizer::VectorGenerator pos_gen = visualizer::VectorGenerator().with_stddev(glm::vec3(5.f, 5.f, 5.f));
	visualizer::VectorGenerator size_gen = visualizer::VectorGenerator(glm::vec3(0.05f, 0.05f, 0.05f)).with_stddev(glm::vec3(0.01f));
	visualizer::VectorGenerator speed_gen = visualizer::VectorGenerator().with_stddev(glm::vec3(1.f, 1.f, 1.f));
	visualizer::ShapeGenerator shape_gen = visualizer::ShapeGenerator(visualizer::SphereSpecification(2), 1.f).with_shape(visualizer::CubeSpecification(), 1.f);

	visualizer::Creation creation = visualizer::Creation(shape_gen)
		.with_quantity(2000)
		.with_position(pos_gen)
		.with_size(size_gen)
		.with_velocity(speed_gen);

	visualizer.create_entities(creation);

	visualizer::Query cube_query = visualizer::Query().with_shape(visualizer::ShapeType::CUBE);
	visualizer::EntityGroup cubes = visualizer.get_entities().query_group(cube_query);

	visualizer::Movement cube_circle(new visualizer::Circle(glm::vec3(), 5.f));
	visualizer::Movement cube_drag(new visualizer::SimpleDrag(0.3f));
	visualizer::Movement cube_random(new visualizer::RandomAcceleration(0.08f, 60));

	for (visualizer::Movable* m : cubes)
	{
		m->add_movement(cube_circle);
		m->add_movement(cube_drag);
		m->add_movement(cube_random);
	}

	visualizer::Query sphere_query = visualizer::Query().with_shape(visualizer::ShapeType::SPHERE);
	visualizer::EntityGroup spheres = visualizer.get_entities().query_group(sphere_query);

	visualizer::Movement sphere_circle(new visualizer::Circle(glm::vec3(0.f, 1.f, 0.f), 4.f));
	visualizer::Movement sphere_drag(new visualizer::SimpleDrag(0.3f));
	visualizer::Movement sphere_random(new visualizer::RandomAcceleration(0.08f, 60));

	for (visualizer::Movable* m : spheres)
	{
		m->add_movement(sphere_circle);
		m->add_movement(sphere_drag);
		m->add_movement(sphere_random);
	}

	while (!visualizer.should_close())
	{
		visualizer.tick();
		visualizer.render();
	}

	visualizer.close();
	return 0;
}
