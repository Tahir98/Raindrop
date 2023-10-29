#vertex shader
#version 460 core
layout(location = 0) in vec3 vpos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 screenPos;
out vec3 worldPos;

void main() {
	worldPos = (model * vec4(vpos, 1.0f)).xyz;
	
	vec4 screen_uv = projection * view * vec4(worldPos, 1);
	
	screenPos = screen_uv.xy / screen_uv.w;
	gl_Position = screen_uv;
}



#fragment shader
#version 460 core

in vec2 screenPos;
in vec3 worldPos;

uniform int screenWidth;
uniform int screenHeight;

uniform ivec3 texSize;
uniform vec3 cameraPos;

uniform sampler3D densityTex;

uniform float stepSize;

uniform vec3 boundMin;
uniform vec3 boundMax;

uniform float threshold;
uniform float opacity;

out vec4 outputColor;

vec2 rayBoxDst(vec3 boundsMin, vec3 boundsMax, vec3 rayOrigin, vec3 rayDir) {
    
    vec3 invRayDir = 1.0f / rayDir;

    vec3 t0 = (boundsMin - rayOrigin) * invRayDir;
    vec3 t1 = (boundsMax - rayOrigin) * invRayDir;
    vec3 tmin = min(t0, t1);
    vec3 tmax = max(t0, t1);

    float dstA = max(max(tmin.x, tmin.y), tmin.z);
    float dstB = min(tmax.x, min(tmax.y, tmax.z));

    float dstToBox = max(0, dstA);
    float dstInsideBox = max(0, dstB - dstToBox);
    return vec2(dstToBox, dstInsideBox);
}

//Blend front to back
vec4 blendFTB(vec4 dstColor, vec4 srcColor) {
    return dstColor + (1.0f - dstColor.w) * srcColor;
}

vec4 blendBTF(vec4 dstColor, vec4 srcColor) {
    return (1.0f - srcColor.w) * dstColor + srcColor;
}

vec4 BlendUnder(vec4 color, vec4 newColor)
{
    color.rgb += (1.0 - color.a) * newColor.a * newColor.rgb;
    color.a += (1.0 - color.a) * newColor.a;
    return color;
}

vec3 calculateTexCoord(vec3 boundMin, vec3 boundMax, vec3 position) {
    position = clamp(position, boundMin, boundMax);

    return  (position - boundMin) / (boundMax - boundMin);
}

float sampleDensity(vec3 texCoord) {
    return texture(densityTex, texCoord).x;
}

void main() {
    outputColor = vec4(0, 0, 0, 0.0f);
    vec3 volumeColor = vec3(1, 1, 1);
    //outputColor = BlendUnder(outputColor, vec4(volumeColor, 0.5f));

    vec3 rayDirection = normalize(worldPos - cameraPos);

    vec2 rayHit = rayBoxDst(boundMin, boundMax, cameraPos, rayDirection);

    float offset = 0;
    vec3 position = cameraPos + rayDirection * rayHit.x;

    while (offset < rayHit.y ) {
        position = cameraPos + rayDirection * (rayHit.x + offset);
        vec3 texCoord = calculateTexCoord(boundMin, boundMax, position);
        
        float density = sampleDensity(texCoord);
        density = clamp(density, 0, 1);
        
        if (density > threshold) {
            outputColor = BlendUnder(outputColor, vec4(density, density, density, density * opacity * stepSize * 100.0f));
            if(outputColor.a >= 0.99f)
                break;
        }

        offset += stepSize;
    }

    if (outputColor.a < 0.001f)
        discard;
}