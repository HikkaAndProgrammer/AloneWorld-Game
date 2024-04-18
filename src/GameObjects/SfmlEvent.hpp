#pragma once

//sf
#include <SFML/Window/Event.hpp>

//engine
#include "Engine/EventSystem.hpp"
#include "Engine/GameManager.hpp"

namespace game_objects {
	class SfmlEvent : public engine::BaseEvent {
	public:
		//TODO: make every sfml event handling
		void update() final override {
			sf::Event event;
			while (engine::game_manager->window->pollEvent(event)) {
				switch (event.type) {
				case sf::Event::Closed:
					engine::game_manager->window->close();
					engine::game_manager->flag = false;
					break;
				default:;
				}
			}
		}
	};
}