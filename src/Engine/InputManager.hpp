#pragma once
//std
#include <memory>
#include <string>
#include <unordered_map>
#include <variant>

//sf
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

//engine
#include "Engine/EventSystem.hpp"

namespace engine {
	enum class InputType {
		Mouse = 0,
		Keyboard
	};
	using InputDetail = std::variant <sf::Mouse::Button, sf::Keyboard::Key>;

	struct input_t {
		InputDetail detail;
		bool prev = false, curr = false;

		input_t() : detail(sf::Keyboard::Unknown) {}
		input_t(InputDetail detail) : detail(detail) {}

		bool is_key_pressing() const;
		bool is_key_pressed() const;
		bool is_key_released() const;
	};
	using Input = std::shared_ptr <input_t>;

	struct cursor_t {
		sf::Vector2i prev, curr;

		cursor_t() : prev(0, 0), curr(0, 0) {}

		sf::Vector2i get_position() const;
		sf::Vector2i get_difference() const;
	};
	using Cursor = std::shared_ptr <cursor_t>;

	class DragDistanceHandler {
	public:
		DragDistanceHandler(const Cursor& cursor, const Input& input) : input(input), cursor(cursor) {}

		sf::Vector2i get_drag_distance() const;

	private:
		sf::Vector2i start_position, difference;
		Cursor cursor;
		Input input;
	};

	//TODO: update for cursor and distance handler

	//every keyboard/mouse event has to be unique
	class InputManager {
		friend class InputEvent;
	public:
		void init();

		void add_input_handler(const std::string& key, InputDetail detail);

		void load_config(const std::string& filename);
		void save_config(const std::string& filename) const;

		Cursor get_cursor() const;
		Input get_handler(const std::string& key) const;

	protected:
		std::unordered_map <std::string, Input> m_handlers;
		Cursor m_cursor;
	};

	class InputEvent : public engine::BaseEvent {
	public:
		InputEvent(InputManager& input_manager) : m_input_manager(input_manager) {}

		void update() override;

	protected:
		InputManager& m_input_manager;
	};
}