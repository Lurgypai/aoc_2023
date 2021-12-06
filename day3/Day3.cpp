#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <array>
#include <bitset>
#include <algorithm>

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

struct matchesColumn {
	unsigned int target;
	unsigned int column;
	bool operator()(const std::string& s) {
		int inCol = s[column] == '1';
		int targetInCol = target & (1 << (s.size() - column - 1));
		return !((inCol && targetInCol) || (!inCol && !targetInCol));
	}
};

int main(int argc, char** argv) {
	std::ifstream input{ "in.txt" };
	std::vector<std::string> lines = split(input);

	constexpr int SIZE = 5;

	std::array<int, SIZE> colCounts = { 0 };
	for (const auto& line : lines) {
		for (int i = 0; i != colCounts.size(); ++i) {
			colCounts[i] += line[i] == '1';
		}
	}

	printVals(colCounts);

	unsigned int gamma = 0;
	for (int i = 0; i != colCounts.size(); ++i) {
		gamma |= (colCounts[i] > (lines.size() / 2)) << (colCounts.size() - i - 1);
	}
	unsigned int epsilon = (~gamma) & 0b0000000000011111;

	std::cout << std::bitset<SIZE>{ gamma } << ", " << std::bitset<SIZE>{epsilon} << ", " << epsilon * gamma << '\n';

	std::string oxy = "", co = "";
	auto cpy = lines;
	for (unsigned int i = 0; i != SIZE; ++i) {
		cpy.erase(std::remove_if(cpy.begin(), cpy.end(), matchesColumn{ gamma, i }), cpy.end());
		if (cpy.size() == 1) {
			oxy = cpy.front();
		}
	}

	cpy = lines;
	for (unsigned int i = 0; i != SIZE; ++i) {
		cpy.erase(std::remove_if(cpy.begin(), cpy.end(), matchesColumn{ epsilon, i }), cpy.end());
		if (cpy.size() == 1) {
			co = cpy.front();
		}
	}

	std::cout << oxy << ", " << co << '\n';

	return  0;
}