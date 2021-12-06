#include <iostream>
#include <fstream>
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

int main(int argc, char** argv) {
	std::ifstream input{ "in.txt" };
	std::vector<std::string> lines{};
	for (std::string s; std::getline(input, s, '\n'); lines.push_back(s));

	std::vector<int> vals;
	vals.reserve(lines.size());
	for (const auto& line : lines) {
		vals.emplace_back(std::stoi(line));
	}

	int incs = 0;
	int prev = vals[0] + vals[1] + vals[2];
	for (int i = 3; i != vals.size(); ++i) {
		int newVal = (vals[i] + vals[i - 1] + vals[i - 2]);
		incs += prev < newVal;
		prev = newVal;
	}
	std::cout << incs << '\n';
}