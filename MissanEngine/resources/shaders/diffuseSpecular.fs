#version 330 core

layout (location = 0) out vec4 fragmentColor;

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

in vec2 textureCoord;
in vec3 fragmentPosition;
in vec3 fragmentNormal;

uniform vec3 cameraPosition;
uniform Material material;
uniform Light light;
uniform sampler2D textureSlot;

void main(){

	vec4 result = vec4(0);

	// ambient
	vec4 ambient = material.ambient * light.ambient;
	result += texture(textureSlot, textureCoord) * ambient;
   
	//// diffuse
	//vec3 lightDirection = normalize(light.position - fragmentPosition);
	//float lightIncline = max(dot(fragmentNormal, lightDirection), 0.0);
	//vec4 diffuse = (material.diffuse * lightIncline) * light.diffuse;
	//result += diffuse;
	//
	//// specular
	//vec3 cameraDirection = normalize(cameraPosition - fragmentPosition);
	//vec3 reflectDirection = reflect(-lightDirection, fragmentNormal);
	//float specularIncline = max(dot(cameraDirection, reflectDirection), 0.0);
	//float shine = pow(specularIncline, material.shininess);
	//vec4 specular = (material.specular * shine) * light.specular;
	//result += specular;

	fragmentColor = result;

}