#include "Log.h"

namespace Engine {

	std::shared_ptr<spdlog::logger> Log::engineLogger;
	std::shared_ptr<spdlog::logger> Log::appLogger;
   
	void Log::init() {
		engineLogger = spdlog::stdout_color_mt("Engine");
		engineLogger->set_pattern("%^[%H:%M:%S] [%n] %v%$");
		engineLogger->set_level(spdlog::level::trace);

		appLogger = spdlog::stdout_color_mt("Application");
		appLogger->set_pattern("%^[%H:%M:%S] [%n] %v%$");
		appLogger->set_level(spdlog::level::trace);
	}

}