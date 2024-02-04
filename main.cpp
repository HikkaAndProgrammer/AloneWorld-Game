//std
#include <array>
#include <functional>
#include <iostream>
#include <memory>
#include <string>

//sf
#include <SFML/Window.hpp>

//taur
#include <Taur/GameManager.hpp>
#include <Taur/ThreadPool.hpp>

//game_objects
#include <GameObjects/Camera.hpp>
#include <GameObjects/Tilemap.hpp>

//script
#ifdef INCLUDE_SCRIPT_ENGINE
#include <chaiscript/chaiscript.hpp>
#endif

//game
#include <Game/Console.hpp>
#include <Game/RenderState.hpp>
#include <Game/Tile.hpp>
#include <Game/GameEngine.hpp>

using BasicTilemap = game_objects::Tilemap <game::tile_t>;

namespace taur {
	std::unique_ptr <GameManager> core = std::make_unique <game::GameEngine>();
}

namespace util {
	void generate(BasicTilemap& tm, size_t width, size_t height) {
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

		tm.resize_and_clear(width, height);

		//tm.at(0, 0) = tile_t(1, 0, 0, 0);
		for (size_t i = 0; i != width; i++) {
			tm.at(i, 0) = game::tile_t(1, 0, 0, 0);
			tm.at(i, height - 1) = game::tile_t(1, 0, 0, 0);
		}

		for (size_t j = 1; j != height - 1; j++) {
			tm.at(0, j) = game::tile_t(1, 0, 0, 0);
			tm.at(width - 1, j) = game::tile_t(1, 0, 0, 0);
			for (size_t i = 1; i != tm.width() - 1; i++)
				tm.at(i, j) = game::tile_t(0, 0, 0, 0);
		}

		for (size_t i = 0; i != width; i++) {
			for (size_t j = 0; j != height; j++) {
				game::tile_t& current = tm.at(i, j);
				std::array <game::tile_t, 4> adjacent = {
					tm.at_try(i, j - 1),
					tm.at_try(i + 1, j),
					tm.at_try(i, j + 1),
					tm.at_try(i - 1, j)
				};
				current.block_type = (uint8_t) choose_type(current, adjacent);
			}
		}
	}
	void print(std::ostream& os, BasicTilemap& tm) {
		os << "width: " << tm.width() << "\nheight: " << tm.height() << '\n';
		for (size_t i = 0; i != tm.height(); i++) {
			for (size_t j = 0; j != tm.width(); j++)
				os << std::to_string(tm.at(j, i).block_type) << '\t';
			os << '\n';
		}
	}
	void init_console_functions(game::Console& console) {
		console.add_function("start_game", [&](std::istream& is) {
			taur::core->state_machine->add_state("render_state", std::make_shared <game::RenderState>());
			taur::core->state_machine->set_render_level("render_state", 0);

			while (taur::core->flag) {
				taur::core->state_machine->update();
			}

			return 0;
		});
		console.add_function("compile_atlas", [&](std::istream& is) {


			return 0;
		});
		console.add_function("generate_texture", [&](std::istream& is) {


			return 0;
		});
	}
	void generate_atlas() {

	}
}

int main() {
	game::Console console;
	taur::core->init(false, false);

	do {
		console.process(std::cin);
	} while (taur::core->flag);

	taur::core->release();
	return 0;
}