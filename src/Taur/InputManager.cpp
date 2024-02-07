//taur
#include <Taur/InputManager.hpp>

//toml
#include <toml.hpp>

//taur
#include <Taur/GameManager.hpp>

namespace taur {
	//input_t

	void input_t::update() {
		using enum InputType;
		this->prev = this->curr;
		switch (this->type) {
		case Keyboard:
			this->curr = sf::Keyboard::isKeyPressed((sf::Keyboard::Key)this->id);
			break;
		case Mouse:
			this->curr = sf::Mouse::isButtonPressed((sf::Mouse::Button)this->id);
			break;
		}
	}

	bool input_t::is_key_pressing() const {
		return this->curr; 
	}
	bool input_t::is_key_pressed() const { 
		return this->curr && !this->prev; 
	}
	bool input_t::is_key_upped() const { 
		return !this->curr && this->prev; 
	}

	//cursor_t

	void cursor_t::update() {
		this->prev = this->curr;
		this->curr = sf::Mouse::getPosition(taur::core->window);
	}

	sf::Vector2i cursor_t::get_position() const { 
		return this->curr; 
	}
	sf::Vector2i cursor_t::get_difference() const { 
		return this->prev - this->curr; 
	}

	//DragDistanceHandler

	void DragDistanceHandler::update() {
		auto current_position = this->cursor->get_position();

		if (this->input->is_key_pressed())
			this->start_position = current_position;
		else if (this->input->is_key_upped())
			this->difference = this->start_position - current_position;
		else
			this->difference = { 0, 0 };
	}

	sf::Vector2i DragDistanceHandler::get_drag_distance() const { 
		return this->difference; 
	}

	//InputManager

	void InputManager::add_input_handler(std::string key, InputType type, uint8_t id) {
		this->m_handlers.emplace(key, std::make_shared <input_t>(type, id));
	}

	void InputManager::update() {
		for (auto& [id, input] : this->m_handlers)
			input->update();
	}

	void InputManager::load_config(std::string filename) {
		auto config = toml::parse(filename).as_table();
		for (const auto& [key, val] : config) {
			auto info = val.as_table();
			InputType type;
			if (info["type"].as_string() == "mouse") {
				type = InputType::Mouse;
			} else if (info["type"].as_string() == "keyboard") {
				type = InputType::Keyboard;
			} else
				continue;
			this->add_input_handler(key, type, info["button_id"].as_integer());
		}
	}
	void InputManager::save_config(std::string filename) const {
		std::ofstream file;
		toml::value config = toml::table();
		toml::table& table = config.as_table();
		
		for (const auto& [key, val] : this->m_handlers) {
			//toml::value on_insert;
			toml::table cell;
			std::string type;
			
			switch (val->type) {
			case InputType::Keyboard:
				type = "keyboard";
				break;
			case InputType::Mouse:
				type = "mouse";
				break;
			default:
				continue;
			}

			cell.emplace("button_id", (uint32_t)val->id);
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
	std::shared_ptr <input_t> InputManager::get_handler(std::string key) const { 
		return this->m_handlers.at(key); 
	}
}