#pragma once
#include "glad/glad.h"

namespace Engine {
	enum CullMode {
		CullFront = 0, CullBack = 1, CullBoth
	};

	class OpenGLUtility {
	public:
		void EnableBlendMode(bool setActive = true) {
			if (setActive)
				glEnable(GL_BLEND);
			else
				glDisable(GL_BLEND);
		}

		void EnableDepthTest(bool setActive = true) {
			if (setActive)
				glEnable(GL_DEPTH_TEST);
			else
				glDisable(GL_DEPTH_TEST);
		}

		void EnableCulling(bool setActive = true) {
			if (setActive)
				glEnable(GL_CULL_FACE);
			else
				glDisable(GL_CULL_FACE);
		}

		void SetCullMode(CullMode mode) {
			if (mode == CullFront)
				glCullFace(GL_FRONT);
			else if (mode == CullBack)
				glCullFace(GL_BACK);
			else
				glCullFace(GL_FRONT_AND_BACK);
		}

	};


}