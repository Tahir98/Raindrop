#include "PostProcess.h"


namespace Engine {
	PostProcess::PostProcess(std::string shaderPath) {
		std::vector<glm::vec2> vertices = {
			glm::vec2(-1,-1), glm::vec2(0,0),
			glm::vec2( 1,-1), glm::vec2(1,0),
			glm::vec2( 1, 1), glm::vec2(1,1),

			glm::vec2(-1,-1), glm::vec2(0,0),
			glm::vec2( 1, 1), glm::vec2(1,1),
			glm::vec2(-1, 1), glm::vec2(0,1),
		};

		vb = new VertexBuffer(vertices.data(), sizeof(glm::vec2) * vertices.size(), GL_STATIC_DRAW);

		va = new VertexArray();
		va->PushElement(vb, 2, VertexArray::FLOAT, false);
		va->PushElement(vb, 2, VertexArray::FLOAT, false);

		shader = new Shader(shaderPath);

		rendererState.blendingEnabled = false;
		rendererState.cullingEnabled = false;
		rendererState.depthTestEnabled = false;
	}

	PostProcess::~PostProcess() {
		delete vb;
		delete va;
		delete shader;
	}

	void PostProcess::draw(FrameBuffer& fb) {
		OpenGLUtility::SetOpenGLState(rendererState);

		va->bind();
		shader->bind();

		uint32_t& colorTexID = fb.getColorAttachmentID();
		uint32_t& depthTexID = fb.getDepthAttachmentID();

		glBindTexture(GL_TEXTURE_2D, colorTexID);
		glActiveTexture(GL_TEXTURE0);

		glBindTexture(GL_TEXTURE_2D, depthTexID);
		glActiveTexture(GL_TEXTURE1);

		shader->SetUniform1i("ColorTex", 0);
		shader->SetUniform1i("DepthTex", 1);

		glDrawArrays(GL_TRIANGLES, 0, 6);
	}

	void PostProcess::draw(FrameBuffer& fb, PerspectiveCamera& camera) {
		OpenGLUtility::SetOpenGLState(rendererState);

		va->bind();
		shader->bind();

		uint32_t& colorTexID = fb.getColorAttachmentID();
		uint32_t& depthTexID = fb.getDepthAttachmentID();

		glBindTexture(GL_TEXTURE_2D, colorTexID);
		glActiveTexture(GL_TEXTURE0);

		glBindTexture(GL_TEXTURE_2D, depthTexID);
		glActiveTexture(GL_TEXTURE1);

		shader->SetUniform1i("ColorTex", 0);
		shader->SetUniform1i("DepthTex", 1);

		shader->SetUniform1f("zNear", camera.getNearPlaneDistance());
		shader->SetUniform1f("zFar", camera.getFarPlaneDistance());

		glDrawArrays(GL_TRIANGLES, 0, 6);
	}

}

