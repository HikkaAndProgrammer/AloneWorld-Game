#include <Game/RenderState.hpp>

//engine
#include <Game/Core.hpp>

//game
#include <Game/TilemapCamera.hpp>

namespace game {
	void RenderState::update() {
		engine::core->render_module->begin();
		engine::core->window.clear(sf::Color::White);

		this->camera.render();
		game::core->window.setView(this->camera.view());

		game::core->render_module->draw();
		game::core->window.display();
		game::core->render_module->end();
	}

	void RenderState::on_create() {
		auto& view = this->camera.view();
		auto tilemap = core->tilemap;
		auto window_size = core->window.getSize();

		this->camera.tilemap() = core->tilemap;
		this->camera.set_position(0, 0);
		this->camera.set_size(window_size.x, window_size.y);
		//this->camera.view().zoom(1.f / 3);
	}
}