#pragma once

#include <GLM\glm.hpp>

#include "Camera.h"
#include "Shader.h"
#include "Shape.h"

namespace ICE {
	class Cube : public Shape {
	public:
		Cube(Shader shader, Camera *camera, Material material, glm::vec3 position, glm::vec3 scale = glm::vec3(1.0f), glm::vec3 rotationAxis = glm::vec3(0.0f, 0.0f, 1.0f), GLfloat angle = 0.0f);
		Cube(Shader shader, Camera *camera, Texture texture, glm::vec3 position, glm::vec3 scale = glm::vec3(1.0f), glm::vec3 rotationAxis = glm::vec3(0.0f, 0.0f, 1.0f), GLfloat angle = 0.0f);

		void draw(std::vector<Light> lights);
		static void init();

	private:
		static GLuint VAO, VBO;
	};
}
