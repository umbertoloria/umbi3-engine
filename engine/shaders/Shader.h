#pragma once

#include <iostream>
#include <unordered_map>
#include <vector>
#include <glm/glm.hpp>
#include "../Resources.h"

class Shader {

private:

	unsigned int id;
	std::unordered_map<std::string, int> uniformLocations;

public:

	explicit Shader (const std::string& vertexShaderPath, const std::string& fragmentShaderPath) {
		id = glCreateProgram();

		unsigned int vs = compileShader(GL_VERTEX_SHADER, Resources::get(vertexShaderPath));
		unsigned int fs = compileShader(GL_FRAGMENT_SHADER, Resources::get(fragmentShaderPath));

		glAttachShader(id, vs);
		glAttachShader(id, fs);
		glLinkProgram(id);
		glValidateProgram(id);

		glDeleteShader(vs);
		glDeleteShader(fs);
	}

	~Shader () {
		glDeleteProgram(id);
	}

	void bind () const {
		glUseProgram(id);
	}

	void unbind () const {
		glUseProgram(0);
	}

	void setUniform1i (const std::string& name, int v) {
		glUniform1i(getUniformLocation(name), v);
	}

	void setUniform1f (const std::string& name, float v) {
		glUniform1f(getUniformLocation(name), v);
	}

	void setUniform3f (const std::string& name, const glm::vec3& vec) {
		glUniform3f(getUniformLocation(name), vec.x, vec.y, vec.z);
	}

	void setUniform4f (const std::string& name, const glm::vec4& vec) {
		glUniform4f(getUniformLocation(name), vec.x, vec.y, vec.z, vec.w);
	}

	void setUniformMat4f (const std::string& name, const glm::mat4& matrix) {
		glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
	}

private:

	static unsigned int compileShader (unsigned int type, const std::string& source) {
		unsigned int id = glCreateShader(type);
		const char* src = source.c_str();
		glShaderSource(id, 1, &src, nullptr);
		glCompileShader(id);

		int result;
		glGetShaderiv(id, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE) {
			int length;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
			std::vector<char> message(length);
			glGetShaderInfoLog(id, length, &length, &message[0]);
			std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment");
			std::cout << " shader!" << std::endl;
			std::cout << message.data() << std::endl;
			glDeleteShader(id);
			return 0;
		}
		return id;
	}

	int getUniformLocation (const std::string& name) {
		if (uniformLocations.find(name) != uniformLocations.end()) {
			return uniformLocations[name];
		} else {
			int location = glGetUniformLocation(id, name.c_str());
			if (location == -1) {
				std::cout << "Warning uniform '" << name << "' doesn't exist!\n";
			}
			uniformLocations[name] = location;
			return location;
		}
	}

};