#pragma once
#include "Camera.h"

namespace Engine {
	class OrthographicCamera : public Camera {
	private:
		float left, right;
		float bottom, top;
		float _far, _near;

	public:
		OrthographicCamera(float left, float right, float bottom, float top, float near, float far) : 
			Camera(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0)),left(left), right(right), bottom(bottom), top(top), _near(near), _far(far){

			projection = glm::ortho(left, right, bottom, top, _near, _far);

			update();
		}
	};
}