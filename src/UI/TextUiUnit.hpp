#pragma once
//sf
#include <SFML/Graphics/Text.hpp>

//ui
#include "UI/Primitives.hpp"

namespace ui {
	class TextUiUnit : public BasicUiUnit, public sf::Text {
	public:
		void render() const override {
			engine::game_manager->window->draw(*this);
		}
	};
}