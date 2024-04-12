#include "Engine/Util.hpp"

namespace util {
	sf::Vertex create_vertex(float x, float y, float tx, float ty, sf::Color color) {
		return sf::Vertex(sf::Vector2f(x, y), color, sf::Vector2f(tx, ty));
	}
}