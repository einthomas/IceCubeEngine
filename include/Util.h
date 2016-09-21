#pragma once

#define _USE_MATH_DEFINES
#include <cmath>
#define GLEW_STATIC
#include <GL\glew.h>
#include <string>
#include <fstream>
#include <streambuf>
#include <vector>
#include <sstream>
#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>

namespace ICE {
	class Util {
	public:
		static std::string readFileToString(std::string path);
		static std::vector<std::string> splitString(std::string s, char delimiter);
		static std::string &ltrim(std::string &s);
		static std::string &rtrim(std::string &s);
	
	private:
		static const std::string delimiters;
	};
}
