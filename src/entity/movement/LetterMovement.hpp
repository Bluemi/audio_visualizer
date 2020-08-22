#ifndef __LETTER_MOVEMENT_CLASS__
#define __LETTER_MOVEMENT_CLASS__

#include <vector>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

class Movable;

class LetterMovement {
	public:
		LetterMovement(char letter, float scale);

		void apply_force(std::vector<Movable>& movables);
		void apply_force(Movable* movable);

		void set_position(const glm::vec3& position);
		void set_scale(float scale);

		const glm::vec3& get_position() const;
	private:
		void init_points(char letter);

		std::vector<glm::vec4> _points;
		glm::vec3 _position;
		float _scale;
		char _letter;
};

float get_letter_width(char letter);

#endif
