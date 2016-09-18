#pragma once

#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <vector>

#include "Shader.h"
#include "ResourceManager.h"
#include "Camera.h"
#include "Light.h"
#include "Material.h"

namespace ICE {
	class Shape {
	public:
		Shape(Shader shader, Camera *camera, Material material, glm::vec3 position, glm::vec3 scale = glm::vec3(1.0f), glm::vec3 rotationAxis = glm::vec3(0.0f, 0.0f, 1.0f), GLfloat angle = 0.0f);
		Shape(Shader shader, Camera *camera, Texture texture, glm::vec3 position, glm::vec3 scale = glm::vec3(1.0f), glm::vec3 rotationAxis = glm::vec3(0.0f), GLfloat angle = 0.0f);
		virtual void draw(std::vector<Light> lights);

		void setPosition(glm::vec3 position);
		void setScale(glm::vec3 scale);
		void setRotation(glm::vec3 rotationAxis, GLfloat angle);

		void translateBy(glm::vec3 direction);
		void scaleBy(glm::vec3 scale);
		void rotateBy(glm::vec3 rotationAxis, GLfloat angle);

	protected:
		Camera *camera;

		Shader shader;
		Material material;

		glm::mat4 model;
		glm::vec3 position;
		glm::vec3 scale;
		glm::vec3 rotationAxis;
		GLfloat angle;

		Texture texture;
		bool hasTexture;

	private:
		void updateTransformMatrix();
	};
}
