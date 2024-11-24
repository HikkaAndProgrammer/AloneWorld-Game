#pragma once
//sf
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

namespace eil::util {
	template <class T>
	struct delta_t {
		T prev, curr = T();

		void update(T next) {
			prev = curr;
			curr = next;
		}
	};

	class Updatable {
	public:
		Updatable() {
			clock.restart();
		}
		virtual ~Updatable() = default;

		virtual void update() = 0;

	protected:
		sf::Time get_elapsed_time() const {
			return this->clock.getElapsedTime();
		}

	private:
		sf::Clock clock;
	};

	class Renderable {
	public:
		virtual ~Renderable() = default;

		//you have to call render_module.request(VertexArray&&) at the end
		virtual void render() const = 0;
	};

	template <class... _Ts>
	struct overload : _Ts... { using _Ts::operator()...; };

	using IUpdatable = std::shared_ptr <Updatable>;
	using IRenderable = std::shared_ptr <Renderable>;
	using IDrawable = std::shared_ptr <sf::Drawable>;
}
