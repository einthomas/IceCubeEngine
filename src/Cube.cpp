#include "Cube.h"

GLuint ICE::Cube::VAO;
GLuint ICE::Cube::VBO;

ICE::Cube::Cube() {
}

ICE::Cube::Cube(Shader shader, Camera *camera, Material material, glm::vec3 position, glm::vec3 scale, glm::vec3 rotationAxis, GLfloat angle)
	: Shape(shader, camera, material, position, scale, rotationAxis, angle) {
}

ICE::Cube::Cube(Shader shader, Camera *camera, Texture texture, glm::vec3 position, glm::vec3 scale, glm::vec3 rotationAxis, GLfloat angle)
	: Shape(shader, camera, texture, position, scale, rotationAxis, angle) {
}

ICE::Cube::Cube(Camera *camera, glm::vec3 position, glm::vec3 scale, glm::vec3 rotationAxis, GLfloat angle)
	: Shape(camera, position, scale, rotationAxis, angle) {
}

void ICE::Cube::draw(std::vector<Light> lights) {
	shader.use();
	glBindVertexArray(VAO);

	Shape::draw(lights);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	glBindVertexArray(0);
}

bool ICE::Cube::intersects(glm::vec3 position) {
	glm::vec4 w = model * glm::vec4(this->position, 1.0f);
	glm::vec3 worldPos(w.x, w.y, w.z);

	glm::vec4 s = model * glm::vec4(this->scale, 1.0f);
	glm::vec3 worldScale(s.x, s.y, s.z);

	if (position.x > worldPos.x - worldScale.x && position.x < worldPos.x + worldScale.x &&
			position.y > worldPos.y - worldScale.y && position.y < worldPos.y + worldScale.y &&
			position.z > worldPos.z - worldScale.z && position.z < worldPos.z + worldScale.z) {
		return true;
	}

	return false;
}

void ICE::Cube::init() {
	GLfloat vertices[] = {
		 // Positions			// Texture Coords   // Normals			
		-0.5f, -0.5f, -0.5f,	0.0f, 0.0f,			0.0f,  0.0f, -1.0f,	
		 0.5f, -0.5f, -0.5f,	1.0f, 0.0f,			0.0f,  0.0f, -1.0f,	
		 0.5f,  0.5f, -0.5f,	1.0f, 1.0f,			0.0f,  0.0f, -1.0f,	
		 0.5f,  0.5f, -0.5f,	1.0f, 1.0f,			0.0f,  0.0f, -1.0f,	
		-0.5f,  0.5f, -0.5f,	0.0f, 1.0f,			0.0f,  0.0f, -1.0f,	
		-0.5f, -0.5f, -0.5f,	0.0f, 0.0f,			0.0f,  0.0f, -1.0f,	

		-0.5f, -0.5f,  0.5f,	0.0f, 0.0f,			0.0f,  0.0f, 1.0f,	
		 0.5f, -0.5f,  0.5f,	1.0f, 0.0f,			0.0f,  0.0f, 1.0f,	
		 0.5f,  0.5f,  0.5f,	1.0f, 1.0f,			0.0f,  0.0f, 1.0f,	
		 0.5f,  0.5f,  0.5f,	1.0f, 1.0f,			0.0f,  0.0f, 1.0f,	
		-0.5f,  0.5f,  0.5f,	0.0f, 1.0f,			0.0f,  0.0f, 1.0f,	
		-0.5f, -0.5f,  0.5f,	0.0f, 0.0f,			0.0f,  0.0f, 1.0f,	

		-0.5f,  0.5f,  0.5f, -	1.0f, 0.0f,		   -1.0f,  0.0f,  0.0f,	
		-0.5f,  0.5f, -0.5f, -	1.0f, 1.0f,		   -1.0f,  0.0f,  0.0f,	
		-0.5f, -0.5f, -0.5f, -	0.0f, 1.0f,		   -1.0f,  0.0f,  0.0f,	
		-0.5f, -0.5f, -0.5f, -	0.0f, 1.0f,		   -1.0f,  0.0f,  0.0f,	
		-0.5f, -0.5f,  0.5f, -	0.0f, 0.0f,		   -1.0f,  0.0f,  0.0f,	
		-0.5f,  0.5f,  0.5f, -	1.0f, 0.0f,		   -1.0f,  0.0f,  0.0f,	

		 0.5f,  0.5f,  0.5f,	1.0f, 0.0f,			1.0f,  0.0f,  0.0f,	
		 0.5f,  0.5f, -0.5f,	1.0f, 1.0f,			1.0f,  0.0f,  0.0f,	
		 0.5f, -0.5f, -0.5f,	0.0f, 1.0f,			1.0f,  0.0f,  0.0f,	
		 0.5f, -0.5f, -0.5f,	0.0f, 1.0f,			1.0f,  0.0f,  0.0f,	
		 0.5f, -0.5f,  0.5f,	0.0f, 0.0f,			1.0f,  0.0f,  0.0f,	
		 0.5f,  0.5f,  0.5f,	1.0f, 0.0f,			1.0f,  0.0f,  0.0f,	

		-0.5f, -0.5f, -0.5f,	0.0f, 1.0f,			0.0f, -1.0f,  0.0f,	
		 0.5f, -0.5f, -0.5f,	1.0f, 1.0f,			0.0f, -1.0f,  0.0f,	
		 0.5f, -0.5f,  0.5f,	1.0f, 0.0f,			0.0f, -1.0f,  0.0f,	
		 0.5f, -0.5f,  0.5f,	1.0f, 0.0f,			0.0f, -1.0f,  0.0f,	
		-0.5f, -0.5f,  0.5f,	0.0f, 0.0f,			0.0f, -1.0f,  0.0f,	
		-0.5f, -0.5f, -0.5f,	0.0f, 1.0f,			0.0f, -1.0f,  0.0f,	

		-0.5f,  0.5f, -0.5f,	0.0f, 1.0f,			0.0f,  1.0f,  0.0f,	
		 0.5f,  0.5f, -0.5f,	1.0f, 1.0f,			0.0f,  1.0f,  0.0f,	
		 0.5f,  0.5f,  0.5f,	1.0f, 0.0f,			0.0f,  1.0f,  0.0f,	
		 0.5f,  0.5f,  0.5f,	1.0f, 0.0f,			0.0f,  1.0f,  0.0f,	
		-0.5f,  0.5f,  0.5f,	0.0f, 0.0f,			0.0f,  1.0f,  0.0f,	
		-0.5f,  0.5f, -0.5f,	0.0f, 1.0f,			0.0f,  1.0f,  0.0f
	};
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Positions
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// TexCoords
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// Normals
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
}
