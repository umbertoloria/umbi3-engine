#pragma once

#include <string>
#include <fstream>
#include <sstream>

class Resources {

public:

	static const std::string get (const std::string& filepath) {
		std::ifstream stream("../" + filepath);
		std::string line;
		std::stringstream ss;
		while (getline(stream, line))
			ss << line << '\n';
		return ss.str();
	}

};