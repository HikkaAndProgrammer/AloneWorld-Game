#pragma once
//sf
#include <SFML/Graphics/Vertex.hpp>

namespace util {
	sf::Vertex create_vertex(float x, float y, float tx, float ty, sf::Color color = sf::Color(255, 255, 255));
}