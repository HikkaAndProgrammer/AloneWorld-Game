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
		game::core->window.setView(this->camera.get_view());

		game::core->render_module->draw();
		game::core->window.display();
		game::core->render_module->end();
	}

	void RenderState::on_create() {
		auto& view = this->camera.get_view();

		view.setCenter(width / 2, height / 2);
		view.setSize(width / zoom, height / zoom);
		view.zoom(zoom);

		this->camera.link(game::core->tilemap);
	}
}