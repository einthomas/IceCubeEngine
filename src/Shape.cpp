#include "Shape.h"

ICE::Shape::Shape() {
}

ICE::Shape::Shape(Shader shader, Camera *camera, Material material, glm::vec3 position, glm::vec3 scale, glm::vec3 rotationAxis, GLfloat angle) {
	this->shader = shader;
	this->camera = camera;
	this->material = material;
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

ICE::Shape::Shape(Camera *camera, glm::vec3 position, glm::vec3 scale, glm::vec3 rotationAxis, GLfloat angle) {
	this->camera = camera;
	this->position = position;
	this->scale = scale;
	this->rotationAxis = rotationAxis;
	this->angle = angle;
	hasTexture = false;

	updateTransformMatrix();
}

void ICE::Shape::draw(std::vector<Light> lights) {
	if (shader.program != -1) {		// if shader has been loaded and compiled
		shader.setMatrix4("model", model);
		shader.setMatrix4("view", camera->getViewMatrix());
		shader.setMatrix4("projection", camera->projection);

		shader.setVector3f("eyePos", camera->position);

		std::string varName;
		GLuint pointLightID = 0;
		for (int i = 0; i < lights.size(); i++) {
			if (lights[i].lightType == LightType::DIRECTIONAL) {
				varName = "dirLight";
				shader.setVector3f(varName + ".dir", lights[i].direction);
			}
			else if (lights[i].lightType == LightType::POINT) {
				varName = "pointLights[" + std::to_string(pointLightID++) + "]";
				shader.setVector3f(varName + ".pos", lights[i].position);
				shader.setFloat(varName + ".constant", lights[i].constant);
				shader.setFloat(varName + ".linear", lights[i].linear);
				shader.setFloat(varName + ".quadratic", lights[i].quadratic);
			}

			shader.setVector3f(varName + ".color", lights[i].color);
		}

		shader.setInteger("numPointLights", pointLightID);

		shader.setInteger("hasTexture", hasTexture);
		if (hasTexture) {
			shader.setTexture2D("textureUniform", GL_TEXTURE0, texture.textureID, 0);
		}
		else {
			shader.setVector3f("material.ambient", material.ambient);
			shader.setVector3f("material.diffuse", material.diffuse);
			shader.setVector3f("material.specular", material.specular);
			shader.setFloat("material.shininess", material.shininess);
		}
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