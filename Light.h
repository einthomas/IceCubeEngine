#pragma once

#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>

#include "LightType.h"

namespace ICE {
	class Light {
	public:
		glm::vec3 position;
		glm::vec3 color;
		LightType lightType;

		// directional
		glm::vec3 direction;

		// point
		GLfloat constant;
		GLfloat linear;
		GLfloat quadratic;

		Light(glm::vec3 position, glm::vec3 color, LightType lightType);

	protected:
	};
}
