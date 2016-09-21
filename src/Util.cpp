#include "Util.h"

std::string ICE::Util::readFileToString(std::string path) {
	std::ifstream file(path);
	std::string str((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

	return str;
}

std::vector<std::string> ICE::Util::splitString(std::string s, char delimiter) {
	std::stringstream strstream(s);
	std::string part;
	std::vector<std::string> elems;

	while (std::getline(strstream, part, delimiter)) {
		elems.push_back(part);
		part = "";
	}

	return elems;
}
