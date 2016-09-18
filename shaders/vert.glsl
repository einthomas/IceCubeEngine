#version 330 core

layout (location = 0) in vec3 Position;
layout (location = 1) in vec2 TexCoord;
layout (location = 2) in vec3 Normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 texCoord;
out vec3 normal;
out vec3 fragPos;

void main() {
    gl_Position = projection * view * model * vec4(Position.xyz, 1.0);
	texCoord = vec2(TexCoord.x, 1.0 - TexCoord.y);
	normal = Normal;
	fragPos = vec3(model * vec4(Position, 1.0f));	// transform the position to world space
}
