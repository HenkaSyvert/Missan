#ifdef COMPILE_VERTEX

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

#endif
#ifdef COMPILE_FRAGMENT

struct Material{
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	float shininess;
};

struct Light{
	vec3 position;
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
};

in vec2 fragmentTextureCoord;
in vec3 fragmentPosition;
in vec3 fragmentNormal;

uniform vec3 cameraPosition;
uniform Material material;
uniform Light light;
uniform sampler2D textureSlot;

layout (location = 0) out vec4 fragmentColor;

void main() {

	vec4 result = vec4(0);

	// ambient
	vec4 ambient = material.ambient * light.ambient;
	result += texture(textureSlot, fragmentTextureCoord) * ambient;
   
	// diffuse
	vec3 lightDirection = normalize(light.position - fragmentPosition);
	float lightIncline = max(dot(fragmentNormal, lightDirection), 0.0);
	vec4 diffuse = (material.diffuse * lightIncline) * light.diffuse;
	result += diffuse;
	
	// specular
	vec3 cameraDirection = normalize(cameraPosition - fragmentPosition);
	vec3 reflectDirection = reflect(-lightDirection, fragmentNormal);
	float specularIncline = max(dot(cameraDirection, reflectDirection), 0.0);
	float shine = pow(specularIncline, material.shininess);
	vec4 specular = (material.specular * shine) * light.specular;
	result += specular;

	fragmentColor = result;

}

#endif