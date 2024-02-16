//game
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

	void RenderState::onCreate() {
		float width = game::core->tilemap->width() * 16,
			height = game::core->tilemap->height() * 16,
			zoom = 1.f / 3;
		auto& view = this->camera.get_view();

		game::core->window.create(sf::VideoMode(width / zoom, height / zoom), "Alone World");

		view.setCenter(width / 2, height / 2);
		view.setSize(width / zoom, height / zoom);
		view.zoom(zoom);

		this->camera.link(game::core->tilemap);
	}
}