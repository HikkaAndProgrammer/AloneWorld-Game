#include <Taur/InputManager.hpp>

//taur
#include <Taur/Core.hpp>

namespace taur {
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

	void cursor_t::update() {
		this->prev = this->curr;
		this->curr = sf::Mouse::getPosition(taur::core.window);
	}

	void DragDistanceHandler::update() {
		auto current_position = this->cursor->get_position();

		if (this->input->is_key_pressed())
			this->start_position = current_position;
		else if (this->input->is_key_upped())
			this->difference = this->start_position - current_position;
		else
			this->difference = { 0, 0 };
	}

	void InputManager::update() {
		for (auto& [id, input] : this->m_handlers)
			input->update();
	}
}