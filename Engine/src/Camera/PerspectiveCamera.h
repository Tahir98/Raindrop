#pragma once
#include "Camera.h"
#include "Log.h"

namespace Engine {
	class PerspectiveCamera : public Camera {
	private:
		float fovy;
		float aspectRatio;
		float nearPlane, farPlane;

	public:
		PerspectiveCamera(float fovy, float aspectRatio, float nearPlane, float farPlane) : Camera(glm::vec3(0,0,0), glm::vec3(0,0,0)), fovy(fovy), aspectRatio(aspectRatio), nearPlane(nearPlane), farPlane(farPlane) {

			projection = glm::perspective(glm::radians(fovy), aspectRatio, nearPlane, farPlane);

			update();
		}

		float getNearPlaneDistane() { return nearPlane; }
		float getFarPlaneDistane() { return farPlane; }
		float getFieldOfView() { return fovy; }
		
		glm::vec2 getFrustom() { return glm::vec2(nearPlane, farPlane); }

		float getAspectRatio() { return aspectRatio; }

		void setNearPlaneDistance(float nearPlane) {
			if (nearPlane <= 0.0f || nearPlane >= farPlane) {
				ENG_LOG_ERROR("Perspective Camera: near plane distance must be greater than zero and lower far plane distance");
				return;
			}


			this->nearPlane = nearPlane;
			projection = glm::perspective(glm::radians(fovy), aspectRatio, nearPlane, farPlane);
		}

		void setFarPlaneDistance(float farPlane) {
			if (farPlane <= nearPlane || farPlane >= 10000.0f) {
				ENG_LOG_ERROR("Perspective Camera: far plane distance must be greater than near plane distance and less than 10000");
				return;
			}


			this->farPlane = farPlane;
			projection = glm::perspective(glm::radians(fovy), aspectRatio, nearPlane, farPlane);
		}

		void setFieldOfView(float fovy) {
			if (fovy <= 0 || fovy >= 180) {
				ENG_LOG_ERROR("Perspective Camera: Field of view must be greater 0 and less than 180");
				return;
			}


			this->fovy = fovy;
			projection = glm::perspective(glm::radians(fovy), aspectRatio, nearPlane, farPlane);
		}
		
		void setAspectRatio(float ratio) {
			if (ratio <= 0) {
				ENG_LOG_ERROR("Perspective Camera: Aspect ratio mest be greater than 0");
				return;
			}

			aspectRatio = ratio;
			projection = glm::perspective(glm::radians(fovy), aspectRatio, nearPlane, farPlane);
		}

	};
}