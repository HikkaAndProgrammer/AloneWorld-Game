#pragma once
//sf
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/Rect.hpp>
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

	class Renderable {
	public:
		//you have to call render_module.request(VertexArray&&) at the end
		virtual void render() const = 0;
	};

	template <class... Ts> 
	struct overload : Ts... { using Ts::operator()...; };
}