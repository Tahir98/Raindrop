#include "VolumeRenderer.h"


namespace Engine {
	VolumeRenderer::VolumeRenderer() {

	}

	VolumeRenderer::~VolumeRenderer() {

	}

	bool VolumeRenderer::init() {
		return true;
	}

	void VolumeRenderer::dispose() {

	}

	void VolumeRenderer::update(float delta) {

	}

	void VolumeRenderer::draw(PerspectiveCamera& camera) {

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