#include "Game/Console.hpp"

namespace game {
	int64_t Console::process(std::istream& is) {
		int64_t result = 0;
		std::string opcode;
		is >> opcode;
		return this->m_functions[opcode](is);
	}
	void Console::add_function(std::string key, std::function <int64_t(std::istream& is)> value) {
		this->m_functions.emplace(key, value);
	}
}