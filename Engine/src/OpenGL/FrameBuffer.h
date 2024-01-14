#pragma once
#include <utility>
#include "glm/glm.hpp"

namespace Engine {

	enum AttachmentType {
		Texture = 0,
		Renderbuffer = 1
	};

	class FrameBuffer {
	private:
		uint32_t id = 0;
		uint32_t colorTexID = 0;
		uint32_t colorRenderbufferID = 0;
		uint32_t depthTexID = 0;
		uint32_t depthRenderbufferID = 0;
		uint32_t stencilTexID =  0;
		uint32_t stencilRenderbufferID = 0;

		uint32_t width, height;
		
		AttachmentType colorAttachmentType = AttachmentType::Texture; 
		AttachmentType depthAttachmentType = AttachmentType::Renderbuffer;
		AttachmentType stencilAttachmentType = AttachmentType::Renderbuffer;

		bool created = false;

	public:
		FrameBuffer(const uint32_t width, const uint32_t height);
		FrameBuffer(const uint32_t width, const uint32_t height, AttachmentType colorAttachmentType = Texture, AttachmentType depthAttachmentType = Texture,
			AttachmentType stencilAttachmentType = Texture);
		~FrameBuffer();

		void resize(const uint32_t width, const uint32_t height);
		
		void release();
		bool isCreated();

		uint32_t getWidth();
		uint32_t getHeight();

		void clear(glm::vec3 color = glm::vec3(1,1,1));

		void bind();
		void unbind();

		uint32_t& getID();
		uint32_t& getColorAttachmentID();
		uint32_t& getDepthAttachmentID();
		uint32_t& getStencilAttachmentID();


	private:
		void createAttachmentObjects();
	};

}