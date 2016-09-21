#pragma once

#define GLEW_STATIC
#include <GL\glew.h>
#include <SOIL.h>
#include <map>
#include <string>
#include <fstream>

#include "Util.h"
#include "Material.h"
#include "Shader.h"

namespace ICE {
	struct Texture {
		GLuint textureID;
		GLuint width, height;
	};

	class ResourceManager {
	public:
		static std::map<std::string, Texture> textures;
		//static std::map<std::string, Model> models;
		static std::map<std::string, Material> materials;
		static std::map<std::string, Shader> shaders;

		static void loadResources(std::string resourceFilePath);

	private:
		static std::string TEXTURE_REGION_SEPARATOR;
		static std::string MODEL_REGION_SEPARATOR;
		static std::string MATERIAL_REGION_SEPARATOR;
		static std::string SHADER_REGION_SEPARATOR;
		static Texture loadTexture(std::string texturePath);
		//static Model loadModel(std::string modelPath);
	};
}
