#version 330 core

uniform vec3 colorUniform;
uniform sampler2D textureUniform;
uniform bool hasTexture;

in vec2 texCoord;
in vec3 normals;

out vec4 color;

void main() {
	if (hasTexture) {
		color = texture(textureUniform, texCoord);
	} else {
		color = vec4(colorUniform, 1.0f);
	}
}
