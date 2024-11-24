#include "InputSystem.hpp"

//std
#include <ranges>

//toml
#include <toml.hpp>

namespace eil::engine {
	//BaseInput

	BaseInput::BaseInput(handler_variant_t id) : _id(id) {}

	bool BaseInput::is_key_pressing() const {
		return _status.curr;
	}
	bool BaseInput::is_key_pressed() const {
		return !_status.prev && _status.curr;
	}
	bool BaseInput::is_ket_released() const {
		return _status.prev && !_status.curr;
	}

	//BaseCursor

	sf::Vector2i BaseCursor::get_position() const {
		return _position.curr;
	}

	sf::Vector2i BaseCursor::get_difference() const {
		return _position.prev - _position.curr;
	}

	//InputManager

	void InputManager::init() {
		m_cursor = std::make_shared<BaseCursor>();
	}

	void InputManager::add_input_handler(const std::string& key, handler_variant_t val) {
		m_handlers.emplace(key, std::make_shared<BaseInput>(val));
	}

	void InputManager::load_config(const std::string& path) {
		auto data = toml::parse(path).as_table();
		for (const auto& [key, val] : data) {
			auto info = val.as_table();
			handler_variant_t handler_id;
			int32_t temp = info.at("button_id").as_integer();

			if (info.at("type").as_string() == "m") {
				handler_id = (sf::Mouse::Button) temp;
			} else if (info.at("type").as_string() == "k") {
				handler_id = (sf::Keyboard::Key) temp;
			} else continue;
			add_input_handler(key, handler_id);
		}
	}

	void InputManager::save_config(const std::string& path) const {
		std::ofstream file;
		toml::value data = toml::table();

		for (const auto& [key, val] : m_handlers) {
			toml::table cell;
			std::string type;
			int32_t id;

			std::visit(util::overload {
				[&](const sf::Keyboard::Key& temp) { type = "k"; id = temp; },
				[&](const sf::Mouse::Button& temp) { type = "m"; id = temp; } },
				val->_id);

			cell.emplace("button_id", id);
			cell.emplace("type", type);
			data.emplace_back(key, cell);
		}

		file.open(path);
		if (!file.is_open())
			return;
		file << toml::format(data);
		file.close();
	}

	Cursor InputManager::get_cursor() const {
		return m_cursor;
	}
	Input InputManager::get_handler(const std::string& key) const {
		return m_handlers.at(key);
	}

	//InputEvent

	InputEvent::InputEvent(InputManager& source) : _source(source) {}

	void InputEvent::update() {
		//TODO: dependant on window
		_source.m_cursor->_position.update(sf::Mouse::getPosition());

		for (const auto& input : _source.m_handlers | std::views::values) {
			std::visit(util::overload {
				[&](const sf::Keyboard::Key& key) { input->_status.update(sf::Keyboard::isKeyPressed(key)); },
				[&](const sf::Mouse::Button& button) {} },
				input->_id);
		}
	}
}
