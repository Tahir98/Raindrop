#pragma once
#include "glad/glad.h"

namespace Engine {
	enum CullMode {
		CullFront = 0, CullBack = 1, CullBoth
	};

	enum DepthMode {
		NEVER = 0, ALWAYS = 1, LESS = 2, LEQUAL = 3, EQUAL = 4, GREATER = 5, GEQUAL = 6, NOTEQUAL = 7
	};

	enum BlendFunction {
		ZERO = 0, ONE = 1,
		SRC_COLOR = 2, ONE_MINUS_SRC_COLOR = 3,
		DST_COLOR = 4, ONE_MINUS_DST_COLOR = 5,
		SRC_ALPHA = 6, ONE_MINUS_SRC_ALPHA = 7,
		DST_ALPHA = 8, ONE_MINUS_DST_ALPHA = 9,
		CONSTANT_COLOR = 10, ONE_MINUS_CONSTANT_COLOR = 11,
		CONSTANT_ALPHA = 12, ONE_MINUS_CONSTANT_ALPHA = 13,
		SRC_ALPHA_SATURATE = 14
	};

	class OpenGLUtility {
	public:
		static void EnableBlend(bool setActive = true) {
			if (setActive)
				glEnable(GL_BLEND);
			else
				glDisable(GL_BLEND);
		}

		static void EnableDepthTest(bool setActive = true) {
			if (setActive)
				glEnable(GL_DEPTH_TEST);
			else
				glDisable(GL_DEPTH_TEST);
		}

		static void EnableCulling(bool setActive = true) {
			if (setActive)
				glEnable(GL_CULL_FACE);
			else
				glDisable(GL_CULL_FACE);
		}

		static void SetCullMode(CullMode mode) {
			switch (mode)
			{
			case Engine::CullFront:
				glCullFace(GL_FRONT);
				break;
			case Engine::CullBack:
				glCullFace(GL_BACK);
				break;
			case Engine::CullBoth:
				glCullFace(GL_FRONT_AND_BACK);
				break;
			}
		}

		static void SetDepthMode(DepthMode mode) {
			switch (mode)
			{
			case Engine::NEVER:
				glDepthFunc(GL_NEVER);
				break;
			case Engine::ALWAYS:
				glDepthFunc(GL_ALWAYS);
				break;
			case Engine::LESS:
				glDepthFunc(GL_LESS);
				break;
			case Engine::LEQUAL:
				glDepthFunc(GL_LEQUAL);
				break;
			case Engine::EQUAL:
				glDepthFunc(GL_EQUAL);
				break;
			case Engine::GREATER:
				glDepthFunc(GL_GREATER);
				break;
			case Engine::GEQUAL:
				glDepthFunc(GL_GEQUAL);
				break;
			case Engine::NOTEQUAL:
				glDepthFunc(GL_NOTEQUAL);
				break;
			}
		}

		static void SetBlendFunction(BlendFunction source, BlendFunction destination) {
			glBlendFunc(GetOpenGLBlendFunctionValue(source), GetOpenGLBlendFunctionValue(destination));
		}

		static GLenum GetOpenGLBlendFunctionValue(BlendFunction function) {
			switch (function) {
			case Engine::ZERO: return GL_ZERO;
			case Engine::ONE: return GL_ONE;
			case Engine::SRC_COLOR: return GL_SRC_COLOR;
			case Engine::ONE_MINUS_SRC_COLOR: return GL_ONE_MINUS_SRC_COLOR;
			case Engine::DST_COLOR: return GL_DST_COLOR;
			case Engine::ONE_MINUS_DST_COLOR: return GL_ONE_MINUS_DST_COLOR;
			case Engine::SRC_ALPHA: return GL_SRC_ALPHA;
			case Engine::ONE_MINUS_SRC_ALPHA: return GL_ONE_MINUS_SRC_ALPHA;
			case Engine::DST_ALPHA: return GL_DST_ALPHA;
			case Engine::ONE_MINUS_DST_ALPHA: return GL_ONE_MINUS_DST_ALPHA;
			case Engine::CONSTANT_COLOR: return GL_CONSTANT_COLOR;
			case Engine::ONE_MINUS_CONSTANT_COLOR: return GL_ONE_MINUS_CONSTANT_COLOR;
			case Engine::CONSTANT_ALPHA: return GL_CONSTANT_ALPHA;
			case Engine::ONE_MINUS_CONSTANT_ALPHA: return GL_ONE_MINUS_CONSTANT_ALPHA;
			case Engine::SRC_ALPHA_SATURATE: return GL_SRC_ALPHA_SATURATE;
			}

			return GL_ZERO;
		}

	};

}