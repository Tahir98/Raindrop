#compute shader
#version 460 core

layout(local_size_x = 4, local_size_y = 4, local_size_z = 1) in;
layout(rgba8, binding = 0) uniform image2D screenTex;

void main() {
	//gl_NumWorkGroups = work group size (uvec3)
	//gl_WorkGroupID = work group id (uvec3)
	//gl_WorkGroupSize = work group size (uvec3)
	//gl_LocalInvocationID = id in local thread group (uvec3)
	//gl_GlocalInvocationID = global id (SV_DispatchThreadID in hlsl) (uvec3)
	//gl_LocalInvocationIndex = local index in a work group 

	uvec3 id = gl_GlobalInvocationID;
	ivec2 texSize = imageSize(screenTex);

	//if(any(id.xy >= uvec2(texSize)))
	//	return;

	ivec2 pixelCoord = ivec2(id.xy);
	
	vec4 color = vec4(1, 1, 0, 1);

	imageStore(screenTex, pixelCoord, color);
}