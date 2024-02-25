#pragma once
#include "OpenGL/VertexArray.h"
#include "OpenGL/VertexBuffer.h"
#include "OpenGL/IndexBuffer.h"
#include "OpenGL/Shader.h"
#include "OpenGL/Texture3D.h"
#include "OpenGL/Texture2D.h"
#include "OpenGL/OpenGLUtility.h"
#include "OpenGL/FrameBuffer.h"

#include "Noise/NoiseGenerator.h"

#include "Camera/PerspectiveCamera.h"

#include "LineRenderer.h"

namespace Engine {
	class VolumeRenderer {
	private:
		bool isInitialized = false;

		glm::vec3 position = glm::vec3(0, 1600, 0);
		glm::vec3 scale = glm::vec3(1, 1, 1);
		glm::vec3 rotation = glm::vec3(0, 0, 0);
		glm::mat4 modelMat = glm::mat4(1.0f);
		
		OpenGLState rendererState;

		//Screen space vertices
		std::vector<glm::vec3> vertices;
		std::vector<uint32_t> indices;

		//OpenGL objects
		VertexBuffer* vb = nullptr;
		VertexArray* va = nullptr;
		IndexBuffer* ib = nullptr;
		Shader* shader = nullptr;

		std::vector<NoiseLayer> shapeNoiseLayers;
		std::vector<NoiseLayer> detailNoiseLayers;
		NoiseGenerator noiseGenerator;

		glm::vec3 volumeSize = glm::vec3(32000, 1000, 32000);
		
		uint32_t shapeTextureSize = 128;
		uint32_t detailTextureSize = 32;

		glm::vec3 shapeTextureFitSize = glm::vec3(15000, 15000, 15000);
		glm::vec3 detailTextureFitSize = glm::vec3(1200, 1200, 1200);
		
		glm::vec3 shapeTextureMovementSpeed = glm::vec3(0, 0, 0);
		glm::vec3 detailTextureMovementSpeed = glm::vec3(0, 0, 0);

		glm::vec3 shapeTexturePositionOffset = glm::vec3(0, 0, 0);
		glm::vec3 detailTexturePositionOffset = glm::vec3(0, 0, 0);

		Texture3D* shapeTexture = nullptr;
		Texture3D* detailTexture = nullptr;
		Texture2D* noiseTex = nullptr; //For stochastic jittering

		glm::vec4 shapeTextureWeights = glm::vec4(0.65f, 0.32f, 0.22f, 0.10f);
		glm::vec2 detailTextureWeights = glm::vec2(0.20f, 0.12f);

		//Rendering parameters
		float minDensity = 0;
		float maxDensity = 1;
		float stepSize = 40.0f; //It determines quality
		float opacity = 0.6f;
		float alphaThreshold = 0.98f; 

		float lightMarchStepSize = 100;
		float lightBaseIntensity = 0.2f;
		float lightAbsorptionCoefficient = 2.0f;

		float falloffDistanceVertical = 25;
		float falloffDistanceHorizontal = 100;

		glm::vec3 animationSpeed = glm::vec3(0, 0, 0);

		glm::vec3 lightDirection = glm::vec3(0, -1, 0);
		glm::vec2 screenSize = glm::vec2(1600, 900);

		LineRenderer lineRenderer;

		int splitCount = 1;

	public:
		//Debug mode
		bool showPropertiesWindow = true;
		bool showBoundingBox = true;
	public:
		VolumeRenderer();
		~VolumeRenderer();

		bool init();
		void dispose();

		void update(float delta);
		void draw(PerspectiveCamera& camera, FrameBuffer& fb);

		void setPosition(glm::vec3 position);
		void setScale(glm::vec3 scale);
		void setRotation(glm::vec3 rotation);
		glm::vec3 getPosition();
		glm::vec3 getScale();
		glm::vec3 getRotation();

		void regenerateVolumeTexture();
		void recalculateLightData();

		void setVolumeSize(glm::vec3 volumeSize);
		glm::vec3 getVolumeSize();

		void setMinDensity(float density);
		void setMaxDensity(float density);
		float getMinDensity();
		float getMaxDensity();

		void setStepSize(float stepSize);
		float getStepSize();

		void setOpacity(float opacity);
		float getOpacity();

		void setLightMarchStepSize(float stepSize);
		void setLightBaseIntensity(float baseIntensity);
		void setLightAbsorptionCoefficient(float absorption);
		float getLightMarchStepSize();
		float getLightBaseIntensity();
		float getLightAbsorptionCoefficient();

		void setLightDirection(glm::vec3 direction);
		void setScreenSize(glm::vec2 screenSize);

	private:
		void DrawPropertiesWindow();
		void DrawBoundingBox(PerspectiveCamera& camera);

		void GenerateVolumeData();
		void UpdateVertexData();
		void ClearData();
		void AddDefaultNoiseLayers();
	};
}