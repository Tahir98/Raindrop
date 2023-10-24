#vertex shader

#version 460 core
layout(location = 0) in vec3 vPos;

uniform mat4 view;
uniform mat4 projection;

out vec3 texCoord;

void main() {
	texCoord = vPos;

	vec3 pos = mat3(view) * vPos;
	gl_Position = projection * vec4(pos, 1.0f);
}


#fragment shader
#version 460 core

in vec3 texCoord;
uniform samplerCube cubemap;

out vec4 outputColor;

void main() {
	outputColor = texture(cubeMap, texCoord);
}
