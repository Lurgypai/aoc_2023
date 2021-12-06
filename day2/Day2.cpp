#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

template<typename Container>
void printVals(const Container& cont) {
	size_t i = 0;
	for (const auto& val : cont) {
		std::cout << val;
		if (++i < cont.size()) std::cout << ", ";
	}
	std::cout << '\n';
}

std::vector<std::string> split(std::istream& stream, char c = '\n') {
	std::vector<std::string> lines{};
	for (std::string s; std::getline(stream, s, c); lines.push_back(s));
	return lines;
}

int main(int argc, char** argv) {
	std::ifstream input{ "in.txt" };
	std::vector<std::string> lines = split(input);

	int x = 0, y = 0, aim = 0;
	for (const auto& line : lines) {
		std::vector<std::string> vals = split(std::stringstream{line}, ' ');
		int val = stoi(vals[1]);
		switch (vals[0][0]) {
		case 'f':
			x += val;
			y += aim * val;
			break;
		case 'u':
			aim -= val;
			break;
		case 'd':
			aim += val;
			break;
		}
	}

	std::cout << "X: " << x << ", Y: " << y << ", mult: " << x * y << '\n';
}