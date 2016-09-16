#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <iostream>
#include <map>
#include <string>
#include <ft2build.h>
#include FT_FREETYPE_H

#include "Shader.h"
#include "Util.h"

namespace ICE {
	struct Character {
		GLuint textureID;
		glm::ivec2 size;
		glm::ivec2 bearing;
		GLuint advance;
	};

	class TextRenderer {
	public:
		static void init(GLuint screenWidth, GLuint screenHeight);
		static void renderText(std::string text, GLfloat x, GLfloat y, GLfloat size, glm::vec3 color);
		static glm::vec3 calcDimensions(std::string text, GLfloat size);

	private:
		static std::map<GLchar, Character> characters;
		static glm::mat4 projection;
		static GLuint VBO, VAO;
		static Shader shader;
	};
}
