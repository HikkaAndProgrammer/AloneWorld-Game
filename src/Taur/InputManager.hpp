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

		bool is_key_pressing() const;
		bool is_key_pressed() const;
		bool is_key_upped() const;
	};

	struct cursor_t {
		sf::Vector2i prev, curr;

		void update();

		sf::Vector2i get_position() const;
		sf::Vector2i get_difference() const;
	};

	class DragDistanceHandler {
	public:
		DragDistanceHandler(std::shared_ptr <cursor_t> cursor, std::shared_ptr <input_t> input) : input(input), cursor(cursor) {}

		void update();

		sf::Vector2i get_drag_distance() const;

	private:
		sf::Vector2i start_position, difference;
		std::shared_ptr <cursor_t> cursor;
		std::shared_ptr <input_t> input;
	};

	//every keyboard/mouse event has to be unique
	class InputManager {
	public:
		void add_input_handler(std::string key, InputType type, uint8_t id);

		void update();

		void load_config();
		void save_config();

		std::shared_ptr <cursor_t> get_cursor() const;
		std::shared_ptr <input_t> get_handler(std::string key) const;

	protected:
		std::unordered_map <std::string, std::shared_ptr <input_t>> m_handlers;
		std::shared_ptr <cursor_t> m_cursor;
	};
}