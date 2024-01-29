#shader_variant USE_AMBIENT_TEXTURE
#shader_variant USE_DIFFUSE_TEXTURE
#shader_variant USE_SPECULAR_TEXTURE
#shader_variant USE_NORMAL_MAP
#shader_variant USE_BUMP_MAP

#shader_variant USE_CUBE_MAP

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
	float metallic;
	float roughness;
	float ao;
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

uniform sampler2D albedoTex;

uniform sampler2D ambientTex;
uniform sampler2D specularTex;
uniform sampler2D normalTex;
uniform sampler2D bumpTex;

uniform samplerCube cubeMap;

//Physically based lighting
vec3 calculatePBL(vec3 pos, vec3 surfaceColor, vec3 normal, vec3 cameraPos, 
	Material material, DirectionalLight light) {



}

void main() {
	
}
