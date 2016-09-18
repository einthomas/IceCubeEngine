#pragma once

#define GLEW_STATIC
#include <GL\glew.h>
#include <glm\glm.hpp>

namespace ICE {
	struct Material {
		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;
		GLfloat shininess;
	};
}
