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

//Graphics Interface Classes
#include "Graphics/Interface/IndexBuffer.h"
#include "Graphics/Interface/Shader.h"
#include "Graphics/Interface/VertexArray.h"
#include "Graphics/Interface/VertexBuffer.h"
#include "Graphics/Interface/Texture.h"
#include "Graphics/Interface/FrameBuffer.h"

//Interface olmadan kullanılmak istenirse 
#ifdef GRAPHICS_API_OPENGL 
#include "Graphics/OpenGL/OpenGLIndexBuffer.h"
#include "Graphics/OpenGL/OpenGLShader.h"
#include "Graphics/OpenGL/OpenGLVertexArray.h"
#include "Graphics/OpenGL/OpenGLVertexBuffer.h"
#include "Graphics/OpenGL/OpenGLTexture.h"
#include "Graphics/OpenGL/OpenGLFrameBuffer.h"
#include "Graphics/OpenGL/OpenGLUtility.h"
#elif GRAPHICS_API_DIRECTX
//TODO Alperen
#endif 


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

//Noise
#include "Noise/PerlinNoise2D.h"
#include "Noise/PerlinNoise3D.h"


//Utility
#include "Utility.h"



