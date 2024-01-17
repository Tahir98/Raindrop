#vertex shader
#version 460 core
layout(location = 0) in vec3 vpos;

uniform vec2 screenSize;

void main() {
	gl_Position = vec4((vpos.xy / screenSize) * 2.0f - 1.0f, 0, 1);
}



#fragment shader
#version 460 core

uniform vec4 color;

out vec4 oColor;

void main() {
	oColor = color;
}