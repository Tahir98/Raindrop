#vertex shader
#version 460 core
layout(location = 0) in vec2 vPos;
layout(location = 1) in vec2 vTexCoord;

out vec2 texCoord;

void main() {
	texCoord = vTexCoord;

	gl_Position = vec4(vPos, 0, 1);
}



#fragment shader
#version 460 core

uniform sampler2D MainTex;
uniform sampler2D DepthTex;

in vec2 texCoord;
out vec4 color;

void main() {
	color = texture(MainTex, texCoord) * 0.5f;
}