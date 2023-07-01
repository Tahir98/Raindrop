#vertex shader
#version 460 core

layout(location = 0) in vec3 vPos;
layout(location = 1) in vec3 vTexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 texCoord;

void main() {
	texCoord = vTexCoord.xy;

	vec4 pos = (model * view * vec4(vPos, 0.0f));
	pos = projection * vec4(pos.xyz, 1.0f);
	pos.z = pos.w;

	gl_Position = pos;
}

#fragment shader
#version 460 core

in vec2 texCoord;

uniform uvec2 texSize;
uniform sampler2D hdriTex;

out vec4 outputColor;

void main() {

	int kernelSize = 1;

	float kernel[3][3] = {
		{1,2,1 },
		{2,3,2 },
		{1,2,1 }
	};

	uvec2 pixelID = uvec2(0,0);
	pixelID.x = uint(float(texSize.x) * texCoord.x);
	pixelID.y = uint(float(texSize.y) * texCoord.y);

	vec3 totalValue = vec3(0, 0, 0);

	uvec2 startPointID = uvec2(pixelID.x - kernelSize / 2, pixelID.y - kernelSize / 2);

	for (int i = 0; i < kernelSize; i++) {
		for (int j = 0; j < kernelSize; j++) {
			vec2 tCoord;
			tCoord.x = float(startPointID.x + i) / float(texSize.x);
			tCoord.y = float(startPointID.y + j) / float(texSize.y);

			totalValue += texture(hdriTex, tCoord).xyz;
		}
	}

	float kernelArae = float(kernelSize * kernelSize);

	outputColor = vec4(totalValue / kernelArae, 1);
}