#include "LineRenderer.h"

namespace Engine {
    LineRenderer::LineRenderer() {
        va = new VertexArray();
        vb = new VertexBuffer(nullptr, sizeof(glm::vec3) * bufferSize, GL_DYNAMIC_DRAW);

        va->PushElement(vb, 3, VertexArray::FLOAT, false);

        shader2d = new Shader("Shaders/LineRenderer2D.shader");
        shader3d = new Shader("Shaders/LineRenderer3D.shader");

        rendererState2d.blendingEnabled = false;
        rendererState2d.depthTestEnabled = false;
        rendererState2d.cullingEnabled = false;
        
        rendererState3d.blendingEnabled = false;
        rendererState3d.depthTestEnabled = false;
        rendererState3d.cullingEnabled = false;
    }
    
    LineRenderer::~LineRenderer() {
        delete va;
        delete vb;
        delete shader2d;
        delete shader3d;
    }

    void LineRenderer::draw2D(const std::vector<glm::vec2>& points, bool line_strip, bool loop) {
        std::vector<glm::vec3> points3d;

        for (int i = 0; i < points.size() - 1; i++) {
            points3d.push_back(glm::vec3(points[i].x, points[i].y, 0));
        }

        int size = points.size() > bufferSize ? bufferSize : points.size();
        vb->SetData(points3d.data(), 0, size * sizeof(glm::vec3));

        va->bind();
        shader2d->bind();

        shader2d->SetUniform2f("screenSize", screenSize);
        shader2d->SetUniform4f("color", color);

        OpenGLUtility::SetOpenGLState(rendererState2d);

        glLineWidth(lineWidth);

        if (loop) {
            glDrawArrays(GL_LINE_LOOP, 0, points3d.size());
        }
        else {
            if (line_strip) {
                glDrawArrays(GL_LINE_STRIP, 0, points3d.size());
            }
            else {
                glDrawArrays(GL_LINES, 0, points3d.size());
            }
        }
    }

    void LineRenderer::draw3D(const std::vector<glm::vec3>& points, PerspectiveCamera& camera, bool line_strip, bool loop) {
        int size = points.size() > bufferSize ? bufferSize : points.size();

        vb->SetData(points.data(), 0, size * sizeof(glm::vec3));

        va->bind();
        shader3d->bind();

        shader3d->SetUniformMatrix4x4("view", 1, false, glm::value_ptr(camera.getViewMatrix()));
        shader3d->SetUniformMatrix4x4("projection", 1, false, glm::value_ptr(camera.getProjectionMatrix()));
        shader3d->SetUniform4f("color", color);

        OpenGLUtility::SetOpenGLState(rendererState3d);

        glLineWidth(lineWidth);

        if (loop) {
            glDrawArrays(GL_LINE_LOOP, 0, points.size());
        }
        else {
            if (line_strip) {
                glDrawArrays(GL_LINE_STRIP, 0, points.size());
            }
            else {
                glDrawArrays(GL_LINES, 0, points.size());
            }
        }
    }

    void LineRenderer::drawBoundingBox(glm::vec3 min, glm::vec3 max, PerspectiveCamera& camera) {
        glm::vec3 size = max - min;

        std::vector<glm::vec3> points = {
            min, min + glm::vec3(size.x, 0, 0),
            min, min + glm::vec3(0, 0, size.z),
            min + glm::vec3(size.x, 0, size.z), min + glm::vec3(size.x, 0, 0),
            min + glm::vec3(size.x, 0, size.z), min + glm::vec3(0, 0, size.z),

            max, max - glm::vec3(size.x, 0, 0),
            max, max - glm::vec3(0, 0, size.z),
            max - glm::vec3(size.x, 0, size.z), max - glm::vec3(size.x, 0, 0),
            max - glm::vec3(size.x, 0, size.z), max - glm::vec3(0, 0, size.z),

            min, min + glm::vec3(0, size.y, 0),
            min + glm::vec3(size.x, 0, 0), min + glm::vec3(size.x, size.y, 0),
            min + glm::vec3(size.x, 0, 0), min + glm::vec3(size.x, size.y, 0),
            min + glm::vec3(0, 0, size.z), min + glm::vec3(0, size.y, size.z),
            min + glm::vec3(size.x, 0, size.z), max
        };

        vb->SetData(points.data(), 0, points.size() * sizeof(glm::vec3));

        va->bind();
        shader3d->bind();

        shader3d->SetUniformMatrix4x4("view", 1, false, glm::value_ptr(camera.getViewMatrix()));
        shader3d->SetUniformMatrix4x4("projection", 1, false, glm::value_ptr(camera.getProjectionMatrix()));
        shader3d->SetUniform4f("color", color);

        OpenGLUtility::SetOpenGLState(rendererState3d);

        glLineWidth(lineWidth);
        glDrawArrays(GL_LINES, 0, points.size());
    }

    void LineRenderer::setLineWidth(float width) {
        lineWidth = glm::clamp<float>(width, 1, 100);
    }
    void LineRenderer::setColor(Color color) {
        this->color = color;
    }

    void LineRenderer::setScreenSize(glm::vec2 screenSize) {
        this->screenSize = screenSize;
    }

    void LineRenderer::enableDepthTest() {
        rendererState3d.depthTestEnabled = true;
    }
    void LineRenderer::disableDepthTest() {
        rendererState3d.depthTestEnabled = false;
    }
}