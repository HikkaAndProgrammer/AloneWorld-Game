//std
#include <iostream>

//eil::engine
#include "TextureManager.hpp"

class Square {
	int operator()(int n) const {
		return n * n;
	}
};

using namespace eil::engine;
int main() {
	Square s;
	std::cout << s(5);

	/*TextureManager tm;
	int64_t h;

	tm.init("res/textures/");*/
}