#pragma once
//sf
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/System/Clock.hpp>

namespace util {
	sf::Vertex create_vertex(float x, float y, float tx, float ty, sf::Color color = sf::Color(255, 255, 255));

	class Updatable {
	public:
		Updatable() {
			clock.restart();
		}

		virtual void update() = 0;

	protected:
		sf::Time get_elapsed_time() {
			return this->clock.getElapsedTime();
		}

	private:
		sf::Clock clock;
	};
}