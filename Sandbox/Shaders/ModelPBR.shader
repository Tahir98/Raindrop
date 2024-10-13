#vertex shader
#version 460 core


layout(location = 0) in vec3 vpos;
layout(location = 1) in vec3 vnormal;
layout(location = 2) in vec2 vtexcoord;

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
	//gl_Position.z = gl_Position.w;
}


#fragment shader
#version 460 core

struct Material {
	vec4 color;
	float roughness;
	float metallic;
	float specular;
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

uniform samplerCube cubeMap;

float PI = 3.14159265359;

//Fresnel Reflectance
vec3 Fresnel_Schlick(float VdotH, vec3 F0) {
	return F0 + (1.0f - F0) * pow(1.0f - VdotH,5.0f);
}

//Normal Distribution Functiom
float NDF_GGX(float NdotH, float roughness) {
	float alpha = roughness * roughness;
	float alpha2 = alpha * alpha;

	float denom = (NdotH * NdotH) * (alpha2 - 1.0) + 1.0f;

	return alpha2 / (PI  * denom * denom);
}

float Geometry_Schlick_GGX(float NdotV, float roughness) {
	float alpha = roughness * roughness;
	float k = alpha / 2.0f;

	return max(NdotV, 0.001f) / (NdotV * (1.0f - k) + k);
}

//Geometry Term
float Geometry_Smith(float NdotV, float NdotL, float roughness) {
	return Geometry_Schlick_GGX(NdotL, roughness) * Geometry_Schlick_GGX(NdotV, roughness);
}

vec3 gamma_sRGB(vec3 color) {
	return pow(color, vec3(2.2f));
}

vec3 gammaInv_sRGB(vec3 color) {
	return pow(color, vec3(1.0f / 2.2f));
}


void main() {
	vec3 baseColor = texture(diffuseTex, texcoord).xyz;

	//Required Vectors
	vec3 N = normalize(normal); //Normal
	vec3 L = light.direction * -1.0f; //Light direction

	vec3 V = normalize(cameraPos - position); //View direction
	vec3 H = normalize(L + V); //Halfway vector

	//Required dot products
	float NdotV = clamp(dot(N,V), 0.0f, 1.0f);
	float NdotL = clamp(dot(N,L), 0.0f, 1.0f);
	float NdotH = clamp(dot(N,H), 0.0f, 1.0f);
	float VdotH = clamp(dot(V,H), 0.0f, 1.0f);

	vec3 F0 = vec3(0.16f * material.specular * material.specular);
	F0 = mix(F0, baseColor, material.metallic); 

	vec3 F = Fresnel_Schlick(VdotH, F0);
	float NDF = NDF_GGX(NdotH, material.roughness);
	float G = Geometry_Smith(NdotV, NdotL, material.roughness);

	vec3 specular = (F * NDF * G) / (4.0f * max(NdotV, 0.001f) * max(NdotL, 0.001f));

	vec3 diffuse = (baseColor * (vec3(1.0f) - F)) * (1.0f - material.metallic) / PI;

	outputColor = vec4(diffuse + specular, 1);
}
