#pragma once

#define GLEW_STATIC
#include <GL\glew.h>
#include <SOIL.h>
#include <map>
#include <string>
#include <fstream>

#include "Util.h"

namespace ICE {
	struct Texture {
		GLuint textureID;
		GLuint width, height;
	};

	class ResourceManager {
	public:
		static std::map<std::string, Texture> textures;

		static void loadResources(std::string resourceFilePath);

	private:
		static std::string TEXTURE_REGION_SEPARATOR;
		static Texture loadTexture(std::string texturePath);
	};
}
