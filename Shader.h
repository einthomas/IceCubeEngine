#pragma once

#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <GLM\glm.hpp>
#include <GLM\gtc\type_ptr.hpp>
#include <string>

namespace ICE {
	class Shader {
	public:
		GLuint program;

		Shader();
		Shader(std::string vertexSource, std::string fragmentSource);
		void use();

		void setFloat(std::string name, GLfloat value);
		void setInteger(std::string name, GLint value);
		void setVector2f(std::string name, GLfloat x, GLfloat y);
		void setVector2f(std::string name, glm::vec2 value);
		void setVector3f(std::string name, GLfloat x, GLfloat y, GLfloat z);
		void setVector3f(std::string name, glm::vec3 value);
		void setMatrix4(std::string name, const glm::mat4 &value);
		void setTexture2D(std::string name, GLenum activeTexture, GLuint texture, GLuint loc);

	private:
		GLuint loadShader(GLuint shaderType, std::string shaderCode);
	};
}
