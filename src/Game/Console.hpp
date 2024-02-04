#pragma once
//std
#include <iostream>
#include <functional>
#include <string>
#include <unordered_map>

namespace game {
	class Console {
	public:
		int64_t process(std::istream& is);
		void add_function(std::string key, std::function <int64_t(std::istream& is)> value);

	private:
		std::unordered_map <std::string, std::function <int64_t(std::istream&)>> m_functions;
	};
}