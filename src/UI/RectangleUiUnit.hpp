#pragma once
//ui
#include "UI/Primitives.hpp"
#include "UI/TextUiUnit.hpp"

namespace ui {
	class RectangleUiUnit : public BasicUiUnit, public IClickable {
	public:
		bool is_clicked(sf::Vector2i point) override {
			return this->m_box.getLocalBounds().contains(point.x, point.y);
		}

		const sf::String& get_text() const {
			return this->m_text.getString();
		}
		void set_text(const std::string& text, uint16_t size) {
			this->m_text.setCharacterSize(size);
			this->m_text.setString(text);
			this->_set_text_to_center();
		}

		sf::RectangleShape& box() { return this->m_box; }
		const sf::RectangleShape& box() const { return this->m_box; }

		void render() const override {
			engine::game_manager->window->draw(this->m_box);
			this->m_text.render();
		}

	protected:
		sf::RectangleShape m_box;
		TextUiUnit m_text;

	private:
		void _set_text_to_center() {
			auto box_position = this->m_box.getLocalBounds();
			auto text_position = this->m_text.getLocalBounds();
			this->m_text.setPosition(box_position.left + (box_position.width - text_position.width) / 2,
				box_position.top + (box_position.height - text_position.height) / 2);
		}
	};
}