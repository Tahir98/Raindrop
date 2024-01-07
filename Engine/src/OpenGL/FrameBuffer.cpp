#include "FrameBuffer.h"
#include "glad/glad.h"
#include "Log.h"

Engine::FrameBuffer::FrameBuffer(const uint32_t width, const uint32_t height) : width(width), height(height) {
    //Frame buffer object
    glGenFramebuffers(1, &id);
    glBindFramebuffer(GL_FRAMEBUFFER, id);

    createAttachmentObjects();
   
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

Engine::FrameBuffer::FrameBuffer(const uint32_t width, const uint32_t height, AttachmentType colorAttachmentType, AttachmentType depthAttachmentType, bool createStencilBuffer) :
    width(width), height(height), colorAttachmentType(colorAttachmentType), depthAttachmentType(depthAttachmentType), stencilBufferExist(createStencilBuffer) {
    //Frame buffer object
    glGenFramebuffers(1, &id);
    glBindFramebuffer(GL_FRAMEBUFFER, id);

    createAttachmentObjects();

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

Engine::FrameBuffer::~FrameBuffer() {
    ENG_LOG_INFO("Frame buffer is deleted, id: {0}, width: {1}, height: {2}", id, width, height);
    glDeleteFramebuffers(1, &id);
    if(colorAttachmentType == Texture)
        glDeleteTextures(1, &colorTexID);
    else 
        glDeleteRenderbuffers(1, &colorRenderbufferID);
    
    if(depthAttachmentType == Texture)
        glDeleteTextures(1, &depthTexID);
    else 
        glDeleteRenderbuffers(1, &depthRenderbufferID);
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
    else {
        glBindRenderbuffer(GL_RENDERBUFFER, colorRenderbufferID);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA8, width, height);
        glBindRenderbuffer(GL_RENDERBUFFER, 0);
    }

    //Render buffer resizing
    if (depthAttachmentType == Texture) {
        glBindTexture(GL_TEXTURE_2D, depthTexID);

        if (stencilBufferExist)
            glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH32F_STENCIL8, width, height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_BYTE, NULL);
        else
            glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, width, height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, NULL);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glBindTexture(GL_TEXTURE_2D, 0);
    }
    else {
        glBindRenderbuffer(GL_RENDERBUFFER, depthRenderbufferID);
        
        if(stencilBufferExist)
            glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH32F_STENCIL8, width, height);
        else 
            glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT32, width, height);

        glBindRenderbuffer(GL_RENDERBUFFER, 0);
    }
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

bool Engine::FrameBuffer::hasStencilBuffer() {
    return stencilBufferExist;
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
        glGenRenderbuffers(1, &colorRenderbufferID);
        glBindRenderbuffer(GL_RENDERBUFFER, colorRenderbufferID);

        glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA8, width, height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, colorRenderbufferID);

        glBindRenderbuffer(GL_RENDERBUFFER, 0);
    }


    if (depthAttachmentType == Texture) {
        glGenTextures(1, &depthTexID);
        glBindTexture(GL_TEXTURE_2D, depthTexID);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        if (stencilBufferExist)
            glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH32F_STENCIL8, width, height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_BYTE, NULL);
        else 
            glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, width, height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, NULL);

        //texture attachment to frame buffer
        if(stencilBufferExist)
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, depthTexID, 0);
        else 
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTexID, 0);

        glBindTexture(GL_TEXTURE_2D, 0);
    }
    else {
        //Render buffer object
        glGenRenderbuffers(1, &depthRenderbufferID);
        glBindRenderbuffer(GL_RENDERBUFFER, depthRenderbufferID);

        if(stencilBufferExist) 
            glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH32F_STENCIL8, width, height);
        else 
            glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT32F, width, height);

        //render buffer attachment to frame buffer

        if(stencilBufferExist)
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, depthRenderbufferID);
        else 
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthRenderbufferID);

        glBindRenderbuffer(GL_RENDERBUFFER, 0);
    }


    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE) {
        ENG_LOG_INFO("Frame buffer is created, id: {0}, width: {1}, height: {2}", id, width, height);
    }
    else {
        ENG_LOG_ERROR("Failed to create frame buffer, id: {0}, width: {1}, height: {2}", id, width, height);
    }
}


