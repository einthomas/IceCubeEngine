#version 330 core

layout (location = 0) in vec3 Position;
layout (location = 1) in vec2 TexCoord;
layout (location = 2) in vec3 Normals;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 texCoord;
out vec3 normals;

void main() {
    gl_Position = projection * view * model * vec4(Position.xyz, 1.0);
	texCoord = vec2(TexCoord.x, 1.0 - TexCoord.y);
	normals = Normals;
	//texCoord = TexCoord;
}
