#ifndef __ENTITY_CLASS__
#define __ENTITY_CLASS__

#include <glm/glm.hpp>

#include <visualizer/shape/shape.hpp>
#include <visualizer/shape/shape_specification.hpp>
#include <visualizer/shader_program.hpp>

class Entity {
	public:
		Entity(const visualizer::Shape& shape);

		void render(visualizer::ShaderProgram& shader_program) const;
		visualizer::Shape get_shape() const;
		const glm::vec3& get_position() const;

		void set_position(const glm::vec3& position);
		void update_position(const glm::vec3& velocity);

		void set_size(const glm::vec3& size);
		void update_size(const glm::vec3& size);
		const glm::vec3& get_size() const;

		void set_color(const glm::vec3& color);
		void update_color(const glm::vec3& color);
		const glm::vec3& get_color() const;

		visualizer::ShapeSpecification get_shape_specification() const;
	private:
		visualizer::Shape _shape;
		glm::vec3 _position;
		glm::vec3 _size;
		glm::vec3 _color;
};

#endif
