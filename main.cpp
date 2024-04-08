//std
#include <array>
#include <functional>
#include <iostream>
#include <memory>
#include <string>

//sf
#include <SFML/Window.hpp>

//engine
#include <Engine/GameManager.hpp>
#include <Engine/ThreadPool.hpp>

//game_objects
#include <GameObjects/Camera.hpp>
#include <GameObjects/Tilemap.hpp>

//script
#ifdef INCLUDE_SCRIPT_ENGINE
#include <chaiscript/chaiscript.hpp>
#endif

//game
#include <Game/Console.hpp>
#include <Game/GameState.hpp>
#include <Game/Tile.hpp>
#include <Game/Core.hpp>

namespace engine {
	std::shared_ptr <GameManager> core = std::make_shared <game::Core>();
}

namespace game {
	std::shared_ptr <Core> core = std::dynamic_pointer_cast <Core>(engine::core);
}

namespace util {
	void generate(game::Tilemap& tm, size_t width, size_t height) {
		//adjacent 3 - left, 2 - down, 1 - right, 0 - upper
		std::function choose_type = [](game::tile_t original, std::array <game::tile_t, 4> adjacent) {
			using enum game::block_state_t;
			static const std::array <game::block_state_t, 16> variants = {
				solid, q3_dn, q3_lt, q2_dl,
				q3_up, q2_lr, q2_ul, q1_lt,
				q3_rt, q2_dr, q2_ud, q1_dn,
				q2_ur, q1_rt, q1_up, empty
			};
			size_t flag = 0;
			for (size_t i = 0; i != 4; i++)
				flag += (adjacent[i].block_id == original.block_id) << i;
			return variants[flag];
		};

		tm->resize_and_clear(width, height);

		//tm.at(0, 0) = tile_t(1, 0, 0, 0);
		for (size_t i = 0; i != width; i++) {
			tm->at(i, 0) = game::tile_t(1, 0, 0, 0);
			tm->at(i, height - 1) = game::tile_t(1, 0, 0, 0);
		}

		for (size_t j = 1; j != height - 1; j++) {
			tm->at(0, j) = game::tile_t(1, 0, 0, 0);
			tm->at(width - 1, j) = game::tile_t(1, 0, 0, 0);
			for (size_t i = 1; i != tm->width() - 1; i++)
				tm->at(i, j) = game::tile_t(0, 0, 0, 0);
		}

		for (size_t i = 0; i != width; i++) {
			for (size_t j = 0; j != height; j++) {
				game::tile_t& current = tm->at(i, j);
				std::array <game::tile_t, 4> adjacent = {
					tm->at_try(i, j - 1),
					tm->at_try(i + 1, j),
					tm->at_try(i, j + 1),
					tm->at_try(i - 1, j)
				};
				current.block_type = (uint8_t)choose_type(current, adjacent);
			}
		}
	}
	void print(std::ostream& os, game::Tilemap& tm) {
		os << "width: " << tm->width() << "\nheight: " << tm->height() << '\n';
		for (size_t i = 0; i != tm->height(); i++) {
			for (size_t j = 0; j != tm->width(); j++)
				os << std::to_string(tm->at(j, i).block_type) << '\t';
			os << '\n';
		}
	}
	void init_console_functions(game::Console& console) {
		console.add_function("start", [&](std::istream& is) {
			engine::core->state_machine->add_state("game_state", std::make_shared <game::GameState>());
			engine::core->state_machine->set_update_level("game_state", 0);

			while (engine::core->flag)
				engine::core->state_machine->update();

			return 0;
		});
		console.add_function("stop", [&](std::istream& is) {
			engine::core->flag = false;
			return 0;
		});
		console.add_function("generate_tilemap", [&](std::istream& is) {
			auto tm = std::dynamic_pointer_cast <game_objects::BaseTilemap <game::tile_t>>(game::core->tilemap);
			generate(tm, 10, 10);
			return 0;
		});
	}
}

int main() {
	game::Console console;
	std::ifstream startup_file("res/startup.txt");

	game::core->init();
	util::init_console_functions(console);

	do {
		console.process(startup_file);
	} while (engine::core->flag);

	startup_file.close();
	game::core->release();
	return 0;
}