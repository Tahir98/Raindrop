#pragma once

#include "OpenGL/VertexArray.h"
#include "OpenGL/VertexBuffer.h"
#include "OpenGL/IndexBuffer.h"
#include "OpenGL/Shader.h"
#include "OpenGL/OpenGLUtility.h"

#include "Camera/PerspectiveCamera.h"
#include "Color.h"

namespace Engine {

	class LineRenderer {
	private:
		VertexArray* va = nullptr;
		VertexBuffer* vb = nullptr;
		Shader* shader2d = nullptr;
		Shader* shader3d = nullptr;

		Color color = Colors::White;
		float lineWidth = 2.0f;
		glm::vec2 screenSize = glm::vec2(1280, 720);

		OpenGLState rendererState2d;
		OpenGLState rendererState3d;

		const uint32_t bufferSize = 1000000; //1 million vertices
	public:
		LineRenderer();
		~LineRenderer();

		void draw2D(const std::vector<glm::vec2>& points, bool line_strip = true, bool loop = false);
		void draw3D(const std::vector<glm::vec3>& points, PerspectiveCamera& camera, bool line_strip = true, bool loop = false);
		void drawBoundingBox(glm::vec3 min, glm::vec3 max, PerspectiveCamera& camera);

		void setLineWidth(float width);
		void setColor(Color color);

		void setScreenSize(glm::vec2 screenSize);

		void enableDepthTest();
		void disableDepthTest();
	};


}