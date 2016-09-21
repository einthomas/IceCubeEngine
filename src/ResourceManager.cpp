#include "ResourceManager.h"

#include <iostream>

std::string ICE::ResourceManager::TEXTURE_REGION_SEPARATOR = "::textures";
std::string ICE::ResourceManager::MODEL_REGION_SEPARATOR = "::models";
std::string ICE::ResourceManager::MATERIAL_REGION_SEPARATOR = "::materials";
std::string ICE::ResourceManager::SHADER_REGION_SEPARATOR = "::shaders";
std::map<std::string, ICE::Texture> ICE::ResourceManager::textures;
std::map<std::string, ICE::Material> ICE::ResourceManager::materials;
std::map<std::string, ICE::Shader> ICE::ResourceManager::shaders;

void ICE::ResourceManager::loadResources(std::string resourceFilePath) {
	std::ifstream file(resourceFilePath);
	std::string line;
	std::string currentRegion;

	while (std::getline(file, line)) {
		if (line.length() == 0) {
			continue;
		}

		if (line.length() >= 2 && line.at(0) == '/' && line.at(1) == '/') {		// line starts with a comment
			continue;
		}

		if (line.compare(TEXTURE_REGION_SEPARATOR) == 0 || 
				line.compare(MODEL_REGION_SEPARATOR) == 0 ||
				line.compare(MATERIAL_REGION_SEPARATOR) == 0 ||
				line.compare(SHADER_REGION_SEPARATOR) == 0) {
			currentRegion = line;
		} else {
			line = line.substr(0, line.find("//"));
			ICE::Util::rtrim(line);
			std::vector<std::string> splitLine = Util::splitString(line, ':');
			if (currentRegion.compare(TEXTURE_REGION_SEPARATOR) == 0) {
				textures[splitLine[0]] = loadTexture(splitLine[1]);

			} else if (currentRegion.compare(MODEL_REGION_SEPARATOR) == 0) {
				//models[splitLine[0]] = loadModel(splitLine[1]);

			} else if (currentRegion.compare(SHADER_REGION_SEPARATOR) == 0) {
				if (splitLine.size() == 2) {
					std::vector<std::string> paths = Util::splitString(splitLine[1], ';');
					if (paths.size() == 2) {
						Shader shader(Util::readFileToString(paths[0]), Util::readFileToString(paths[1]));
						shaders[splitLine[0]] = shader;
					}
				}

			} else if (currentRegion.compare(MATERIAL_REGION_SEPARATOR) == 0) {
				std::vector<std::string> materialProperties = Util::splitString(splitLine[1], ' ');

				if (materialProperties.size() == 10) {
					Material material;
					material.ambient = glm::vec3(atof(materialProperties[0].c_str()),
												 atof(materialProperties[1].c_str()),
												 atof(materialProperties[2].c_str()));

					material.diffuse= glm::vec3(atof(materialProperties[3].c_str()),
												atof(materialProperties[4].c_str()),
												atof(materialProperties[5].c_str()));

					material.specular = glm::vec3(atof(materialProperties[6].c_str()),
												  atof(materialProperties[7].c_str()),
												  atof(materialProperties[8].c_str()));

					material.shininess = atof(materialProperties[9].c_str());

					materials[splitLine[0]] = material;
				}
			}
		}
	}

	file.close();
}

ICE::Texture ICE::ResourceManager::loadTexture(std::string texturePath) {
	GLuint textureID;
	int width, height;
	unsigned char* image = SOIL_load_image(texturePath.c_str(), &width, &height, 0, SOIL_LOAD_RGB);

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);

	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	Texture texture;
	texture.textureID = textureID;
	texture.width = width;
	texture.height = height;

	return texture;
}
