#include "Engine/InputManager.hpp"

//toml
#include <toml.hpp>

//engine
#include <ranges>

#include "Engine/Util.hpp"

namespace engine {
	//input_t

	bool input_t::is_key_pressing() const {
		return this->curr; 
	}
	bool input_t::is_key_pressed() const { 
		return this->curr && !this->prev; 
	}
	bool input_t::is_key_released() const { 
		return !this->curr && this->prev; 
	}

	//cursor_t

	sf::Vector2i cursor_t::get_position() const { 
		return this->curr; 
	}
	sf::Vector2i cursor_t::get_difference() const { 
		return this->prev - this->curr; 
	}

	//DragDistanceHandler

	sf::Vector2i DragDistanceHandler::get_drag_distance() const { 
		return this->difference; 
	}

	//InputManager

	void InputManager::add_input_handler(const std::string& key, InputDetail detail) {
		Input temp(new input_t(detail));
		this->m_handlers.emplace(key, temp);
	}

	void InputManager::load_config(const std::string& filename) {
		auto config = toml::parse(filename).as_table();
		for (const auto& [key, val] : config) {
			auto info = val.as_table();
			InputDetail detail;
			if (info["type"].as_string() == "mouse") {
				detail = (sf::Mouse::Button)info["button_id"].as_integer();
			} else if (info["type"].as_string() == "keyboard") {
				detail = (sf::Keyboard::Key)info["button_id"].as_integer();
			} else
				continue;
			this->add_input_handler(key, detail);
		}
	}
	void InputManager::save_config(const std::string& filename) const {
		std::ofstream file;
		toml::value config = toml::table();
		toml::table& table = config.as_table();
		
		for (const auto& [key, val] : this->m_handlers) {
			toml::table cell;
			std::string type;
			uint32_t id;

			std::visit(util::overload{
				[&](const sf::Keyboard::Key& key) { type = "keyboard"; id = key; },
				[&](const sf::Mouse::Button& button) { type = "mouse"; id = button; }
			}, val->detail);

			cell.emplace("button_id", id);
			cell.emplace("type", type);
			table.emplace(key, cell);
		}

		file.open(filename);
		if (!file.is_open())
			return;
		file << config;
		file.close();
	}

	std::shared_ptr <cursor_t> InputManager::get_cursor() const { 
		return this->m_cursor; 
	}
	std::shared_ptr <input_t> InputManager::get_handler(const std::string& key) const { 
		return this->m_handlers.at(key); 
	}

	//InputEvent

	void InputEvent::update() {
		for (const auto& input : this->m_input_manager.m_handlers | std::views::values) {
			input->prev = input->curr;
			std::visit(util::overload{
				[&](const sf::Keyboard::Key& key) { input->curr = sf::Keyboard::isKeyPressed(key); },
				[&](const sf::Mouse::Button& button) { input->curr = sf::Mouse::isButtonPressed(button); }
			}, input->detail);
		}
	}
}