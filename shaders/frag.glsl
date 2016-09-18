#version 330 core

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

uniform Material material;
uniform sampler2D textureUniform;
uniform bool hasTexture;

uniform vec3 eyePos;
uniform DirLight dirLight;

in vec2 texCoord;
in vec3 normal;
in vec3 fragPos;

out vec4 color;

vec3 calcDirLight(vec3 eyeVec) {
	vec3 norm = normalize(normal);
	vec3 color = dirLight.color * material.ambient;
	
	// diffuse
	color += dirLight.color * (max(dot(norm, normalize(-dirLight.dir)), 0.0) * material.diffuse);

	// specular - phong
	vec3 r = reflect(dirLight.dir, norm);
	color += dirLight.color * (pow(max(dot(r, eyeVec), 0.0), material.shininess) * material.specular);

	// specular - blinn-phong
	//vec3 h = normalize(-dirLight.dir + eyeVec);
	//color += dirLight.color * (pow(max(dot(h, eyeVec), 0.0), material.shininess) * material.specular);

	return color;
}

void main() {
	vec3 eyeVec = normalize(eyePos - fragPos);
	vec3 dirLightColor = calcDirLight(eyeVec);

	if (hasTexture) {
		color = texture(textureUniform, texCoord) * vec4(dirLightColor, 1.0f);
	} else {
		color = vec4(dirLightColor, 1.0f);
	}
}
