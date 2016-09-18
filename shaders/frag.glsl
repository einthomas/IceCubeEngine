#version 330 core

#define NR_POINT_LIGHTS 64

struct DirLight {
	vec3 dir;
	vec3 color;
};

struct Material {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

struct PointLight {
	vec3 pos;
	vec3 color;
	float constant;
	float linear;
	float quadratic;
};

uniform Material material;
uniform sampler2D textureUniform;
uniform bool hasTexture;

uniform vec3 eyePos;
uniform int numPointLights;
uniform DirLight dirLight;
uniform PointLight pointLights[NR_POINT_LIGHTS];

in vec2 texCoord;
in vec3 normal;
in vec3 fragPos;

out vec4 color;

vec3 calcDirLight(vec3 viewDir, vec3 norm) {
	vec3 color = dirLight.color * material.ambient;
	
	// diffuse
	color += dirLight.color * (max(dot(norm, normalize(-dirLight.dir)), 0.0) * material.diffuse);

	// specular - phong
	vec3 r = reflect(dirLight.dir, norm);
	color += dirLight.color * (pow(max(dot(r, viewDir), 0.0), material.shininess) * material.specular);

	// specular - blinn-phong
	//vec3 h = normalize(-dirLight.dir + viewDir);
	//color += dirLight.color * (pow(max(dot(h, viewDir), 0.0), material.shininess) * material.specular);

	return color;
}

vec3 calcPointLight(PointLight pointLight, vec3 viewDir, vec3 norm) {
	vec3 color = pointLight.color * material.ambient;
	
	// diffuse
	vec3 lightDir = normalize(fragPos - pointLight.pos);
	color += pointLight.color * (max(dot(norm, normalize(-lightDir)), 0.0) * material.diffuse);

	// specular - phong
	vec3 r = reflect(lightDir, norm);
	color += pointLight.color * (pow(max(dot(r, viewDir), 0.0), material.shininess) * material.specular);

	float dist = distance(pointLight.pos, fragPos);
	float attenuation = 1.0 / (pointLight.constant + pointLight.linear * dist + pointLight.quadratic * dist * dist);

	return color * attenuation;
}

void main() {
	vec3 norm = normalize(normal);
	vec3 viewDir = normalize(eyePos - fragPos);
	vec3 dirLightColor = calcDirLight(viewDir, norm);

	vec3 pointLightColor = vec3(0.0);
	for (int i = 0; i < numPointLights; i++) {
		pointLightColor += calcPointLight(pointLights[i], viewDir, norm);
	}

	if (hasTexture) {
		color = texture(textureUniform, texCoord) * vec4(dirLightColor + pointLightColor, 1.0f);
	} else {
		color = vec4(dirLightColor + pointLightColor, 1.0f);
	}
}
