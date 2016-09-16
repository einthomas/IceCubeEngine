#include "ResourceManager.h"

std::string ICE::ResourceManager::TEXTURE_REGION_SEPARATOR = "::textures";
std::map<std::string, ICE::Texture> ICE::ResourceManager::textures;

void ICE::ResourceManager::loadResources(std::string resourceFilePath) {
	std::ifstream file(resourceFilePath);
	std::string line;
	std::string currentRegion;

	while (std::getline(file, line)) {
		if (line.compare(TEXTURE_REGION_SEPARATOR) == 0) {
			currentRegion = line;
		} else {
			std::vector<std::string> splitLine = Util::splitString(line, ':');
			if (currentRegion.compare(TEXTURE_REGION_SEPARATOR) == 0) {
				std::string key = splitLine[0];
				std::string texturePath = splitLine[1];
				textures.insert(std::pair<std::string, Texture>(key, loadTexture(texturePath)));			
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
