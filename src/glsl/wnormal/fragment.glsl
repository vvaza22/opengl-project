#version 330 core

in vec3 FragNorm;
out vec4 FragColor;

void main()
{
	vec3 modifiedNorm = (FragNorm + vec3(1.0, 1.0, 1.0)) / 2.0;
	FragColor = vec4(modifiedNorm, 1.0f);
}
