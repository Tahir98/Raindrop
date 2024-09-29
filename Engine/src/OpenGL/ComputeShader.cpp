#include "ComputeShader.h"
#include <iostream>
#include <sstream>

namespace Engine {
	ComputeShader::ComputeShader(const std::string filePath) {
		std::ifstream file(filePath);

		if (!file.is_open()) {
			ENG_LOG_ERROR("Given shader file is not found: {0}", filePath);
			return;
		}

		std::vector<std::string> allLines;
		std::string line;

		//Read all lines
		while (std::getline(file, line)) {
			allLines.push_back(line);
		}

		int shaderStartIndex = -1;

		//Find kernel definitions
		for (uint32_t i = 0; i < allLines.size(); i++) {
			std::stringstream ss(allLines[i]);

			std::string s1, s2, s3;

			ss >> s1 >> s2 >> s3;

			if (s1.compare("#pragma") == 0 && s2.compare("kernel") == 0) {
				kernelNames.push_back(s3);

				shaderStartIndex = i + 1;
			}
		}

		for (uint32_t i = 0; i < kernelNames.size(); i++) {

			std::string cs_string = "";

			bool kernelFunctionFound = false;

			for (int j = shaderStartIndex; j < allLines.size(); j++) {
				int index = allLines[j].find(kernelNames[i]);

				if (index != std::string::npos && (allLines[j][index + kernelNames[i].length()] == ' ' || allLines[j][index + kernelNames[i].length()] == '(')) {
					kernelFunctionFound = true;

					int parenthesisBeginIndex = allLines[j].find_first_of("(") + 1;
					int parenthesisEndIndex = allLines[j].find_first_of(")");
					std::string subLine = allLines[j].substr(parenthesisBeginIndex, parenthesisEndIndex - parenthesisBeginIndex);

					uint32_t tx = 1, ty = 1, tz = 1;
					
					int firstCommaIndex = subLine.find_first_of(",");
					int lastCommaIndex = subLine.find_last_of(",");

					//Local thread size x
					std::string str = subLine.substr(0, firstCommaIndex);
					int splitIndex = str.find_first_of("=");

					std::string decimalStr = str.substr(splitIndex + 1, str.size() - (splitIndex + 1));
					tx = std::atoi(decimalStr.c_str());
					
					//Local thread size y
					str = subLine.substr(firstCommaIndex + 1, lastCommaIndex - firstCommaIndex - 1);
					splitIndex = str.find_first_of("=");

					decimalStr = str.substr(splitIndex + 1, str.size() - (splitIndex + 1));
					ty = std::atoi(decimalStr.c_str());

					//Local thread size z
					str = subLine.substr(lastCommaIndex + 1, subLine.size() - lastCommaIndex - 1);
					splitIndex = str.find_first_of("=");

					decimalStr = str.substr(splitIndex + 1, str.size() - (splitIndex + 1));
					tz = std::atoi(decimalStr.c_str());

					//layout(local_size_x = 4, local_size_y = 4, local_size_z = 1) in;
					cs_string += "layout(local_size_x =" + std::to_string(tx) +
						", local_size_y = " + std::to_string(ty) +
						", local_size_z = " + std::to_string(tz) + ") in;\n";

					cs_string += "void main()";

					if (allLines[j].find("{") != std::string::npos)
						cs_string += "{";

					cs_string += "\n";
				}
				else {
					cs_string += allLines[j] + "\n";
				}
			}


			if (!kernelFunctionFound) {
				ENG_LOG_ERROR("Kernel Not Found, name : {0}", kernelNames[i]);
				continue;
			}

			ShaderVariant* sv = new ShaderVariant;

			sv->id = glCreateProgram();
			int success;

			cs_id = glCreateShader(GL_COMPUTE_SHADER);

			const char* source4 = cs_string.c_str();

			glShaderSource(cs_id, 1, &source4, nullptr);
			glCompileShader(cs_id);

			glGetShaderiv(cs_id, GL_COMPILE_STATUS, &success);
			if (!success) {
				int length;
				glGetShaderiv(cs_id, GL_INFO_LOG_LENGTH, &length);
				char* message = (char*)malloc(length);
				glGetShaderInfoLog(cs_id, length, &length, message);

				ENG_LOG_ERROR("FAILED TO COMPILE COMPUTE SHADER (Variant: {1}): {0}", message, i);
				ENG_LOG_WARN(cs_string);

				free(message);
			}

			glAttachShader(sv->id, cs_id);

			glLinkProgram(sv->id);

			glGetProgramiv(sv->id, GL_LINK_STATUS, &success);
			if (!success) {
				int length;
				glGetProgramiv(sv->id, GL_INFO_LOG_LENGTH, &length);
				char* message = (char*)malloc(length);
				glGetProgramInfoLog(sv->id, length, &length, message);

				ENG_LOG_ERROR("FAILED TO LINK COMPUTE SHADER(PROGRAM): {0}", message);
				free(message);
			}

			glValidateProgram(sv->id);

			glGetProgramiv(sv->id, GL_VALIDATE_STATUS, &success);
			if (!success) {
				int length;
				glGetProgramiv(sv->id, GL_INFO_LOG_LENGTH, &length);
				char* message = (char*)malloc(length);
				glGetProgramInfoLog(sv->id, length, &length, message);

				ENG_LOG_ERROR("FAILED TO VALIDATE COMPUTE SHADER(PROGRAM): {0}", message);
				free(message);
				exit(-1);
			}

			if (cs_id != -1)
				glDeleteShader(cs_id);

			shaderVariants.push_back(sv);

			ENG_LOG_INFO("Compute Shader is created, variant id: {0}", sv->id);
		}

		if (kernelNames.size() == 0) {
			ENG_LOG_ERROR("No kernel found in the given compute shader file: {0}", filePath);
			exit(-1);
		}

		SetCurrentVariantIndex(0);
	}

	ComputeShader::~ComputeShader() {
		for (uint32_t i = 0; i < shaderVariants.size(); i++) {
			glDeleteProgram(shaderVariants[i]->id);
			ENG_LOG_INFO("Compute Shader is deleted, variant id: {0}", shaderVariants[i]->id);

			delete shaderVariants[i];
		}
	}

	void ComputeShader::bind() {
		glUseProgram(currentVariant->id);
	}

	void ComputeShader::unbind() {
		glUseProgram(0);
	}

	int ComputeShader::GetKernelIndex(std::string kernelName) {
		for (uint32_t i = 0; i < kernelNames.size(); i++) {
			if (kernelName.compare(kernelNames[i]) == 0)
				return i;
		}

		return -1;
	}

	bool ComputeShader::EnableKernel(std::string kernelName) {
		int kernelIndex = GetKernelIndex(kernelName);

		if (kernelIndex >= 0) {
			SetCurrentVariantIndex(kernelIndex);
			return true;
		}
		else {
			ENG_LOG_ERROR("Kernel not found: {0}", kernelName);
		}

		return false;
	}

	bool ComputeShader::EnableKernel(int kernelIndex) {
		if (kernelIndex >= 0 && kernelIndex < kernelNames.size()) {
			SetCurrentVariantIndex(kernelIndex);
			return true;
		}

		return false;
	}

	void ComputeShader::DispatchCompute(uint32_t threadGroupX, uint32_t threadGroupY, uint32_t threadGroupZ) {
		bind();
		glDispatchCompute(threadGroupX, threadGroupY, threadGroupZ);

		glMemoryBarrier(GL_ALL_BARRIER_BITS);
	}
}