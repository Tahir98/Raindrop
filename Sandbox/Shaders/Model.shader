#vertex shader
#version 460 core

layout(location = 0) in ve3 vpos;
layout(location = 1) in ve3 vnormal;
layout(location = 2) in ve2 vtexcoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 position;
out vec3 normal;
out vec2 texcoord;

void main() {
	position = (model * vec4(vpos, 1.0f)).xyz;
	normal = mat3(model) * vnormal;
	texcoord = vtexcoord;

	gl_Position = projection * view * vec4(position, 1.0f);
}

#fragment shader

struct Material {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

struct DirectionalLight{
	vec3 direction;
	vec4 color;
	float intensity;
};

in vec3 position;
in vec3 normal;
in vec2 texcoord;

out vec4 outputColor;

uniform vec3 cameraPos;

uniform Material material;
uniform DirectionalLight light;

uniform sampler2D diffuseTex;

void main() {
	vec3 Normal = normalize(normal);

	//Ambient
	vec3 ambient = material.ambient;

	//Diffuse
	float cosAngle = clamp(dot(Normal, light.direction * -1.0f), 0, 1);
	vec3 diffuse = material.diffuse * cosAngle;

	//Specular;
	vec3 viewDirection = normalize(position - cameraPos);
	vec3 reflectionDirection = reflect(light.direction, Normal);

	float cosAngle = clamp(dot(viewDirection * -1.0f, reflectionDirection), 0, 1);
	vec3 specular = material.specular * pow(cosAngle, material.shininess);

	vec4 texColor = texture(diffuseTex, texcoord);

	outputColor = vec4(ambient + diffuse + specular, 1.0f) * texColor * light.color * light.intensity;
}
