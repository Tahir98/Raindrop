#include "Texture1D.h"

namespace Engine {
    Texture1D::Texture1D(uint32_t width, TextureFormat format) : width(width), format(format) {
        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_1D, id);

        SetTextureFilter(filter);
        SetTextureWrapMode(wrapper);

        bbp = TextureUtility::GetTextureFormatStride(format);

        glTexImage1D(GL_TEXTURE_1D, 0, TextureUtility::GetOpenGLInternalFormat(format), width, 0,
            TextureUtility::GetOpenGLBaseFormat(format), TextureUtility::GetOpenGLPixelDataType(format), nullptr);

        glBindTexture(GL_TEXTURE_1D, 0);

        ENG_LOG_INFO("1D Texture created, id:{0}, width:{1}, bbp:{3}", id, width, bbp);
    }

    Texture1D::Texture1D(uint32_t width, TextureFormat format, TextureFilter filter) : width(width), format(format), filter(filter) {
        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_1D, id);

        SetTextureFilter(filter);
        SetTextureWrapMode(wrapper);

        bbp = TextureUtility::GetTextureFormatStride(format);

        glTexImage1D(GL_TEXTURE_1D, 0, TextureUtility::GetOpenGLInternalFormat(format), width, 0,
            TextureUtility::GetOpenGLBaseFormat(format), TextureUtility::GetOpenGLPixelDataType(format), nullptr);

        glBindTexture(GL_TEXTURE_1D, 0);

        ENG_LOG_INFO("1D Texture created, id:{0}, width:{1}, bbp:{3}", id, width, bbp);
    }

    Texture1D::Texture1D(uint32_t width, TextureFormat format, TextureFilter filter, TextureWrapper wrapper) : width(width), format(format), filter(filter), wrapper(wrapper) {
        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_1D, id);

        SetTextureFilter(filter);
        SetTextureWrapMode(wrapper);

        bbp = TextureUtility::GetTextureFormatStride(format);

        glTexImage1D(GL_TEXTURE_1D, 0, TextureUtility::GetOpenGLInternalFormat(format), width, 0,
            TextureUtility::GetOpenGLBaseFormat(format), TextureUtility::GetOpenGLPixelDataType(format), nullptr);

        glBindTexture(GL_TEXTURE_1D, 0);

        ENG_LOG_INFO("1D Texture created, id:{0}, width:{1}, bbp:{3}", id, width, bbp);
    }

    Texture1D::Texture1D(void* data, uint32_t width, TextureFormat format) : width(width), format(format) {
        if (data) {
            glGenTextures(1, &id);
            glBindTexture(GL_TEXTURE_1D, id);

            SetTextureFilter(filter);
            SetTextureWrapMode(wrapper);

            bbp = TextureUtility::GetTextureFormatStride(format);

            glTexImage1D(GL_TEXTURE_1D, 0, TextureUtility::GetOpenGLInternalFormat(format), width, 0,
                TextureUtility::GetOpenGLBaseFormat(format), TextureUtility::GetOpenGLPixelDataType(format), data);

            glBindTexture(GL_TEXTURE_1D, 0);

            ENG_LOG_INFO("1D Texture created, id:{0}, width:{1}, bbp:{3}", id, width, bbp);
        }
        else {
            ENG_LOG_ERROR("Texture1D, given data pointer is null");
        }
    }

    Texture1D::Texture1D(void* data, uint32_t width, TextureFormat format, TextureFilter filter) : width(width), format(format), filter(filter) {
        if (data) {
            glGenTextures(1, &id);
            glBindTexture(GL_TEXTURE_1D, id);

            SetTextureFilter(filter);
            SetTextureWrapMode(wrapper);

            bbp = TextureUtility::GetTextureFormatStride(format);

            glTexImage1D(GL_TEXTURE_1D, 0, TextureUtility::GetOpenGLInternalFormat(format), width, 0,
                TextureUtility::GetOpenGLBaseFormat(format), TextureUtility::GetOpenGLPixelDataType(format), data);

            glBindTexture(GL_TEXTURE_1D, 0);

            ENG_LOG_INFO("1D Texture created, id:{0}, width:{1}, bbp:{3}", id, width, bbp);
        }
        else {
            ENG_LOG_ERROR("Texture1D, given data pointer is null");
        }
    }

    Texture1D::Texture1D(void* data, uint32_t width, TextureFormat format, TextureFilter filter, TextureWrapper wrapper) : width(width), format(format), filter(filter), wrapper(wrapper) {
        if (data) {
            glGenTextures(1, &id);
            glBindTexture(GL_TEXTURE_1D, id);

            SetTextureFilter(filter);
            SetTextureWrapMode(wrapper);

            bbp = TextureUtility::GetTextureFormatStride(format);

            glTexImage1D(GL_TEXTURE_1D, 0, TextureUtility::GetOpenGLInternalFormat(format), width, 0,
                TextureUtility::GetOpenGLBaseFormat(format), TextureUtility::GetOpenGLPixelDataType(format), data);

            glBindTexture(GL_TEXTURE_1D, 0);

            ENG_LOG_INFO("1D Texture created, id:{0}, width:{1}, bbp:{3}", id, width, bbp);
        }
        else {
            ENG_LOG_ERROR("Texture1D, given data pointer is null");
        }
    }

    Texture1D::~Texture1D() {
        if (id != 0) {
            glDeleteTextures(1, &id);

            ENG_LOG_INFO("1D Texture deleted, id:{0}, width:{1}, bbp:{3}", id, width, bbp);
        }
    }

    void Texture1D::SetData(void* data, uint32_t size, uint32_t startIndex) {
        if (id != 0) {
            int32_t previouslyBindedTexture;
            glGetIntegerv(GL_TEXTURE_BINDING_1D, &previouslyBindedTexture);

            glBindTexture(GL_TEXTURE_1D, id);

            glTexSubImage1D (GL_TEXTURE_1D, 0, startIndex, width, TextureUtility::GetOpenGLBaseFormat(format), TextureUtility::GetOpenGLPixelDataType(format), data);

            glBindTexture(GL_TEXTURE_1D, (uint32_t)previouslyBindedTexture);
        }
    }

    void Texture1D::Resize(uint32_t width) {
        this->width = width;

        bind();

        glTexImage1D(GL_TEXTURE_1D, 0, TextureUtility::GetOpenGLInternalFormat(format), width, 0,
            TextureUtility::GetOpenGLBaseFormat(format), TextureUtility::GetOpenGLPixelDataType(format), nullptr);
    }

    void Texture1D::bind() {
        glBindTexture(GL_TEXTURE_1D, id);
    }

    void Texture1D::unbind() {
        glBindTexture(GL_TEXTURE_1D, 0);
    }

    void Texture1D::setActiveTextureSlot(int slot) {
        glActiveTexture(GL_TEXTURE0 + slot);
    }

    uint32_t Texture1D::getID() {
        return id;
    }

    uint32_t Texture1D::getWidth() {
        return width;
    }

    uint32_t Texture1D::getBBP() {
        return bbp;
    }

    TextureFormat Texture1D::getTextureFormat() {
        return format;
    }

    TextureFilter Texture1D::getTextureFilter() {
        return filter;
    }

    TextureWrapper Texture1D::getWrapMode() {
        return wrapper;
    }

    void Texture1D::SetTextureFilter(TextureFilter filter) {
        this->filter = filter;

        if (id != 0) {
            int32_t previouslyBindedTexture;
            glGetIntegerv(GL_TEXTURE_BINDING_1D, &previouslyBindedTexture);

            glBindTexture(GL_TEXTURE_1D, id);

            switch (filter) {
            case TextureFilter::POINT:
                glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
                glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
                break;
            case TextureFilter::BILINEAR:
                glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                break;
            case TextureFilter::TRILINEAR:
                glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                break;
            }

            glBindTexture(GL_TEXTURE_1D, (uint32_t)previouslyBindedTexture);
        }
    }

    void Texture1D::SetTextureWrapMode(TextureWrapper wrapper) {
        this->wrapper = wrapper;

        if (id != 0) {
            int32_t previouslyBindedTexture;
            glGetIntegerv(GL_TEXTURE_BINDING_1D, &previouslyBindedTexture);

            glBindTexture(GL_TEXTURE_1D, id);

            switch (wrapper)
            {
            case Engine::CLAMP:
                glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                break;
            case Engine::MIRROR:
                glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
                break;
            case Engine::REPEAT:
                glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_REPEAT);
                break;
            }

            glBindTexture(GL_TEXTURE_1D, (uint32_t)previouslyBindedTexture);
        }
    }
}

