#include "Util.h"

const std::string ICE::Util::delimiters = " \f\n\r\t\v";

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

std::string &ICE::Util::ltrim(std::string &s) {
	return s.erase(0, s.find_last_not_of(delimiters));
}

std::string &ICE::Util::rtrim(std::string &s) {
	return s.erase(s.find_last_not_of(delimiters) + 1);
}
