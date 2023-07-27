#ifdef COMPILE_VERTEX

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 textureCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 fragmentTextureCoord;

void main() {

    gl_Position = projection * view * model * vec4(position, 1.0f);
    fragmentTextureCoord = textureCoord;

}

#endif
#ifdef COMPILE_FRAGMENT

in vec2 fragmentTextureCoord;

uniform sampler2D textureSlot;
uniform vec4 materialColor;

layout(location = 0) out vec4 fragmentColor;

void main() {

	fragmentColor = texture(textureSlot, fragmentTextureCoord) * materialColor;

}

#endif