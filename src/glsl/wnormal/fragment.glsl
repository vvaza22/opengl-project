#version 330 core

in vec3 FragNorm;
in vec3 FragPos;
out vec4 FragColor;

uniform vec3 lightPosition;
uniform vec3 lightColor;
uniform vec3 objectColor;
uniform vec3 cameraPosition;

void main()
{
	// Ambient
	float ambientScalar = 0.1;
	vec3 ambient = ambientScalar * lightColor;

	vec3 lightDir = normalize(lightPosition - FragPos);
	// Diffuse
	vec3 surfaceNormal = normalize(FragNorm);
	float diff = max(dot(lightDir, surfaceNormal), 0.0);
	vec3 diffuse = diff * lightColor;

	// Specular
	float specularScalar = 0.7;
	vec3 viewDir = normalize(cameraPosition - FragPos);
	vec3 uVector = surfaceNormal * dot(lightDir, surfaceNormal);
	vec3 reflectDir = 2 * uVector - lightDir;
	float specularDot = max(dot(reflectDir, viewDir), 0.0);
	float spec = pow(specularDot, 12);
	vec3 specular = specularScalar * spec * lightColor;

	vec3 result = (ambient + diffuse + specular) * objectColor;

	FragColor = vec4(result, 1.0f);
}
