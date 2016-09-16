#include "Camera.h"

ICE::Camera::Camera() {
}

ICE::Camera::Camera(glm::vec3 position, glm::vec3 target, GLfloat movementSpeed, GLfloat mouseSpeed, GLfloat fov, GLfloat near, GLfloat far, GLuint screenWidth, GLuint screenHeight) {
	this->position = position;
	this->target = target;
	this->movementSpeed = movementSpeed;
	this->mouseSpeed = mouseSpeed;

	glm::vec3 worldUp(0.0f, 1.0f, 0.0f);
	direction = glm::normalize(position - target);
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

void ICE::Camera::handleKeyboardInput(Movement movement, GLfloat deltaTime) {
	GLfloat actualMovementSpeed = movementSpeed * deltaTime;
	if (movement == Movement::FORWARD)
		position += actualMovementSpeed * front;
	if (movement == Movement::BACKWARD)
		position -= actualMovementSpeed * front;
	if (movement == Movement::LEFT)
		position -= glm::normalize(glm::cross(front, up)) * actualMovementSpeed;
	if (movement == Movement::RIGHT)
		position += glm::normalize(glm::cross(front, up)) * actualMovementSpeed;
	if (movement == Movement::UPWARD)
		position += actualMovementSpeed * up;
	if (movement == Movement::DOWNWARD)
		position -= actualMovementSpeed * up;
}

void ICE::Camera::handleMouseInput(GLfloat offsetX, GLfloat offsetY) {
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
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	this->front = glm::normalize(front);
}
