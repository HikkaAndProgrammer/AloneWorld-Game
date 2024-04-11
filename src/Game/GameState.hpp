#pragma once
//engine
#include "Engine/GameManager.hpp"
#include "Engine/InputManager.hpp"
#include "Engine/StateMachine.hpp"

//game
#include "Game/Core.hpp"

namespace game {
	class GameState : public engine::BaseState {
	public:
		void update() override {
			//update things
			engine::core->event_system->update();

			if (this->move_left->is_key_pressing())
				core->camera->move(-1, 0);
			if (this->move_right->is_key_pressing())
				core->camera->move(1, 0);

			core->camera->update();
			
			//render begin
			core->render_module->begin();
			core->window->clear(sf::Color::White);
			
			//render things
			core->window->setView(core->camera->view());
			core->tilemap->render();

			//render end
			core->render_module->draw();
			core->window->display();
			core->render_module->end();
		}

		void on_create() override {
			auto& view = core->camera->view();
			auto window_size = core->window->getSize();

			core->camera->set_position(0, 0);
			core->camera->set_size(window_size.x, window_size.y);

			this->move_left = core->input_manager->get_handler("move_left");
			this->move_right = core->input_manager->get_handler("move_right");
			this->move_up = core->input_manager->get_handler("move_up");
			this->move_down = core->input_manager->get_handler("move_down");
		}

	protected:
		engine::Input move_left, move_right, move_up, move_down;
	};
}