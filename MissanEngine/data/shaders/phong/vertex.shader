#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 textureCoord;
layout (location = 2) in vec3 normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat3 normalMatrix;

out vec3 fragmentPosition;
out vec3 fragmentNormal;
out vec2 fragmentTextureCoord;

void main() {

	fragmentPosition = vec3(model * vec4(position, 1.0));
	fragmentNormal = normalize(normalMatrix * normal);
	fragmentTextureCoord = textureCoord;

	gl_Position = projection * view * vec4(fragmentPosition, 1.0);

}