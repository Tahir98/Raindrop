#vertex shader
#version 460 core
layout(location = 0) in vec3 vpos;

uniform mat4 view;
uniform mat4 projection;

void main() {
	gl_Position = projection * view * vec4(vpos, 1);
}



#fragment shader
#version 460 core

uniform vec4 color;

out vec4 oColor;

void main() {
	oColor = color;
}