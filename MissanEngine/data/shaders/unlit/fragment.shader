#version 330 core

in vec2 fragmentTextureCoord;

uniform sampler2D textureSlot;
uniform vec4 materialColor;

layout(location = 0) out vec4 fragmentColor;

void main() {

	fragmentColor = texture(textureSlot, fragmentTextureCoord) * materialColor;

}
