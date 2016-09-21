#include "Camera.h"

ICE::Camera::Camera() {
}

ICE::Camera::Camera(glm::vec3 position, glm::vec3 target, GLboolean freeFly, GLfloat mouseSpeed, GLfloat fov, GLfloat near, GLfloat far, GLuint screenWidth, GLuint screenHeight) {
	this->position = position;
	this->target = target;
	this->freeFly = freeFly;
	this->mouseSpeed = mouseSpeed;

	firstMovement = true;

	glm::vec3 worldUp(0.0f, 1.0f, 0.0f);
	glm::vec3 direction = glm::normalize(position - target);
	right = glm::normalize(glm::cross(direction, worldUp));
	up = glm::cross(-direction, right);
	front = glm::vec3(0.0f, 0.0f, -1.0f);

	yaw = 0.0f;
	pitch = 0.0f;

	projection = glm::perspective(fov, (GLfloat)screenWidth / (GLfloat)screenHeight, near, far);
}

glm::mat4 ICE::Camera::getViewMatrix() {
	return glm::lookAt(position, position + front, up);
}

void ICE::Camera::handleKeyboardInput(Movement movement, GLfloat movementSpeed, GLfloat deltaTime) {
	GLfloat actualMovementSpeed = movementSpeed * deltaTime;
	if (movement == Movement::FORWARD)
		position += actualMovementSpeed * movementDirection;
	if (movement == Movement::BACKWARD)
		position -= actualMovementSpeed * movementDirection;
	if (movement == Movement::LEFT)
		position -= glm::normalize(glm::cross(movementDirection, up)) * actualMovementSpeed;
	if (movement == Movement::RIGHT)
		position += glm::normalize(glm::cross(movementDirection, up)) * actualMovementSpeed;
	if (movement == Movement::UPWARD)
		position += actualMovementSpeed * up;
	if (movement == Movement::DOWNWARD)
		position -= actualMovementSpeed * up;
}

void ICE::Camera::handleMouseInput(GLfloat positionX, GLfloat positionY) {
	if (firstMovement) {
		lastX = positionX;
		lastY = positionY;
		firstMovement = false;
	}

	GLfloat offsetX = positionX - lastX;
	GLfloat offsetY = lastY - positionY;
	lastX = positionX;
	lastY = positionY;

	offsetX *= mouseSpeed;
	offsetY *= mouseSpeed;

	yaw += offsetX;
	pitch += offsetY;

	if (pitch > 89.0f) {
		pitch = 89.0f;
	}
	if (pitch < -89.0f) {
		pitch = -89.0f;
	}

	glm::vec3 front;
	front.x = cos(glm::radians(yaw));
	front.y = 0.0f;
	front.z = sin(glm::radians(yaw));

	if (!freeFly) {
		movementDirection = glm::normalize(front);
	}

	front.x *= cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z *= cos(glm::radians(pitch));
	this->front = glm::normalize(front);

	if (freeFly) {
		movementDirection = front;
	}
}
