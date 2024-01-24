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

		glm::vec3 position = glm::vec3(0, 20, 0);
		glm::vec3 scale = glm::vec3(1, 1, 1);
		glm::vec3 rotation = glm::vec3(0, 0, 0);
		glm::mat4 modelMat = glm::mat4(1.0f);
		
		OpenGLState rendererState;

		//Cube shape that volume data shown inside
		std::vector<glm::vec3> vertices;
		std::vector<uint32_t> indices;

		//Opengl objects
		VertexBuffer* vb = nullptr;
		VertexArray* va = nullptr;
		IndexBuffer* ib = nullptr;
		Shader* shader = nullptr;

		//Volume data parameters
		std::vector<NoiseLayer> noiseLayers;
		NoiseGenerator noiseGenerator;

		uint32_t virtualTextureSize = 256;
		glm::uvec3 textureSize = glm::uvec3(128, 128, 128);
		glm::vec3 volumeSize = glm::vec3(100, 25, 100);
		glm::vec3 textureFitSize = glm::vec3(100, 25, 100);

		//Volume data textures
		std::vector<float> volumeData;
		Texture3D* densityTex = nullptr; // It holds volumetric density and light intensity data
		Texture2D* noiseTex = nullptr; //For stochastic jittering

		//Rendering parameters
		float minDensity = 0;
		float maxDensity = 1;
		float stepSize = 0.5f; //It determines quality
		float opacity = 0.6f;
		float alphaThreshold = 0.98f; 

		float lightMarchStepSize = 2;
		float lightBaseIntensity = 0.2f;
		float lightAbsorptionCoefficient = 2.0f;

		float falloffDistanceVertical = 2;
		float falloffDistanceHorizontal = 10;

		glm::vec3 texturePositionOffset = glm::vec3(0, 0, 0);
		glm::vec3 animationSpeed = glm::vec3(0, 0, 0);

		glm::vec3 lightDirection = glm::vec3(0, -1, 0);
		glm::vec2 screenSize = glm::vec2(1600, 900);

		LineRenderer lineRenderer;

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

		void setNoiseLayers(std::vector<NoiseLayer>& layers);
		std::vector<NoiseLayer>& getNoiseLayers();

		void regenerateVolumeTexture();
		void recalculateLightData();

		uint32_t getVirtualTexSize();
		void setVirtualTexSize(uint32_t texSize);

		void setVolumeSize(glm::vec3 volumeSize);
		glm::vec3 getVolumeSize();

		void setTextureFitSize(glm::vec3 fitSize);
		glm::vec3 getTextureFitSize();

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
	};
}