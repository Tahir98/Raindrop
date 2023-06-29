#pragma once
#include "glm/glm.hpp"
#include "glm/ext.hpp"

namespace Engine {

	class Camera {
	protected:
		glm::vec3 position;
		glm::vec3 eulerAngles;
		glm::vec3 direction;

		glm::mat4 view;
		glm::mat4 projection;

	public:
		Camera(glm::vec3 position, glm::vec3 eulerAngles) : position(position), eulerAngles(eulerAngles) {
			eulerAngles.z = 0;

			view = glm::mat4(1.0f);
			projection = glm::mat4(1.0f);

			direction = glm::vec3(0, 0, -1);
		}

		void update() {
			eulerAngles.z = 0;

			direction = glm::vec3(0, 0, -1);

			direction.x = glm::cos(glm::radians(eulerAngles.x)) * glm::sin(glm::radians(eulerAngles.y));
			direction.y = glm::sin(glm::radians(eulerAngles.x));
			direction.z = glm::cos(glm::radians(eulerAngles.x)) * glm::cos(glm::radians(eulerAngles.y)) * -1.0f;

			view = glm::lookAt(position, position + direction, glm::vec3(0, 1, 0));
		}

		glm::mat4 getViewMatrix() { return view; }
		glm::mat4 getProjectionMatrix() { return projection; }

		glm::vec3 getPosition() { return position; }
		glm::vec3 getRotation() { return eulerAngles; }
		glm::vec3 getForward() { return direction; }

		glm::vec3 getRight() {
			glm::vec3 right = glm::cross(direction, glm::vec3(0, 1, 0));

			return right;
		}

		glm::vec3 getUp() {
			glm::vec3 right = getRight();

			glm::vec3 up = glm::cross(right, direction);

			return up;
		}

		void setPosition(glm::vec3 pos) {
			position = pos;
		}

		void translate(glm::vec3 translation) {
			position += translation;
		}

		void translate(float x, float y, float z) {
			position += glm::vec3(x, y, z);
		}

		void rotatePitch(float angle) {
			eulerAngles.x += angle;

			if (eulerAngles.x > 85 || eulerAngles.x < -85)
				eulerAngles.x = glm::fclamp(eulerAngles.x, -85.0f,85.0f);
		}

		void rotateYaw(float angle) {
			eulerAngles.y += angle;
		}

	};


}