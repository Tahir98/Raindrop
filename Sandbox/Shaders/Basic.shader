#vertex shader
#version 460 core
layout(location = 0) in vec2 vpos;

void main() {
	gl_Position = vec4(vpos, 0, 1);
}

#fragment shader
#version 460 core
out vec4 oColor;

void main() {
	oColor = vec4(0, 0, 1, 1);
}