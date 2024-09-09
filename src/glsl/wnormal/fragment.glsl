#version 330 core

in vec3 FragNorm;
in vec3 FragPos;
out vec4 FragColor;

uniform vec3 lightPosition;
uniform vec3 lightColor;
uniform vec3 objectColor;

void main()
{
	float ambientScalar = 0.1;
	vec3 ambient = ambientScalar * lightColor;

	vec3 lightDir = normalize(lightPosition - FragPos);
	vec3 surfaceNormal = normalize(FragNorm);
	float diff = max(dot(lightDir, surfaceNormal), 0.0);
	vec3 diffuse = diff * lightColor;

	vec3 result = (ambient + diffuse) * objectColor;

	FragColor = vec4(result, 1.0f);
}
