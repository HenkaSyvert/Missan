#version 330 core

layout (location = 0) in vec3 vertexPosition;
layout (location = 2) in vec3 vertexNormal;

out vec3 fragmentPosition;
out vec3 fragmentNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat3 normalMatrix;

void main(){

	fragmentPosition = vec3(model * vec4(vertexPosition, 1.0));
	fragmentNormal = normalize(normalMatrix * vertexNormal);

	gl_Position = projection * view * vec4(fragmentPosition, 1.0);

}