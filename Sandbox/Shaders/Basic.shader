#vertex shader
#version 460 core
layout(location = 0) in vec3 vpos;
layout(location = 1) in vec3 vcolor;

out vec3 color;

void main() {
	color = vcolor;

	gl_Position = vec4(vpos, 1);
}



#fragment shader
#version 460 core

in vec3 color;

out vec4 oColor;

void main() {
	oColor = vec4(color, 1);
}