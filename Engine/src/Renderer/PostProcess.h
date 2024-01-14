#pragma once
 
#include "OpenGL/VertexBuffer.h"
#include "OpenGL/VertexArray.h"
#include "OpenGL/Shader.h"
#include "OpenGL/FrameBuffer.h"
#include "OpenGL/OpenGLUtility.h"

#include "Camera/PerspectiveCamera.h"

namespace Engine {

	class PostProcess {
	protected:
		VertexBuffer* vb = nullptr;
		VertexArray* va = nullptr;
		Shader* shader = nullptr;

		OpenGLState rendererState;
	public:
		PostProcess(std::string shaderPath);
		~PostProcess();
		virtual void draw(FrameBuffer& fb);
		virtual void draw(FrameBuffer& fb, PerspectiveCamera& camera);
	};

}