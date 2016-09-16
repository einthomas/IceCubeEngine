#include "Shape.h"

ICE::Shape::Shape(Shader shader, Camera *camera, glm::vec3 color, glm::vec3 position, glm::vec3 scale, glm::vec3 rotationAxis, GLfloat angle) {
	this->shader = shader;
	this->camera = camera;
	this->color = color;
	this->position = position;
	this->scale = scale;
	this->rotationAxis = rotationAxis;
	this->angle = angle;
	hasTexture = false;

	updateTransformMatrix();
}

ICE::Shape::Shape(Shader shader, Camera *camera, Texture texture, glm::vec3 position, glm::vec3 scale, glm::vec3 rotationAxis, GLfloat angle) {
	this->shader = shader;
	this->camera = camera;
	this->texture = texture;
	this->position = position;
	this->scale = scale;
	this->rotationAxis = rotationAxis;
	this->angle = angle;
	hasTexture = true;

	updateTransformMatrix();
}

void ICE::Shape::draw() {
	shader.setMatrix4("model", model);
	shader.setMatrix4("view", camera->getViewMatrix());
	shader.setMatrix4("projection", camera->projection);

	shader.setInteger("hasTexture", hasTexture);
	if (hasTexture) {
		shader.setTexture2D("textureUniform", GL_TEXTURE0, texture.textureID, 0);
	} else {
		shader.setVector3f("colorUniform", color);
	}
}

void ICE::Shape::updateTransformMatrix() {
	model = glm::mat4();
	model = glm::translate(model, position);
	model = glm::rotate(model, glm::radians(angle), rotationAxis);
	model = glm::scale(model, scale);
}

void ICE::Shape::setPosition(glm::vec3 position) {
	this->position = position;
	updateTransformMatrix();
}

void ICE::Shape::setScale(glm::vec3 scale) {
	this->scale = scale;
	updateTransformMatrix();
}

void ICE::Shape::setRotation(glm::vec3 rotationAxis, GLfloat angle) {
	this->rotationAxis = rotationAxis;
	this->angle = angle;
	updateTransformMatrix();
}

void ICE::Shape::translateBy(glm::vec3 direction) {
	position += direction;
	updateTransformMatrix();
}

void ICE::Shape::scaleBy(glm::vec3 scale) {
	this->scale += scale;
	updateTransformMatrix();
}

void ICE::Shape::rotateBy(glm::vec3 rotationAxis, GLfloat angle) {
	this->rotationAxis += rotationAxis;
	this->angle += angle;
	updateTransformMatrix();
}