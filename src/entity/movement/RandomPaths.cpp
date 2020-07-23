#include "RandomPaths.hpp"

#include "../Movable.hpp"

glm::vec3 RandomPaths::generate_target(const Movable& movable, unsigned int group_id) {
	glm::vec3 target_point;
	target_point.x = _perlin_noise({static_cast<float>(movable.get_position().x + movable.get_position().y + movable.get_position().z),
								   static_cast<float>(group_id)});

	target_point.y = _perlin_noise({static_cast<float>(movable.get_position().x + movable.get_position().y + movable.get_position().z + 100.7),
								   static_cast<float>(group_id)});

	target_point.z = _perlin_noise({static_cast<float>(movable.get_position().x + movable.get_position().y + movable.get_position().z + 200.7),
								   static_cast<float>(group_id)});

	return target_point;
}

void RandomPaths::apply_force(std::vector<Movable>& movables) {
	for (Movable& m : movables) {
		glm::vec3 target_point = generate_target(m, 0);

		glm::vec3 dir = target_point - m.get_position();
		glm::vec3 update = dir - m.get_velocity();

		m.update_acceleration(update*0.01f);
	}
}
