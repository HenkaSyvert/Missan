#version 330 core

out vec4 fragmentColor;

struct Material{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

struct Light{
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

in vec3 fragmentPosition;
in vec3 fragmentNormal;

uniform vec3 cameraPosition;
uniform Material material;
uniform Light light;

void main(){

	vec3 result;

	// ambient
	vec3 ambient = material.ambient * light.ambient;
	result += ambient;

	// diffuse
	vec3 lightDirection = normalize(light.position - fragmentPosition);
	float lightIncline = max(dot(fragmentNormal, lightDirection), 0.0);
	vec3 diffuse = (material.diffuse * lightIncline) * light.diffuse;
	result += diffuse;
	
	// specular
	vec3 cameraDirection = normalize(cameraPosition - fragmentPosition);
	vec3 reflectDirection = reflect(-lightDirection, fragmentNormal);
	float specularIncline = max(dot(cameraDirection, reflectDirection), 0.0);
	float shine = pow(specularIncline, material.shininess);
	vec3 specular = (material.specular * shine) * light.specular;
	result += specular;

	fragmentColor = vec4(result, 1.0);

}