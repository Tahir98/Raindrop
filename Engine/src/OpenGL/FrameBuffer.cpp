#include "FrameBuffer.h"
#include "glad/glad.h"
#include "Log.h"

Engine::FrameBuffer::FrameBuffer(const uint32_t width, const uint32_t height) : width(width), height(height) {
    //Frame buffer object
    glGenFramebuffers(1, &id);
    glBindFramebuffer(GL_FRAMEBUFFER, id);

    createAttachmentObjects();
   
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    created = true;
}

Engine::FrameBuffer::FrameBuffer(const uint32_t width, const uint32_t height, AttachmentType colorAttachmentType, AttachmentType depthAttachmentType, 
    AttachmentType stencilAttachmentType) : width(width), height(height), colorAttachmentType(colorAttachmentType), 
    depthAttachmentType(depthAttachmentType), stencilAttachmentType(stencilAttachmentType) {
    //Frame buffer object
    glGenFramebuffers(1, &id);
    glBindFramebuffer(GL_FRAMEBUFFER, id);

    createAttachmentObjects();

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    created = true;
}

Engine::FrameBuffer::~FrameBuffer() {
    ENG_LOG_INFO("Frame buffer is deleted, id: {0}, width: {1}, height: {2}", id, width, height);

    release();

    glDeleteFramebuffers(1, &id);
}

void Engine::FrameBuffer::resize(const uint32_t width, const uint32_t height){
    this->width = width;
    this->height = height;
    
    //Color attachment resizing
    if (colorAttachmentType == Texture) {
        glBindTexture(GL_TEXTURE_2D, colorTexID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glBindTexture(GL_TEXTURE_2D, 0);
    }
    else {//Render buffer resizing
        glBindRenderbuffer(GL_RENDERBUFFER, colorRenderbufferID);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA8, width, height);
        glBindRenderbuffer(GL_RENDERBUFFER, 0);
    }

  
    if (depthAttachmentType == Texture) {
        glBindTexture(GL_TEXTURE_2D, depthTexID);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, width, height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, NULL);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glBindTexture(GL_TEXTURE_2D, 0);
    }
    else {
        glBindRenderbuffer(GL_RENDERBUFFER, depthRenderbufferID);
        
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT32, width, height);

        glBindRenderbuffer(GL_RENDERBUFFER, 0);
    }

    //if (stencilAttachmentType == Texture) {
    //    glBindTexture(GL_TEXTURE_2D, stencilTexID);
    //
    //    glTexImage2D(GL_TEXTURE_2D, 0, GL_STENCIL_INDEX8, width, height, 0, GL_STENCIL_INDEX, GL_UNSIGNED_BYTE, NULL);
    //
    //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    //
    //    glBindTexture(GL_TEXTURE_2D, 0);
    //}
    //else {
    //    glBindRenderbuffer(GL_RENDERBUFFER, stencilRenderbufferID);
    //
    //    glRenderbufferStorage(GL_RENDERBUFFER, GL_STENCIL_INDEX8, width, height);
    //
    //    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    //}
}

void Engine::FrameBuffer::release() {
    if (colorAttachmentType == Texture) {
        glDeleteTextures(1, &colorTexID);
        colorTexID = 0;
    }
    else {
        glDeleteRenderbuffers(1, &colorRenderbufferID);
        colorRenderbufferID = 0;
    }

    if (depthAttachmentType == Texture) {
        glDeleteTextures(1, &depthTexID);
        depthTexID = 0;
    }
    else {
        glDeleteRenderbuffers(1, &depthRenderbufferID);
        depthRenderbufferID = 0;
    }

    //f (stencilAttachmentType == Texture) {
    //   glDeleteTextures(1, &stencilTexID);
    //   stencilTexID = 0;
    //
    //lse {
    //   glDeleteRenderbuffers(1, &stencilRenderbufferID);
    //   stencilRenderbufferID = 0;
    //

    created = false;
}

bool Engine::FrameBuffer::isCreated() {
    return created;
}

uint32_t Engine::FrameBuffer::getWidth()
{
    return width;
}

uint32_t Engine::FrameBuffer::getHeight()
{
    return height;
}

void Engine::FrameBuffer::clear(glm::vec3 color){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glClearColor(color.r, color.g, color.b, 1);
}

void Engine::FrameBuffer::bind() {
    glBindFramebuffer(GL_FRAMEBUFFER, id);
    glViewport(0, 0, width, height);
}

void Engine::FrameBuffer::unbind() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

uint32_t& Engine::FrameBuffer::getID()
{
    return id;
}

uint32_t& Engine::FrameBuffer::getColorAttachmentID() {
    if (colorAttachmentType == AttachmentType::Texture)
        return colorTexID;
    else
        return colorRenderbufferID;
}

uint32_t& Engine::FrameBuffer::getDepthAttachmentID() {
    if (depthAttachmentType == AttachmentType::Texture)
        return depthTexID;
    else
        return depthRenderbufferID;
}

uint32_t& Engine::FrameBuffer::getStencilAttachmentID() {
    if (stencilAttachmentType == AttachmentType::Texture)
        return stencilTexID;
    else       
        return stencilRenderbufferID;
}

void Engine::FrameBuffer::createAttachmentObjects() {
    if (colorAttachmentType == Texture) {
        //Color texture object
        glGenTextures(1, &colorTexID);
        glBindTexture(GL_TEXTURE_2D, colorTexID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        //texture attachment to frame buffer
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorTexID, 0);

        glBindTexture(GL_TEXTURE_2D, 0);
    }
    else {
        //Color render buffer object
        glGenRenderbuffers(1, &colorRenderbufferID);
        glBindRenderbuffer(GL_RENDERBUFFER, colorRenderbufferID);

        glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA8, width, height);

        //render buffer attachment to the frame buffer
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, colorRenderbufferID);

        glBindRenderbuffer(GL_RENDERBUFFER, 0);
    }


    if (depthAttachmentType == Texture) {
        //Depth texture object
        glGenTextures(1, &depthTexID);
        glBindTexture(GL_TEXTURE_2D, depthTexID);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, width, height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, NULL);

        //texture attachment to frame buffer
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTexID, 0);

        glBindTexture(GL_TEXTURE_2D, 0);
    }
    else {
        //Render buffer object
        glGenRenderbuffers(1, &depthRenderbufferID);
        glBindRenderbuffer(GL_RENDERBUFFER, depthRenderbufferID);

        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH32F_STENCIL8, width, height);

        //render buffer attachment to the frame buffer
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthRenderbufferID);

        glBindRenderbuffer(GL_RENDERBUFFER, 0);
    }

    //if (stencilAttachmentType == Texture) {
    //    //Stencil texture object
    //    glGenTextures(1, &stencilTexID);
    //    glBindTexture(GL_TEXTURE_2D, stencilTexID);
    //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    //
    //    glTexImage2D(GL_TEXTURE_2D, 0, GL_STENCIL_INDEX, width, height, 0, GL_STENCIL_INDEX, GL_UNSIGNED_BYTE, nullptr);
    //
    //    //texture attachment to frame buffer
    //    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_TEXTURE_2D, stencilTexID, 0);
    //
    //    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    //}
    //else {
    //    //Render buffer object
    //    glGenRenderbuffers(1, &stencilRenderbufferID);
    //    glBindRenderbuffer(GL_RENDERBUFFER, stencilRenderbufferID);
    //
    //    glRenderbufferStorage(GL_RENDERBUFFER, GL_STENCIL_INDEX8, width, height);
    //
    //    //render buffer attachment to the frame buffer
    //    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, stencilRenderbufferID);
    //
    //    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    //}


    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE) {
        ENG_LOG_INFO("Frame buffer is created, id: {0}, width: {1}, height: {2}", id, width, height);
    }
    else {
        ENG_LOG_ERROR("Failed to create frame buffer, id: {0}, width: {1}, height: {2}", id, width, height);
    }
}

//https://stackoverflow.com/questions/37506460/opengl-framebuffer-separate-stencil-texture

