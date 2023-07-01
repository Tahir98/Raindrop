#pragma once

#define LOG_INPUTS

#include "EntryPoint.h"
#include "Window/Window.h"
#include "Application.h"
#include "Log.h"

#include "Input/InputHandler.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"
#include "Events/WindowEvent.h"

//OpenGL Classes
#include "OpenGL/IndexBuffer.h"
#include "OpenGL/Shader.h"
#include "OpenGL/VertexArray.h"
#include "OpenGL/VertexBuffer.h"
#include "OpenGL/Texture.h"
#include "OpenGL/FrameBuffer.h"

//Scene system
#include "Scene/Scene.h"
#include "Scene/SceneManager.h"

//Camera Classes
#include "Camera/OrthographicCamera.h"
#include "Camera/PerspectiveCamera.h"

//Skybox
#include "Skybox/SpherecalSkybox.h"

//ImGui
#include "imgui.h"

//Random
#include "Random/AddWithCarry.h"
#include "Random/LaggedFibonacciGenerator.h"
#include "Random/LaggedFibonacciGenerator64.h"
#include "Random/MersenneTwister.h"
#include "Random/MersenneTwister64.h"
#include "Random/MultiplyWithCarry.h"
#include "Random/Xorshift.h"
#include "Random/Xorshift64.h"