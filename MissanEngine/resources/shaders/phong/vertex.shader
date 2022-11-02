#version 330 core

layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec2 textureUv;
layout (location = 2) in vec3 vertexNormal;

out vec3 fragmentPosition;
out vec3 fragmentNormal;
out vec2 textureCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat3 normalMatrix;

void main(){

	fragmentPosition = vec3(model * vec4(vertexPosition, 1.0));
	fragmentNormal = normalize(normalMatrix * vertexNormal);
	textureCoord = textureUv;

	gl_Position = projection * view * vec4(fragmentPosition, 1.0);

}