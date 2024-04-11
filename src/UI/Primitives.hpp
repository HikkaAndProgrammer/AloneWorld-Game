#pragma once
//std
#include <vector>
#include <list>

//sf
#include <SFML/Graphics.hpp>

//engine
#include "Engine/GameManager.hpp"
#include "Engine/Util.hpp"

namespace engine::ui {
	class BasicUiUnit : public sf::Transformable, public util::Renderable {
	public:
		virtual bool is_clicked(sf::Vector2i point) = 0;
		virtual void on_click() = 0;
	};

	class UiPage {
	public:


	protected:
		std::vector <std::list <BasicUiUnit>> m_elements;
	};

	class RectangleUiUnit : public BasicUiUnit {
	public:
		bool is_clicked(sf::Vector2i point) override {
			return this->m_box.getLocalBounds().contains(point.x, point.y);
		}

		void set_text(std::string text, uint16_t size) {
			if (text.empty())
				this->m_text.reset(new sf::Text(text, *core->font, size));
			else {
				this->m_text->setCharacterSize(size);
				this->m_text->setString(text);
			}
		}
		
		sf::RectangleShape& box() { return this->m_box; }
		const sf::RectangleShape& box() const { return this->m_box; }

		void render() const override {
			
		}

	protected:
		sf::RectangleShape m_box;
		std::shared_ptr <sf::Text> m_text; //optional
	};
}