#pragma once
//std
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>

//sf
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

namespace taur {
	enum class InputType : bool {
		Keyboard = 0,
		Mouse = 1
	};

	struct input_t {
		InputType type;
		uint8_t id;
		bool prev = false, curr = false;

		input_t(InputType type, uint8_t id) : type(type), id(id) {}

		void update();

		bool is_key_pressing() const { return this->curr; }
		bool is_key_pressed() const { return this->curr && !this->prev; }
		bool is_key_upped() const { return !this->curr && this->prev; }
	};
	using Input = std::shared_ptr <input_t>;

	struct cursor_t {
		sf::Vector2i prev, curr;

		void update();

		sf::Vector2i get_position() { return this->curr; }
		sf::Vector2i get_difference() { return this->prev - this->curr; }
	};
	using Cursor = std::shared_ptr <cursor_t>;

	class DragDistanceHandler {
	public:
		DragDistanceHandler(Cursor cursor, Input input) : input(input), cursor(cursor) {}

		void update();

		sf::Vector2i get_drag_distance() { return this->difference; }

	private:
		sf::Vector2i start_position, difference;
		Cursor cursor;
		Input input;
	};

	//every keyboard/mouse event has to be unique
	class InputManager {
	public:
		void add_input_handler(std::string key, InputType type, uint8_t id) {
			this->m_handlers.emplace(key, std::make_shared <input_t>(new input_t(type, id)));
		}

		void update();

		void load_config();
		void save_config();

		std::shared_ptr <cursor_t> get_cursor() const { return this->m_cursor; }
		std::shared_ptr <input_t> get_handler(std::string key) const { return this->m_handlers.at(key); }

	protected:
		std::unordered_map <std::string, Input> m_handlers;
		Cursor m_cursor;
	};
}