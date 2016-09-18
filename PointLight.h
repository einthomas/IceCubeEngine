#pragma once

#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>

#include "Light.h"

namespace ICE {
	class PointLight : public Light {
	public:
		PointLight(glm::vec3 position, glm::vec3 color, GLfloat linear, GLfloat quadratic, GLfloat constant = 1.0f) : Light(position, color, LightType::POINT) {
			this->linear = linear;
			this->quadratic = quadratic;
			this->constant = constant;
		}
	};
}
