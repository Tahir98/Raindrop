#include "VolumeRenderer.h"


namespace Engine {
	VolumeRenderer::VolumeRenderer() {
		rendererState.cullingEnabled = true;
		rendererState.cullMode = CullFront;
		rendererState.blendingEnabled = true;
		rendererState.depthTestEnabled = false;
	}

	VolumeRenderer::~VolumeRenderer() {
		delete vb;
		delete va;
		delete ib;
		delete shader;

		delete densityTex;
		delete noiseTex;
	}

	bool VolumeRenderer::init() {
		vertices.clear();

		vertices = {
			glm::vec3(0,0,0),
			glm::vec3(0,1,0),
			glm::vec3(1,1,0),
			glm::vec3(1,0,0),
			glm::vec3(1,0,1),
			glm::vec3(1,1,1),
			glm::vec3(0,1,1),
			glm::vec3(0,0,1)
		};

		for (int i = 0; i < vertices.size(); i++) {
			vertices[i] += glm::vec3(-0.5f, -0.5f, -0.5f);
			vertices[i] *= volumeSize;
		}

		indices = {
			0,1,2, 0,2,3,
			3,2,5, 3,5,4,
			4,5,6, 4,6,7,
			7,6,1, 7,1,0,
			7,0,3, 7,3,4,
			1,6,5, 1,5,2
		};

		//OpenGL objects creation
		vb = new VertexBuffer(vertices.data(), vertices.size() * sizeof(glm::vec3), GL_STATIC_DRAW);

		va = new VertexArray();
		va->PushElement(vb, 3, VertexArray::DataType::FLOAT, false);

		ib = new IndexBuffer(indices.data(), indices.size() * sizeof(uint32_t), GL_STATIC_DRAW);

		shader = new Shader("Shaders/VolumeRenderer.shader");

		//3D texture generation
		uint32_t voxelCount = virtualTextureSize * virtualTextureSize * virtualTextureSize;
		float fVoxelCount = textureFitSize.x * textureFitSize.y * textureFitSize.z;
		float tSize = glm::pow(fVoxelCount, 1.0f / 3.0f);

		textureSize.x = (uint32_t)(virtualTextureSize * tSize / textureFitSize.x);
		textureSize.y = (uint32_t)(virtualTextureSize * tSize / textureFitSize.y);
		textureSize.z = (uint32_t)(virtualTextureSize * tSize / textureFitSize.z);
		ENG_LOG_INFO("Volume renderer texture size ({0}, {1}, {2})", textureSize.x, textureSize.y, textureSize.z);

		NoiseLayer layer1;
		layer1.offset = glm::vec3(120.34,467.66, 53.87);
		layer1.scale = 1.0f / virtualTextureSize * 3.0f;
		layer1.opacity = 0.5f;

		NoiseLayer layer2;
		layer2.offset = glm::vec3(125.34, 46.66, 520.87);
		layer2.scale = 1.0f / virtualTextureSize * 22.0f;
		layer2.opacity = 0.1f;

		noiseLayers.push_back(layer2);

		for (int z = 0; z < textureSize.z; z++) {
			for (int y = 0; y < textureSize.y; y++) {
				for (int x = 0; x < textureSize.x; x++) {
					glm::vec3 point(x, y, z);
					float noise = noiseGenerator.Value(point, noiseLayers);

					volumeData.push_back(glm::vec2(noise, 1));
				}
			}
		}

		densityTex = new Texture3D(volumeData.data(), textureSize.x, textureSize.y, textureSize.z, TextureFormat::RG32_Float, TRILINEAR, TextureWrapper::MIRROR);

		std::vector<uint8_t> noiseData;
		Xorshift rng((uint32_t)2356);

		for (int y = 0; y < 64; y++) {
			for (int x = 0; x < 64; x++) {
				noiseData.push_back((uint8_t)(rng.nextFloat() * 255.0f));
			}
		}

		noiseTex = new Texture2D(noiseData.data(), 64, 64, TextureFormat::R8_UNORM, TextureFilter::POINT, TextureWrapper::REPEAT);

		return true;
	}

	void VolumeRenderer::dispose() {

	}

	void VolumeRenderer::update(float delta) {
	}

	void VolumeRenderer::draw(PerspectiveCamera& camera, FrameBuffer& fb) {
		OpenGLUtility::SetOpenGLState(rendererState);

		modelMat = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), scale);

		va->bind();
		ib->bind();

		shader->bind();

		densityTex->bind();
		densityTex->setActiveTextureSlot(0);

		noiseTex->bind();
		noiseTex->setActiveTextureSlot(1);

		uint32_t& depthTexId = fb.getDepthAttachmentID();
		glBindTexture(GL_TEXTURE_2D, depthTexId);
		glActiveTexture(GL_TEXTURE0);

		shader->SetUniformMatrix4x4("model", 1, false, glm::value_ptr(modelMat));
		shader->SetUniformMatrix4x4("view", 1, false, glm::value_ptr(camera.getViewMatrix()));

		glm::mat4 projection = camera.getProjectionMatrix();
		shader->SetUniformMatrix4x4("projection", 1, false, glm::value_ptr(projection));

		shader->SetUniform1i("screenWidth", screenSize.x);
		shader->SetUniform1i("screenHeight", screenSize.y);

		shader->SetUniform3i("texSize", textureSize);
		shader->SetUniform3f("cameraPos", camera.getPosition());
		shader->SetUniform1i("densityTex", 1);
		//shader->SetUniform1i("noiseTex", 1);
		shader->SetUniform1i("depthTex", 0);

		shader->SetUniform1f("stepSize", stepSize);
		shader->SetUniform3f("boundMin", position - volumeSize / 2.0f);
		shader->SetUniform3f("boundMax", position + volumeSize / 2.0f);

		shader->SetUniform1f("alphaThreshold", alphaThreshold);
		shader->SetUniform1f("minDensity", minDensity);
		shader->SetUniform1f("opacity", opacity);
		
		shader->SetUniform1f("zNear", camera.getNearPlaneDistance());
		shader->SetUniform1f("zFar", camera.getFarPlaneDistance());

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}

	void VolumeRenderer::setPosition(glm::vec3 position) {
		this->position = position;
	}

	void VolumeRenderer::setScale(glm::vec3 scale) {
		this->scale = scale;
	}

	void VolumeRenderer::setRotation(glm::vec3 rotation) {
		this->rotation = rotation;
	}

	glm::vec3 VolumeRenderer::getPosition() {
		return position;
	}

	glm::vec3 VolumeRenderer::getScale() {
		return scale;
	}

	glm::vec3 VolumeRenderer::getRotation() {
		return rotation;
	}

	void VolumeRenderer::setNoiseLayers(std::vector<NoiseLayer>& layers) {
		this->noiseLayers = layers;
	}

	std::vector<NoiseLayer>& VolumeRenderer::getNoiseLayers() {
		return noiseLayers;
	}

	void VolumeRenderer::regenerateVolumeTexture() {

	}

	void VolumeRenderer::recalculateLightData() {

	}

	uint32_t VolumeRenderer::getVirtualTexSize() {
		return virtualTextureSize;
	}

	void VolumeRenderer::setVirtualTexSize(uint32_t texSize) {
		if(texSize > 8 && texSize < 2000)
			virtualTextureSize = texSize;
	}

	void VolumeRenderer::setVolumeSize(glm::vec3 volumeSize) {
		this->volumeSize = volumeSize;
	}

	glm::vec3 VolumeRenderer::getVolumeSize() {
		return volumeSize;
	}

	void VolumeRenderer::setTextureFitSize(glm::vec3 fitSize) {
		textureFitSize = fitSize;
	}

	glm::vec3 VolumeRenderer::getTextureFitSize() {
		return textureFitSize;
	}

	void VolumeRenderer::setMinDensity(float density) {
		minDensity = density;
	}

	void VolumeRenderer::setMaxDensity(float density) {
		maxDensity = density;
	}

	float VolumeRenderer::getMinDensity() {
		return minDensity;
	}

	float VolumeRenderer::getMaxDensity() {
		return maxDensity;
	}

	void VolumeRenderer::setStepSize(float stepSize) {
		this->stepSize = stepSize;
	}

	float VolumeRenderer::getStepSize() {
		return stepSize;
	}

	void VolumeRenderer::setOpacity(float opacity) {
		this->opacity;
	}

	float VolumeRenderer::getOpacity() {
		return opacity;
	}

	void VolumeRenderer::setLightMarchStepSize(float stepSize) {
		lightMarchStepSize = stepSize;
	}

	void VolumeRenderer::setLightBaseIntensity(float baseIntensity) {
		lightBaseIntensity = baseIntensity;
	}

	void VolumeRenderer::setLightAbsorptionCoefficient(float absorption) {
		lightAbsorptionCoefficient = absorption;
	}

	float VolumeRenderer::getLightMarchStepSize() {
		return lightMarchStepSize;
	}

	float VolumeRenderer::getLightBaseIntensity() {
		return lightBaseIntensity;
	}

	float VolumeRenderer::getLightAbsorptionCoefficient() {
		return lightAbsorptionCoefficient;
	}

	void VolumeRenderer::setLightDirection(glm::vec3 direction) {
		lightDirection = direction;
	}

	void VolumeRenderer::setScreenSize(glm::vec2 screenSize) {
		this->screenSize = screenSize;
	}

	void VolumeRenderer::DrawPropertiesWindow() {

	}

	void VolumeRenderer::DrawBoundingBox() {

	}
}