#pragma once

#include "Scene.h"
#include <vector>

namespace Engine {
	class SceneManager {
		friend class Window;
	private:
		static std::vector<Scene*> scenes;
		static float delta;

		static void update(float delta) {
			SceneManager::delta = delta;

			if (scenes.size() > 0) {
				scenes[scenes.size() - 1]->OnUpate(delta);
			}
		}

	public:
		static void pushScene(Scene* scene) {
			for (int i = 0; i < scenes.size(); i++) {
				if (scene->getID() == scenes[i]->getID())
					return;
			}

			if (scenes.size() > 0) {
				scenes[scenes.size() - 1]->OnSuspend();
			}

			scenes.push_back(scene);
			scene->OnCreate();
		}

		static void popScene() {
			if (scenes.size() > 0) {
				scenes[scenes.size() - 1]->OnSuspend();
				scenes[scenes.size() - 1]->OnDestroy();

				scenes.pop_back();

				if (scenes.size() > 0)
					scenes[scenes.size() - 1]->OnResume();
			}
		}

		static void deleteScene(Scene* scene) {
			for (int i = 0; i < scenes.size(); i++) {
				if (scenes[i]->getID() == scene->getID()) {
					scene->OnSuspend();
					scene->OnDestroy();

					if (i == scenes.size() - 1) {
						scenes.pop_back();

						if (scenes.size() > 0)
							scenes[scenes.size() - 1]->OnResume();
					}
					else {
						scenes.erase(scenes.begin() + i);
					}
				}
			}
		}

		static void bringTopScene(Scene* scene) {
			for (int i = 0; i < scenes.size(); i++) {
				if (scenes[i]->getID() == scene->getID() && i != scenes.size() - 1) {
					scenes.erase(scenes.begin() + i);

					scenes[scenes.size() - 1]->OnSuspend();
					
					scenes.push_back(scene);
					scene->OnResume();
				}
			}
		}

		static void clearAll() {
			for (int i = 0; i < scenes.size(); i++) {
				scenes[i]->OnSuspend();
				scenes[i]->OnDestroy();
			}

			scenes.clear();
			scenes.shrink_to_fit();
		}

	};
}
