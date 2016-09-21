#include "Shader.h"

#include <iostream>

ICE::Shader::Shader() { }

ICE::Shader::Shader(std::string vertexSource, std::string fragmentSource) {
	GLuint vertexShader = loadShader(GL_VERTEX_SHADER, vertexSource);
	GLuint fragmentShader = loadShader(GL_FRAGMENT_SHADER, fragmentSource);

	program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	GLint success;
	GLchar infoLog[512];
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		std::cout << "ERROR::SHADERPROGRAM::LINKING\n" << infoLog << std::endl;
	}
}

void ICE::Shader::use() {
	glUseProgram(program);
}

GLuint ICE::Shader::loadShader(GLuint shaderType, std::string shaderCode) {
	GLuint shader = glCreateShader(shaderType);
	const char *shaderCode_c_str = shaderCode.c_str();
	glShaderSource(shader, 1, &shaderCode_c_str, NULL);
	glCompileShader(shader);

	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR::ICE::Shader::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	return shader;
}

void ICE::Shader::setFloat(std::string name, GLfloat value) {
	glUniform1f(glGetUniformLocation(program, name.c_str()), value);
}

void ICE::Shader::setInteger(std::string name, GLint value) {
	glUniform1i(glGetUniformLocation(program, name.c_str()), value);
}

void ICE::Shader::setVector2f(std::string name, GLfloat x, GLfloat y) {
	glUniform2f(glGetUniformLocation(program, name.c_str()), x, y);
}

void ICE::Shader::setVector2f(std::string name, glm::vec2 value) {
	glUniform2f(glGetUniformLocation(program, name.c_str()), value.x, value.y);
}

void ICE::Shader::setVector3f(std::string name, GLfloat x, GLfloat y, GLfloat z) {
	glUniform3f(glGetUniformLocation(program, name.c_str()), x, y, z);
}

void ICE::Shader::setVector3f(std::string name, glm::vec3 value) {
	glUniform3f(glGetUniformLocation(program, name.c_str()), value.x, value.y, value.z);
}

void ICE::Shader::setMatrix4(std::string name, const glm::mat4 &value) {
	glUniformMatrix4fv(glGetUniformLocation(program, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void ICE::Shader::setTexture2D(std::string name, GLenum activeTexture, GLuint texture, GLuint loc) {
	glActiveTexture(activeTexture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(program, name.c_str()), loc);
}
