#include <Taur/InputManager.hpp>

//taur
#include <Taur/Core.hpp>

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
		this->curr = sf::Mouse::getPosition(taur::core.window);
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
	std::shared_ptr <cursor_t> InputManager::get_cursor() const { 
		return this->m_cursor; 
	}
	std::shared_ptr <input_t> InputManager::get_handler(std::string key) const { 
		return this->m_handlers.at(key); 
	}
}