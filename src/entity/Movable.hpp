#ifndef __MOVABLE_CLASS__
#define __MOVABLE_CLASS__

#include <vector>

#include "Entity.hpp"
#include "Accelerator.hpp"
#include "movement/Movement.hpp"
#include <visualizer/shape/shape_specification.hpp>

class Movable {
	public:
		Movable(const visualizer::Shape& shape);

		void tick(const double speed);
		void render(visualizer::ShaderProgram& shader_program) const;

		void add_movement(const Movement& movement);

		// Position
		void set_position(const glm::vec3& position);
		const glm::vec3& get_position() const;

		void update_velocity(const glm::vec3& velocity_update);
		void set_velocity(const glm::vec3& velocity);
		const glm::vec3& get_velocity() const;

		void update_acceleration(const glm::vec3& acceleration);
		void set_acceleration(const glm::vec3& acceleration);
		const glm::vec3& get_acceleration() const;

		// Size
		void set_size(const glm::vec3& size);
		void update_size(const glm::vec3& size);
		const glm::vec3& get_size() const;

		// Color
		void set_color(const glm::vec3& color);
		void update_color(const glm::vec3& color);
		const glm::vec3& get_color() const;

		void set_color_velocity(const glm::vec3& color_velocity);
		void update_color_velocity(const glm::vec3& color_velocity);
		const glm::vec3& get_color_velocity() const;

		void set_color_acceleration(const glm::vec3& color_acceleration);
		void update_color_acceleration(const glm::vec3& color_acceleration);
		const glm::vec3& get_color_acceleration() const;

		void set_tags(const std::vector<std::string>& tags);
		const std::vector<std::string>& get_tags() const;

		unsigned int get_id() const;

		visualizer::ShapeSpecification get_shape_specification() const;
	private:
		Entity _entity;
		Accelerator _position_accelerator;
		Accelerator _color_accelerator;
		std::vector<Movement> _movements;
		std::vector<std::string> _tags;
		unsigned int _id;
};

#endif
