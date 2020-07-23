#ifndef __VECTORGENERATOR_CLASS__
#define __VECTORGENERATOR_CLASS__

#include <glm/glm.hpp>

class VectorGenerator {
	public:
		VectorGenerator();
		VectorGenerator(const glm::vec3& mean);
		VectorGenerator(const VectorGenerator&) = default;

		VectorGenerator& with_mean(const glm::vec3& mean);
		VectorGenerator& with_stddev(const glm::vec3& stddev);

		glm::vec3 get() const;
	private:
		glm::vec3 _mean;
		glm::vec3 _stddev;
};

#endif
