#include "Light.h"

ICE::Light::Light(glm::vec3 position, glm::vec3 color, LightType lightType) {
	this->position = position;
	this->color = color;
	this->lightType = lightType;
}
