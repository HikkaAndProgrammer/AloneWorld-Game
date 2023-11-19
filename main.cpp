//std
#include <iostream>
#include <memory>
#include <string>

//sf
#include <SFML/Window.hpp>

//taur
#include <Taur/Core.hpp>
#include <Taur/Tilemap.hpp>
#include <Taur/Camera.hpp>

//script
#include <chaiscript/chaiscript.hpp>

namespace util {
	/*void generate(taur::Tilemap& tm, size_t width, size_t height) {
		tm.resize_and_clear(width, height);

		tm.at(0, 0) = ;
		for (size_t i = 0; i != width - 1; i++) {
			tm.at(i, 0) = ;
			tm.at(i, height - 1) = ;
		}

		for (size_t j = 1; j != height - 1; j++) {
			tm.at(0, j) = ;
			for (size_t i = 1; i != tm.width(); i++)
				tm.at(i, j) = ;
			tm.at(width - 1, j) = ;
		}
	}*/
	void print(std::ostream& os,taur::Tilemap& tm) {
		os << "width: " << tm.width() << "\nheight: " << tm.height() << '\n';
		for (size_t i = 0; i != tm.height(); i++) {
			for (size_t j = 0; j != tm.width(); j++)
				os << tm.at(j, i).block_id << ' ';
			os << '\n';
		}
	}
}

int main() {
	taur::core.init();

	//std::cout << sizeof(taur::tile_t);

	auto& rend = taur::core.renderer;
	auto& window = taur::core.window;
	taur::Tilemap tilemap;
	tilemap.load("res/saves/Admin/main.sav");

	float width = tilemap.width() * 16, height = tilemap.height() * 16;

	util::print(std::cout, tilemap);
	window.create(sf::VideoMode(width, height), "Alone World");

	taur::Camera camera;
	auto& view = camera.get_view();
	camera.link(&tilemap);

	view.setCenter(width / 4, height / 4);
	view.setSize(width, height);
	view.zoom(0.5f);

	while (window.isOpen()) {
		rend.begin();
		window.clear();

		sf::Event event;
		while (window.pollEvent(event))
			if (event.type == sf::Event::Closed)
				window.close();

		camera.render();
		window.setView(view);

		rend.draw();
		window.display();
		rend.end();
	}

	tilemap.save("res/saves/Admin/main.sav");

	taur::core.release();
	return 0;
}