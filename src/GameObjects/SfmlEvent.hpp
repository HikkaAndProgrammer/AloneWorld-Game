#pragma once
//std
#include <list>

//sf
#include <SFML/Window/Event.hpp>

//engine
#include <Engine/EventSystem.hpp>
#include <Engine/GameManager.hpp>

namespace game_objects {
	class SfmlEvent : public engine::BaseEvent {
	public:
		//TODO: make evenry sfml event handling
		void update() final override {
			sf::Event event;
			while (engine::core->window.pollEvent(event)) {
				switch (event.type) {
				case sf::Event::Closed:

				}
			}
		}
	};
}