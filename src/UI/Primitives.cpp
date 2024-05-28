#include "UI/Primitives.hpp"

namespace util {
	sf::Color to_color(const toml::value& value) {
		auto colors = toml::get <std::vector <sf::Uint8>>(value);
		return sf::Color(colors[0], colors[1], colors[2], colors.size() == 4 ? colors[3] : 255);
	}
}
