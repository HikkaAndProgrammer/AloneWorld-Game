#include "RenderState.hpp"

namespace game {
	void RenderState::update(float dt) {
		taur::core.render_module->begin();
		taur::core.window.clear(sf::Color::White);

		sf::Event event;
		while (taur::core.window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				taur::core.window.close();
				taur::core.flag.store(false);
			}
		}

		this->camera.render();
		taur::core.window.setView(this->camera.get_view());

		taur::core.render_module->draw();
		taur::core.window.display();
		taur::core.render_module->end();
	}

	void RenderState::onCreate() {
		float width = taur::core.tilemap.width() * 16,
			height = taur::core.tilemap.height() * 16,
			zoom = 1.f / 3;
		auto& view = this->camera.get_view();

		taur::core.window.create(sf::VideoMode(width / zoom, height / zoom), "Alone World");

		view.setCenter(width / 2, height / 2);
		view.setSize(width / zoom, height / zoom);
		view.zoom(zoom);

		this->camera.link(&taur::core.tilemap);
	}
}