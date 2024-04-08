#pragma once
//engine
#include <Engine/InputManager.hpp>
#include <Engine/StateMachine.hpp>

//game
#include <Game/TilemapCamera.hpp>

namespace game {
	class GameState : public engine::BaseState {
	public:
		void update() override {
			engine::core->event_system->update();

			if (this->move_left->is_key_pressing())
				this->camera.move(-0.1, 0);
			if (this->move_right->is_key_pressing())
				this->camera.move(0.1, 0);

			this->camera.update();
			
			engine::core->render_module->begin();
			engine::core->window.clear(sf::Color::White);

			this->camera.render();
			game::core->window.setView(this->camera.view());

			game::core->render_module->draw();
			game::core->window.display();
			game::core->render_module->end();
		}

		void on_create() override {
			auto& view = this->camera.view();
			auto tilemap = core->tilemap;
			auto window_size = core->window.getSize();

			this->camera.tilemap() = core->tilemap;
			this->camera.set_position(0, 0);
			this->camera.set_size(window_size.x, window_size.y);

			this->move_left = core->input_manager->get_handler("move_left");
			this->move_right = core->input_manager->get_handler("move_right");
			this->move_up = core->input_manager->get_handler("move_up");
			this->move_down = core->input_manager->get_handler("move_down");
		}

	protected:
		game::TilemapCamera camera;
		engine::Input move_left, move_right, move_up, move_down;
	};
}