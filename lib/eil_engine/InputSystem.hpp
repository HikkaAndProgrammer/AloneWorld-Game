#pragma once
//std
#include <memory>
#include <string>
#include <unordered_map>

//sf
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

//eil::util
#include <variant>

#include "EventSystem.hpp"
#include "Util.hpp"

namespace eil::engine {
	using handler_variant_t = std::variant<sf::Mouse::Button, sf::Keyboard::Key>;

	class BaseInput {
		friend class InputManager;
		friend class InputEvent;
	public:
		BaseInput(handler_variant_t id);

		bool is_key_pressing() const;
		bool is_key_pressed() const;
		bool is_ket_released() const;

	private:
		handler_variant_t _id;
		util::delta_t<bool> _status = { false, false };
	};
	using Input = std::shared_ptr<BaseInput>;

	class BaseCursor {
		friend class InputEvent;
	public:
		BaseCursor() = default;

		sf::Vector2i get_position() const;
		sf::Vector2i get_difference() const;

	private:
		util::delta_t<sf::Vector2i> _position;
	};
	using Cursor = std::shared_ptr<BaseCursor>;

	//TODO: drag distance handler

	class InputManager {
		friend class InputEvent;
	public:
		void init();

		void add_input_handler(const std::string& key, handler_variant_t val);

		void load_config(const std::string& path);
		void save_config(const std::string& path) const;

		Cursor get_cursor() const;
		Input get_handler(const std::string& key) const;

	protected:
		std::unordered_map<std::string, Input> m_handlers;
		Cursor m_cursor;
	};

	class InputEvent : public BaseEvent {
	public:
		InputEvent(InputManager& source);

		void update() override;

	private:
		InputManager& _source;
	};
}
