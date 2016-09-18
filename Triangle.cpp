#include "Triangle.h"

GLuint ICE::Triangle::VAO;
GLuint ICE::Triangle::VBO;

ICE::Triangle::Triangle(Shader shader, Camera *camera, Material material, glm::vec3 position, glm::vec3 scale, glm::vec3 rotationAxis, GLfloat angle)
	: Shape(shader, camera, material, position, scale, rotationAxis, angle) {
}

ICE::Triangle::Triangle(Shader shader, Camera *camera, Texture texture, glm::vec3 position, glm::vec3 scale, glm::vec3 rotationAxis, GLfloat angle)
	: Shape(shader, camera, texture, position, scale, rotationAxis, angle) {
}

void ICE::Triangle::draw(std::vector<Light> lights) {
	shader.use();
	glBindVertexArray(VAO);

	Shape::draw(lights);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glBindVertexArray(0);
}

void ICE::Triangle::init() {
	GLfloat vertices[] = {
		 // Positions		 // Colors
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // Bottom Right
		-0.5f, -0.5f, 0.0f,	 0.0f, 1.0f, 0.0f,   // Bottom Left
		 0.0f,  0.5f, 0.0f,	 0.0f, 0.0f, 1.0f    // Top 
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Positions
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// Colors
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
}
