#include "Quad.h"

GLuint ICE::Quad::VAO;
GLuint ICE::Quad::VBO;
GLuint ICE::Quad::EBO;

ICE::Quad::Quad(Shader shader, Camera *camera, Material material, glm::vec3 position, glm::vec3 scale, glm::vec3 rotationAxis, GLfloat angle)
	: Shape(shader, camera, material, position, scale, rotationAxis, angle) {
}

ICE::Quad::Quad(Shader shader, Camera *camera, Texture texture, glm::vec3 position, glm::vec3 scale, glm::vec3 rotationAxis, GLfloat angle)
	: Shape(shader, camera, texture, position, scale, rotationAxis, angle) {
}

void ICE::Quad::draw(std::vector<Light> lights) {
	shader.use();
	glBindVertexArray(VAO);

	Shape::draw(lights);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}

void ICE::Quad::init() {
	GLfloat vertices[] = {
		 // Positions		 // Texture coords
		 0.5f,  0.5f, 0.0f,  1.0f, 1.0f,
		 0.5f, -0.5f, 0.0f,	 1.0f, 0.0f,
		-0.5f, -0.5f, 0.0f,	 0.0f, 0.0f,
		-0.5f,  0.5f, 0.0f,	 0.0f, 1.0f
	};

	GLuint indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Positions
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// Texture coords
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}
