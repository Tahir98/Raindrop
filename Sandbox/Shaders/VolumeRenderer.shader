#vertex shader
#version 460 core
layout(location = 0) in vec3 vpos;

void main() {
	gl_Position = vec4(vpos.xy, 0, 1);
}



#fragment shader
#version 460 core
uniform int screenWidth;
uniform int screenHeight;

uniform vec3 cameraPos;

uniform sampler3D shapeTex;
uniform sampler3D detailTex;

uniform sampler2D noiseTex;
uniform sampler2D depthTex;

uniform float stepSize;

uniform vec3 boundMin;
uniform vec3 boundMax;

uniform float coverage;
uniform float transmittanceThreshold;

uniform float zNear;
uniform float zFar;

uniform vec3 shapeTexPosOffset;
uniform vec3 detailTexPosOffset;

uniform float shapeTexFitSize;
uniform float detailTexFitSize;

uniform vec4 shapeTexWeights;
uniform vec2 detailTexWeights;

uniform vec3 lightDirection;
uniform int lightMarchStepCount;
uniform float lightBaseIntensity;
uniform float lightAbsorptionSun;
uniform float lightAbsorptionCloud;
uniform float lightEnergyCoefficient;

uniform float falloffDistanceH;
uniform float falloffDistanceV;

uniform mat4 _CameraToWorld;
uniform mat4 _CameraInverseProjection;

const float PI = 3.1415926535f;

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

float remap(float originalValue, float originalMin, float originalMax, float newMin, float newMax) {
	return newMin + (originalValue - originalMin) / (originalMax - originalMin) * (newMax - newMin);
}

float CalculateEdgeWeight(vec3 position) {
    float edgeWeightX = min(position.x - boundMin.x, boundMax.x - position.x);
    edgeWeightX = clamp(edgeWeightX / falloffDistanceH, 0 , 1);

    float edgeWeightY = min(position.y - boundMin.y, (boundMax.y - position.y) / 4);
    edgeWeightY = clamp(edgeWeightY / falloffDistanceV, 0 , 1);

    float edgeWeightZ = min(position.z - boundMin.z, boundMax.z - position.z);
    edgeWeightZ = clamp(edgeWeightZ / falloffDistanceH, 0 , 1);

    float edgeWeight = min(edgeWeightX, edgeWeightZ) * edgeWeightY;

    return edgeWeight;
}

float SampleBaseDensity(vec3 position) {
    vec3 baseTexCoord = (position - shapeTexPosOffset - boundMin) / shapeTexFitSize;
    vec4 baseDensity = texture(shapeTex, baseTexCoord);  

    baseDensity *= shapeTexWeights;
    float shapeFBM = baseDensity.x + baseDensity.y + baseDensity.z + baseDensity.w;

    float edgeWeight = CalculateEdgeWeight(position);

    float density = clamp(shapeFBM * edgeWeight, 1.0f - coverage, 1);
    return remap(density, 1.0f - coverage, 1, 0, 1);
}

float SampleDensity(vec3 position) {
    vec3 baseTexCoord = (position - shapeTexPosOffset - boundMin) / shapeTexFitSize;
    vec4 baseDensity = texture(shapeTex, baseTexCoord);  

    baseDensity *= shapeTexWeights;
    float shapeFBM = baseDensity.x + baseDensity.y + baseDensity.z + baseDensity.w;

    if(shapeFBM <= 0)
        return 0;

    vec3 detailTexCoord = (position - shapeTexPosOffset - detailTexPosOffset - boundMin) / detailTexFitSize;
    vec2 detailDensity = texture(detailTex, detailTexCoord).rg;  

    detailDensity *= detailTexWeights;
    float detailFBM = detailDensity.x + detailDensity.y;

    float edgeWeight = CalculateEdgeWeight(position);

    float density = clamp((shapeFBM - detailFBM), 1.0f - coverage, 1);
    return remap(density, 1.0f - coverage , 1, 0, 1) * edgeWeight; 
}
//d : deth, f : farplane, n : nearplane 
float LinearEyeDepth(float d,float n, float f) {
    d = d * 2.0f - 1.0f;
    return 2.0f * f * n / (-d * (f - n) +  (f + n));
}

float CalculateLightIntensity(vec3 rayPos, vec3 rayDir) {
    float intensity = 1;

    vec2 rayHit = RayAABBIntersection(boundMin, boundMax, rayPos, rayDir);
    float totalDensity = 0;     

    if(rayHit.y > 0) {
        float lightMarchStepSize = rayHit.y / float(lightMarchStepCount);
        float offset = 0;
        
        for(int i = 0; i < lightMarchStepCount; i++) {
             vec3 position = rayPos + rayDir * (offset); 
    
            float density = SampleDensity(position);
    
            totalDensity += density * lightMarchStepSize;
            offset += lightMarchStepSize;
        }
    }

    intensity = exp(totalDensity * lightAbsorptionSun *  -0.01f);

    return lightBaseIntensity + intensity * ( 1.0f - lightBaseIntensity);
}

vec3 GetRayDirection(vec2 uv) {
    vec3 direction = (_CameraInverseProjection * vec4(uv * 2.0f - 1.0f, 0, 1)).xyz;
    direction = (_CameraToWorld * vec4(direction, 0)).xyz;

    return normalize(direction);
}

vec3 GetCameraViewDir(vec2 uv) {
   return (_CameraInverseProjection * vec4(uv * 2.0f - 1.0f, 0, 1)).xyz;
}

float phaseFunc(float cosAngle, float g) {
    float invPI = 1.0f / (4.0f * PI);
    float g_sqr = g * g;
    float denom = 1.0f + g_sqr + 2.0f * g * cosAngle * sqrt(cosAngle);

    return invPI * (1.0f - g_sqr) / denom;
}

void main() {
    vec2 screen_uv = gl_FragCoord.xy / vec2(screenWidth, screenHeight);

    vec3 rayDirection = GetRayDirection(screen_uv);
    vec2 rayHit = RayAABBIntersection(boundMin, boundMax, cameraPos, rayDirection);

    //Calculate actual depth to limit ray end point
    float depth = texture(depthTex, screen_uv).r;

    depth = LinearEyeDepth(depth, zNear, zFar);
    float cosAngle = dot(normalize(GetCameraViewDir(screen_uv)), vec3(0, 0, -1));
    depth = depth * (1.0f / cosAngle);

    rayHit.y = min(depth - rayHit.x, rayHit.y);
    
    float offset = 0;
    float noise = texture(noiseTex, gl_FragCoord.xy / vec2(64, 64)).r;
    offset += noise * stepSize;
    vec3 position = cameraPos + rayDirection * rayHit.x;

    float transmittance = 1;
    float lightEnergy = 0;

    float phaseVal = phaseFunc(dot(rayDirection, lightDirection * -1.0f), -1);

    float energyCoefficient = lightEnergyCoefficient / lightAbsorptionCloud;

    while (offset < rayHit.y ) {
        position = cameraPos + rayDirection * (rayHit.x + offset);

        float density = SampleDensity(position);
        density = clamp(density, 0, 1);

        if (density > 0) {
            float intensity = CalculateLightIntensity(position, normalize(lightDirection * -1.0f));
            
            lightEnergy += density * intensity * transmittance * stepSize * energyCoefficient * 0.1f;
            transmittance = transmittance * exp(-density * stepSize * lightAbsorptionCloud * 0.01f);

            if(transmittance <= transmittanceThreshold)
                break;
        }
    
        offset += stepSize;
    }
        
    transmittance = clamp(transmittance / (1.0f - transmittanceThreshold), 0, 1);

    lightEnergy /= (1.0f - transmittance);

    outputColor = vec4(lightEnergy, lightEnergy, lightEnergy, 1.0f - transmittance); 
}