#include "Window.h"
#include <iostream>
#include "Log.h"
#include "Input/InputHandler.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"
#include "Events/WindowEvent.h"

Engine::Window::Window(std::string name, uint32_t width, uint32_t height, bool fullscreen) {
    properties.name = name;
    properties.width = width;
    properties.height = height;

    if (glfwInit() != GLFW_TRUE) {
         ENG_LOG_ERROR("Failed to initialize GLFW");
        return;
    }

    ENG_LOG_INFO("GLFW is successfuly initialized");

    //TODO Window hints
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    if (fullscreen) {
        properties.nativeWindowPtr = glfwCreateWindow(width, height, name.c_str(), glfwGetPrimaryMonitor(), nullptr);
    }
    else {
        properties.nativeWindowPtr = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);
    }

    if (properties.nativeWindowPtr == nullptr) {
        glfwTerminate();
        ENG_LOG_ERROR("Failed to create window: {0}, ({1},{2})", name, width, height);

        return;
    }

    ENG_LOG_INFO("Window is created successfully: {0}, ({1},{2})", name, width, height);

    glfwMakeContextCurrent(properties.nativeWindowPtr);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        ENG_LOG_ERROR("Failed to initialize GLAD and OpenGL!!!");
        glfwTerminate();

        return;
    }

    glfwSetWindowUserPointer(properties.nativeWindowPtr, &properties);

    glViewport(0, 0, properties.width, properties.height);

    InputHandler::Init();

    AddCallbackFunctions();

    time_now = (float)glfwGetTime();
}

void Engine::Window::AddCallbackFunctions() {
    glfwSetKeyCallback(properties.nativeWindowPtr, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
        if (action == GLFW_PRESS) {
            KeyPressedEvent event(key);
#ifdef LOG_INPUTS
            ENG_LOG_INFO(event.getMessage());
#endif
        }
        else if (action == GLFW_REPEAT) {
            KeyRepeatedEvent event(key);
#ifdef LOG_INPUTS
            ENG_LOG_INFO(event.getMessage());
#endif
        }
        if (action == GLFW_RELEASE) {
            KeyReleasedEvent event(key);
#ifdef LOG_INPUTS
            ENG_LOG_INFO(event.getMessage());
#endif
        }
    });

    glfwSetCursorPosCallback(properties.nativeWindowPtr, [](GLFWwindow* window, double xpos, double ypos) {
        MouseMovedEvent event((float)xpos, (float)ypos);

#ifdef LOG_INPUTS
        ENG_LOG_INFO(event.getMessage());
#endif
    });

    glfwSetScrollCallback(properties.nativeWindowPtr, [](GLFWwindow* window, double xoffset, double yoffset) {
        MouseScrolledEvent event((float)xoffset, (float) yoffset);

#ifdef LOG_INPUTS
        ENG_LOG_INFO(event.getMessage());
#endif
    });

    glfwSetMouseButtonCallback(properties.nativeWindowPtr, [](GLFWwindow* window, int button, int action, int mods) {
        if (action == GLFW_PRESS) {
            MouseButtonPressedEvent event(button);

#ifdef LOG_INPUTS
            ENG_LOG_INFO(event.getMessage());
#endif
        }
        else if (action == GLFW_RELEASE) {
            MouseButtonReleasedEvent event(button);

#ifdef LOG_INPUTS
            ENG_LOG_INFO(event.getMessage());
#endif
        }
    });

    glfwSetWindowCloseCallback(properties.nativeWindowPtr, [](GLFWwindow* window) {
        WindowClosedEvent event;

#ifdef LOG_INPUTS
        ENG_LOG_INFO(event.getMessage());
#endif
    });

    glfwSetWindowSizeCallback(properties.nativeWindowPtr, [](GLFWwindow* window, int width, int height) {
        WindowResizedEvent event(width, height);
    
#ifdef LOG_INPUTS
        ENG_LOG_INFO(event.getMessage());
#endif
    });

    glfwSetWindowPosCallback(properties.nativeWindowPtr, [](GLFWwindow* window, int xpos, int ypos) {
        WindowMovedEvent event(xpos, ypos);

#ifdef LOG_INPUTS
        ENG_LOG_INFO(event.getMessage());
#endif
    });

}

Engine::Window::~Window() {
    glfwDestroyWindow(properties.nativeWindowPtr);
    ENG_LOG_INFO("Window is destoryed: {0}, ({1},{2})", properties.name, properties.width, properties.height);
    glfwTerminate();

    ENG_LOG_INFO("GLFW is terminated");
}

GLFWwindow* Engine::Window::GetNativeWindowPtr() {
    return properties.nativeWindowPtr;
}

void Engine::Window::Update() {
    glClearColor(1, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    time_prev = time_now;
    time_now = (float)glfwGetTime();

    deltaTime = time_now - time_prev;

    glfwPollEvents();
}

void Engine::Window::PostEvents() {
    glfwSwapBuffers(properties.nativeWindowPtr);

    InputHandler::UpdateTemporaryBuffers();
}

float Engine::Window::GetDeltaTime()
{
    return deltaTime;
}

void Engine::Window::Resize(const uint32_t width, const uint32_t height) {
    properties.width = width;
    properties.height = height;

    glfwSetWindowSize(properties.nativeWindowPtr, width, height);
}

bool Engine::Window::ShouldClose()
{
    return glfwWindowShouldClose(properties.nativeWindowPtr);
}
