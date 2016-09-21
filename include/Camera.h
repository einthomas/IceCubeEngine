#pragma once

#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "Movement.h"

namespace ICE {
	class Camera {
	public:
		GLfloat mouseSpeed;
		glm::vec3 position;
		glm::vec3 target;
		glm::mat4 projection;

		Camera();
		Camera(glm::vec3 position, glm::vec3 target, GLfloat mouseSpeed, GLfloat fov, GLfloat near, GLfloat far, GLuint screenWidth, GLuint screenHeight);
		void handleKeyboardInput(Movement movement, GLfloat movementSpeed, GLfloat deltaTime);
		void handleMouseInput(GLfloat positionX, GLfloat positionY);
		glm::mat4 getViewMatrix();

	private:
		glm::vec3 direction;
		glm::vec3 right;
		glm::vec3 up;
		glm::vec3 front;
		GLfloat yaw;
		GLfloat pitch;
		GLboolean firstMovement;
		GLdouble lastX, lastY;
	};
}
