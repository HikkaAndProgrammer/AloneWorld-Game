#pragma once
//engine
#include <GameObjects/Camera.hpp>
#include <GameObjects/Tilemap.hpp>

//game
#include <Game/Tile.hpp>
#include <Game/Core.hpp>

namespace game {
	class TilemapCamera : public game_objects::BaseCamera {
	public:
		void render() override {
			const auto& tile_size = core->tile_size;
			auto& tilemap = *this->m_observed;
			auto width = tilemap.width(), height = tilemap.height();
			//every quad tile consists of 2 triangles, triangle consists of 3 points
			auto request = sf::VertexArray(sf::Triangles, width * height * 6);

			for (size_t i = 0; i != width; i++) {
				for (size_t j = 0; j != height; j++) {
					tile_t tile = tilemap.at_try(i, j);
					if (!tile.block_id)
						continue;

					size_t idx = (i + j * width) * 6,
						x = i * tile_size,
						y = j * tile_size,
						tx = 2 + (tile.block_type % 8) * (tile_size + 2),
						ty = 2 + (tile.block_id - 1) * (tile_size + 2) * 4 + size_t(tile.block_type / 8) * (tile_size + 2);

					request[idx + 0] = util::create_vertex(x, y + tile_size, tx, ty + tile_size);
					request[idx + 1] = util::create_vertex(x, y, tx, ty);
					request[idx + 2] = util::create_vertex(x + tile_size, y, tx + tile_size, ty);
					request[idx + 3] = util::create_vertex(x + tile_size, y, tx + tile_size, ty);
					request[idx + 4] = util::create_vertex(x + tile_size, y + tile_size, tx + tile_size, ty + tile_size);
					request[idx + 5] = util::create_vertex(x, y + tile_size, tx, ty + tile_size);
				}
			}

			core->render_module->request(std::move(request), core->texture_manager->at("tiles"));
		}

		void link(Tilemap tilemap) {
			this->m_observed = tilemap;
		}

	protected:
		Tilemap m_observed = nullptr;
	};
}