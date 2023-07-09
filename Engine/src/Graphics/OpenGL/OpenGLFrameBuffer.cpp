#include "OpenGLFrameBuffer.h"
#include "glad/glad.h"
#include "Log.h"

Engine::OpenGLFrameBuffer::OpenGLFrameBuffer(const uint32_t width, const uint32_t height) : width(width), height(height) {
    //Frame buffer object
    glGenFramebuffers(1, &id);
    glBindFramebuffer(GL_FRAMEBUFFER, id);

    //Texture object
    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //texture attachment to frame buffer
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture_id, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    //Render buffer object
    glGenRenderbuffers(1, &renderbuffer_id);
    glBindRenderbuffer(GL_RENDERBUFFER, renderbuffer_id);

    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);

    //render buffer attachment to frame buffer
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderbuffer_id);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE) {
        ENG_LOG_INFO("Frame buffer is created, id: {0}, width: {1}, height: {2}", id, width, height);
    }
    else {
        ENG_LOG_ERROR("Failed to create frame buffer, id: {0}, width: {1}, height: {2}", id, width, height);
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

Engine::OpenGLFrameBuffer::~OpenGLFrameBuffer() {
    ENG_LOG_INFO("Frame buffer is deleted, id: {0}, width: {1}, height: {2}", id, width, height);
    glDeleteFramebuffers(1, &id);
    glDeleteTextures(1, &texture_id);
    glDeleteRenderbuffers(1, &renderbuffer_id);
}

void Engine::OpenGLFrameBuffer::resize(const uint32_t width, const uint32_t height){
    this->width = width;
    this->height = height;
    
    //Color texture resizing
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, texture_id);

    //Render buffer resizing
    glBindRenderbuffer(GL_RENDERBUFFER, renderbuffer_id);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

uint32_t Engine::OpenGLFrameBuffer::getWidth()
{
    return width;
}

uint32_t Engine::OpenGLFrameBuffer::getHeight()
{
    return height;
}

void Engine::OpenGLFrameBuffer::clear(glm::vec3 color){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glClearColor(color.r, color.g, color.b, 1);
}

void Engine::OpenGLFrameBuffer::bind() {
    glBindFramebuffer(GL_FRAMEBUFFER, id);
    glViewport(0, 0, width, height);
}

void Engine::OpenGLFrameBuffer::unbind() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

uint32_t& Engine::OpenGLFrameBuffer::getID()
{
    return id;
}

uint32_t& Engine::OpenGLFrameBuffer::getTextureID()
{
    return texture_id;
}

uint32_t& Engine::OpenGLFrameBuffer::getRenderbufferID()
{
    return renderbuffer_id;
}
