#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 textureCoords;

out vec3 color;
//out vec2 pass_textureCoords;

uniform mat4 u_model;	// aka transformationMatrix
uniform mat4 u_view;
uniform mat4 u_proj;
uniform vec3 u_color;

void main() {

	gl_Position = vec4(position, 1.0f);
	color = position;

}