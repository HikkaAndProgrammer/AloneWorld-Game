//game
#include <Game/RenderState.hpp>

//taur
#include <Taur/GameManager.hpp>

namespace game {
	void RenderState::update() {
		taur::core->render_module->begin();
		taur::core->window.clear(sf::Color::White);

		sf::Event event;
		while (taur::core->window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				taur::core->window.close();
				taur::core->flag.store(false);
			}
		}

		/*{
			sf::VertexArray shape(sf::PrimitiveType::Triangles, 6);

			size_t w = 120, h = 120;

			shape[0].position = { 0, 0 };
			shape[1].position = { 1.0f * w, 0 };
			shape[2].position = { 0.5f * w, 0.5f * h };
			shape[3].position = { 0, 0 };
			shape[4].position = { 0, 1.0f * h };
			shape[5].position = { 0.5f * w, 0.5f * h };

			shape[0].texCoords = { 0, 0 };
			shape[1].texCoords = { 640, 0 };
			shape[2].texCoords = { 640, 640 };
			shape[3].texCoords = { 0, 0 };
			shape[4].texCoords = { 0, 640 };
			shape[5].texCoords = { 640, 640 };
			
			sf::RenderStates states;
			states.texture = taur::core.texture_manager->at("sakura").get();
			taur::core.window.draw(shape, states);
		}*/

		this->camera->render();
		taur::core->window.setView(this->camera->get_view());

		taur::core->render_module->draw();
		taur::core->window.display();
		taur::core->render_module->end();
	}

	//TODO
	void RenderState::onCreate() {
		/*float width = taur::core.tilemap.width() * 16,
			height = taur::core.tilemap.height() * 16,
			zoom = 1.f / 3;
		auto& view = this->camera.get_view();

		taur::core.window.create(sf::VideoMode(width / zoom, height / zoom), "Alone World");

		view.setCenter(width / 2, height / 2);
		view.setSize(width / zoom, height / zoom);
		view.zoom(zoom);

		this->camera.link(&taur::core.tilemap);*/
	}
}