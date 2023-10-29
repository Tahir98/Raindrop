#pragma once

#define LOG_INPUTS

#include "EntryPoint.h"
#include "Window/Window.h"
#include "Application.h"
#include "Log.h"

//Event Classes
#include "Input/InputHandler.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"
#include "Events/WindowEvent.h"

//OpenGL Classes
#include "OpenGL/IndexBuffer.h"
#include "OpenGL/Shader.h"
#include "OpenGL/VertexArray.h"
#include "OpenGL/VertexBuffer.h"
#include "OpenGL/FrameBuffer.h"
#include "OpenGL/OpenGLUtility.h"
#include "OpenGL/Texture1D.h"
#include "OpenGL/Texture2D.h"
#include "OpenGL/Texture3D.h"


//Scene system
#include "Scene/Scene.h"
#include "Scene/SceneManager.h"

//Camera Classes
#include "Camera/OrthographicCamera.h"
#include "Camera/PerspectiveCamera.h"

//Skybox
#include "Skybox/SpherecalSkybox.h"
#include "Skybox/CubeMapSkybox.h"

//ImGui
#include "imgui.h"

//Random Number Generators
#include "Random/AddWithCarry.h"
#include "Random/LaggedFibonacciGenerator.h"
#include "Random/LaggedFibonacciGenerator64.h"
#include "Random/MersenneTwister.h"
#include "Random/MersenneTwister64.h"
#include "Random/MultiplyWithCarry.h"
#include "Random/Xorshift.h"
#include "Random/Xorshift64.h"

//Noise Generators
#include "Noise/PerlinNoise2D.h"
#include "Noise/PerlinNoise3D.h"


//Utility
#include "Utility.h"



