#include "VectorGenerator.hpp"

#include "../../misc/Misc.hpp"

VectorGenerator::VectorGenerator()
	: _mean(0.f, 0.f, 0.f), _stddev(0.f, 0.f, 0.f)
{}

VectorGenerator::VectorGenerator(const glm::vec3& mean)
	: _mean(mean), _stddev(0.f, 0.f, 0.f)
{}

VectorGenerator& VectorGenerator::with_mean(const glm::vec3& mean) {
	_mean = mean;
	return *this;
}

VectorGenerator& VectorGenerator::with_stddev(const glm::vec3& stddev) {
	_stddev = stddev;
	return *this;
}

glm::vec3 VectorGenerator::get() const {
	return glm::vec3(
		misc::generate_float(_mean.x, _stddev.x),
		misc::generate_float(_mean.y, _stddev.y),
		misc::generate_float(_mean.z, _stddev.z)
	);
}
