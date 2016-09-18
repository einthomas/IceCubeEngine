#pragma once

#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>

#include "Light.h"

namespace ICE {
	class DirectionalLight : public Light {
	public:
		DirectionalLight(glm::vec3 position, glm::vec3 direction, glm::vec3 color) : Light(position, color, LightType::DIRECTIONAL) {
			this->direction = direction;
		}
	};
}
