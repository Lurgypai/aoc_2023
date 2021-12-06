#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <array>
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

struct point {
	int x;
	int y;
	bool operator==(const point& other) const {
		return x == other.x && y == other.y;
	}
	bool operator!=(const point& other) const {
		return !(*this == other);
	}
};

int main(int argc, char** argv) {
	std::ifstream input{ "in.txt" };
	std::vector<std::string> lines = split(input);

	std::vector<std::vector<int>> vals;
	vals.resize(lines.size());
	for (int i = 0; i != vals.size(); ++i) {
		vals[i] = extractNumbers(lines[i]);
	}

	std::vector<std::vector<int>> map{ {0} };
	map.resize(1000);
	for (auto& m : map)
		m.resize(1000);
	for (const auto& val : vals) {
		point start{ val[0], val[1] };
		point end{ val[2], val[3] };
		int xdir = (start.x < end.x) ? 1 : -1;
		int ydir = (start.y < end.y) ? 1 : -1;
		while (start != end) {
			++map[start.x][start.y];
			if(start.x != end.x) start.x += xdir;
			if(start.y != end.y) start.y += ydir;
		}
		++map[start.x][start.y];
	}

	//for (const auto& m : map) {
	//	printVals(m);
	//}

	int cnt = 0;
	for (auto& row : map) {
		for (const auto& val : row) {
			cnt += val >= 2;
		}
	}

	std::cout << cnt << '\n';
	return  0;
}