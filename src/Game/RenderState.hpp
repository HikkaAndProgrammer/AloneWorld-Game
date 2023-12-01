#pragma once
//taur
#include <Taur/Camera.hpp>
#include <Taur/Core.hpp>
#include <Taur/StateMachine.hpp>
#include <Taur/Tilemap.hpp>

namespace game {
	class RenderState : public taur::BaseState {
	public:
		void update(float dt) final override {
			taur::core.renderer->begin();
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

			taur::core.renderer->draw();
			taur::core.window.display();
			taur::core.renderer->end();
		}

		void onCreate() final override {
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

	private:
		taur::Camera camera;
	};
}
