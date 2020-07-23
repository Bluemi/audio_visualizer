#ifndef __COLORHANDLER_CLASS__
#define __COLORHANDLER_CLASS__

#include <vector>

#include "entity/creation/VectorGenerator.hpp"

#include "BaseHandler.hpp"

class ColorHandler : public BaseHandler {
	public:
		ColorHandler(float strength, float std_dev);
		void update(const essentia::Pool& pool);
	private:
		struct _Color {
			_Color(glm::vec3 col, glm::vec2 cen, float str) : color(col), center(cen), strength(str) {}

			glm::vec3 color;
			glm::vec2 center;
			float strength;
		};

		glm::vec3 calculate_color(const glm::vec2& emotions);
		std::vector<float> get_influences(const glm::vec2& emotions, const std::vector<_Color>& color);

		float _strength;
		float _std_dev;
		VectorGenerator _color_gen;
		static std::vector<_Color> _colors;
};

#endif
