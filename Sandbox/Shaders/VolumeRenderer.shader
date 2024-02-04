#vertex shader
#version 460 core
layout(location = 0) in vec3 vpos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 screenPos;
out vec3 cameraViewDir;
out vec3 worldPos;

void main() {
	worldPos = (model * vec4(vpos, 1.0f)).xyz;
	cameraViewDir = (view  * vec4(worldPos, 1.0f)).xyz;
    
	vec4 screen_uv = projection * vec4(cameraViewDir, 1.0f);
	
	screenPos = (screen_uv.xy / screen_uv.w * -1.0f) + 1;
    screenPos /= 2.0f;
	gl_Position = screen_uv;
}



#fragment shader
#version 460 core


in vec2 screenPos;
in vec3 cameraViewDir;
in vec3 worldPos;

uniform int screenWidth;
uniform int screenHeight;

uniform vec3 cameraPos;

uniform sampler3D textures[20];
uniform int textureCount;

uniform sampler2D noiseTex;
uniform sampler2D depthTex;

uniform float stepSize;

uniform vec3 boundMin;
uniform vec3 boundMax;

uniform float minDensity;
uniform float maxDensity;
uniform float alphaThreshold;
uniform float opacity;

uniform float zNear;
uniform float zFar;

uniform vec3 positionOffsets[20];
uniform vec3 textureFitSizes[20];

uniform vec3 lightDirection;
uniform float lightMarchStepSize;
uniform float lightBaseIntensity;
uniform float lightAbsorption;

uniform float falloffDistanceH;
uniform float falloffDistanceV;

out vec4 outputColor;

vec2 RayAABBIntersection(vec3 boundsMin, vec3 boundsMax, vec3 rayOrigin, vec3 rayDir) {
    
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
vec4 BlendFTB(vec4 color, vec4 newColor) {
    color.rgb += (1.0 - color.a) * newColor.a * newColor.rgb;
    color.a += (1.0 - color.a) * newColor.a;
    return color;
}

vec3 CalculateTexCoord(vec3 position) {
    //position += texturePositionOffset;
    return  (position - boundMin) / (boundMax - boundMin);
}

float SampleDensity(vec3 position) {
    float density = 0;

    for(int i = 0; i < textureCount; i++) {
        vec3 pos = position + positionOffsets[i];
        vec3 texCoord = (pos - boundMin) / textureFitSizes[i];

        density += texture(textures[i], texCoord).x;
    }

    if(density < minDensity || density > maxDensity)
        density = 0;
    //else {
    //    density = density - minDensity;
    //}

    //float density = texture(densityTex, texCoord).x;
       
    float edgeWeightX = min(position.x - boundMin.x, boundMax.x - position.x);
    edgeWeightX = clamp(edgeWeightX / falloffDistanceH, 0 , 1);

    float edgeWeightY = min(position.y - boundMin.y, boundMax.y - position.y);
    edgeWeightY = clamp(edgeWeightY / falloffDistanceV, 0 , 1);

    float edgeWeightZ = min(position.z - boundMin.z, boundMax.z - position.z);
    edgeWeightZ = clamp(edgeWeightZ / falloffDistanceH, 0 , 1);

    float edgeWeight = min(edgeWeightX, edgeWeightZ) * edgeWeightY;

    density = density * edgeWeight;

    //if(density < minDensity || density > maxDensity) {
    //    density = 0;
    //}

    return density;
}

//d : deth, f : farplane, n : nearplane 
float LinearEyeDepth(float d,float n, float f) {
    d = d * 2.0f - 1.0f;
    return 2.0f * f * n / (-d * (f - n) +  (f + n));
}

float CalculateLightIntensity(vec3 rayPos, vec3 rayDir, float noise) {
    float intensity = 1;

    vec2 rayHit = RayAABBIntersection(boundMin, boundMax, rayPos, rayDir);

    if(rayHit.y > 0) {
        float offset = noise * lightMarchStepSize;
        
        while(offset < rayHit.y) {
            vec3 position = rayPos + rayDir * (rayHit.y - offset); 

            float density = SampleDensity(position) * opacity;
            intensity = intensity * exp(lightMarchStepSize * lightAbsorption * density * -0.1f);

            if(intensity < 0.01f)
                break;

            offset += lightMarchStepSize;
        }
    }

    return lightBaseIntensity + intensity * ( 1.0f - lightBaseIntensity);
}

void main() {
    outputColor = vec4(0, 0, 0, 0);

    vec3 rayDirection = normalize(worldPos - cameraPos);
    vec2 rayHit = RayAABBIntersection(boundMin, boundMax, cameraPos, rayDirection);

    //Calculate actual depth to limit ray end point
    vec2 screen_uv = gl_FragCoord.xy / vec2(screenWidth, screenHeight);
    float depth = texture(depthTex, screen_uv).r;

    depth = LinearEyeDepth(depth, zNear, zFar);
    float cosAngle = dot(normalize(cameraViewDir), vec3(0, 0, -1));
    depth = depth * (1.0f / cosAngle);

    rayHit.y = min(depth - rayHit.x, rayHit.y);
    
    float offset = 0;
    float noise = texture(noiseTex, screen_uv * 64).r;
    offset += noise * stepSize;
    vec3 position = cameraPos + rayDirection * rayHit.x;

    while (offset < rayHit.y ) {
        position = cameraPos + rayDirection * (rayHit.x + offset);

        float density = SampleDensity(position);
        density = clamp(density, 0, 1);
        

        if (density > 0) {
            float intensity = CalculateLightIntensity(position, normalize(lightDirection * -1.0f), noise);
            
            outputColor = BlendFTB(outputColor, vec4(intensity, intensity, intensity, density * opacity * stepSize * 0.9));
            if(outputColor.a >= alphaThreshold)
                break;
        }
    
        offset += stepSize;
    }
    
     outputColor.rgb *= (1.0f / outputColor.a);
     outputColor.a /= alphaThreshold; 
}