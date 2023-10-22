#vertex shader
#version 460 core
layout(location = 0) in vec3 vPos;
layout(location = 1) in vec2 vTexCoord;

//uniform mat4 model;
//uniform mat4 view;
//uniform mat4 projection;

out vec2 texCoord;

void main() {
	texCoord = vTexCoord;
	gl_Position = vec4(vPos, 1);
}



#fragment shader
#version 460 core

in vec2 texCoord;

uniform sampler2D tex;

out vec4 oColor;

void main() {
	oColor = texture(tex, texCoord);
}