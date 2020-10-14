#include "pch.h"
#include "UI.h"

void Menus::FromFiles(const std::vector<std::string>& filepaths)
{
	for (int i = 0; i < filepaths.size(); i++) {
		std::string content = "";
		FromFile(filepaths[i], content);
		contents.push_back(content);
	}
}

void Menus::FromFile(const std::string& filepath, std::string& content)
{
	if (std::filesystem::exists(filepath)) {
		std::ifstream ifs(filepath);
		std::string line;
		while (std::getline(ifs, line))
			content += line + "\n";
		ifs.close();
	}
	else {
		std::cout << "Menu content is missing!\n"
			<< "Please reload the application with the new menu provided to this location: \"" << filepath << "\"\n"
			<< "Or make sure that given filepath is correct.\n";
		std::cin.get();
		exit(1);
	}
}

bool isInt(std::string line) {
	for (char c : line)
		if (!isdigit(c) && c != '-')
			return false;
	return true;
}

bool isFloat(std::string line) {
	for (char c : line)
		if (!isdigit(c) && c != '.' && c != '-')
			return false;
	return true;
}

std::string toLower(std::string line) {
	for (auto& c : line)
		c = tolower(c);
	return line;
}

template<>
std::string Input<std::string>(const std::string& print) {
	std::cout << "  " << print;
	std::string in;
	std::getline(std::cin, in);
	return toLower(in);
}

template<>
char Input<char>(const std::string& print) {
	std::cout << "  " << print;
	std::string in;
	std::getline(std::cin, in);
	return tolower(in[0]);
}

template<>
int Input<int>(const std::string& print) {
	std::cout << "  " << print;
	std::string in;
	std::getline(std::cin, in);
	if (isInt(in))
		return atoi(in.c_str());
	else
		return -1;
}

template<>
double Input<double>(const std::string& print) {
	std::cout << "  " << print;
	std::string in;
	std::getline(std::cin, in);
	if (isFloat(in))
		return atof(in.c_str());
	else
		return -1;
}

void WrongChoice(const std::string& print)
{
	std::cout << Clr(12) << "  " << print;
	system("pause");
	std::cout << Clr();
}

std::string Time(float t) {
	std::string line = "";
	if (t < 10)
		line += "0" + std::to_string((int)t) + ":";
	else
		line += std::to_string((int)t) + ":";
	if ((t - std::trunc(t)) * 60.f < 10.f)
		line += "0" + std::to_string((int)(std::round((t - (int)t) * 60.f)));
	else
		line += std::to_string((int)(std::round((t - (int)t) * 60.f)));
	return line;
}

std::string Money(float m) {
	std::string line = std::to_string((int)m) + ".";
	int n = (int)(m - (int)m) * 100;
	if (n < 10)
		line += "0";
	line += std::to_string(n) + "$";
	return line;
}
