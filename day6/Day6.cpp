#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <array>
#include <algorithm>
#include <unordered_map>

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

std::vector<int> extractNumbers(std::string str)
{
	std::string val;
	std::vector<std::string> storedNums;
	for (char c : str) {
		if (c >= '0' && c <= '9') {
			val += c;
		} else {
			if (val != "") storedNums.emplace_back(std::move(val));
			val = "";
		}
	}
	if (val != "") storedNums.emplace_back(std::move(val));
	std::vector<int> ret;
	for (const auto& str : storedNums) {
		ret.emplace_back(std::stoi(str));
	}
	return ret;
}

int main(int argc, char** argv) {
	std::ifstream input{ "in.txt" };
	std::vector<std::string> lines = split(input);

	std::vector<std::vector<int>> vals;
	vals.resize(lines.size());
	for (int i = 0; i != vals.size(); ++i) {
		vals[i] = extractNumbers(lines[i]);
	}

	auto startAges = vals.front();

	std::array<unsigned long long, 9> ages{};
	for (const auto& age : startAges) {
		++ages[age];
	}

	constexpr int DAY_COUNT = 256;
	for (int i = 0; i != DAY_COUNT; ++i) {
		unsigned long long newCount = ages[0];
		for (int i = 0; i != 9; ++i) {
			if (i != 8) {
				ages[i] = ages[i + 1];
				if (i == 6) ages[i] += newCount;
			}
			else {
				ages[i] = newCount;
			}
		}
	}

	//printVals(ages);

	unsigned long long count = 0;
	for (const auto& age : ages) {
		count += age;
	}

	std::cout << count << '\n';
	return  0;
}