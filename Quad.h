#pragma once

#include "Shader.h"
#include "Shape.h"

namespace ICE {
	class Quad : public Shape {
	public:
		Quad(Shader shader, Camera *camera, glm::vec3 color, glm::vec3 position, glm::vec3 scale = glm::vec3(1.0f), glm::vec3 rotationAxis = glm::vec3(0.0f, 0.0f, 1.0f), GLfloat angle = 0.0f);
		Quad(Shader shader, Camera *camera, Texture texture, glm::vec3 position, glm::vec3 scale = glm::vec3(1.0f), glm::vec3 rotationAxis = glm::vec3(0.0f, 0.0f, 1.0f), GLfloat angle = 0.0f);

		void draw();
		static void init();

	private:
		static GLuint VAO, VBO, EBO;
	};
}
