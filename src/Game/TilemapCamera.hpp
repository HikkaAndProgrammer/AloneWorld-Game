#pragma once
//std
#include <cmath>
#include <cstdint>

//engine
#include <GameObjects/Camera.hpp>
#include <GameObjects/Tilemap.hpp>

//game
#include <Game/Core.hpp>
#include <Game/Tile.hpp>

namespace game {
	class TilemapCamera : public game_objects::BaseCamera {
	public:
		void render() override {
			auto tile_size = core->tile_size;
			auto& tilemap = this->m_observed;
			auto size = this->get_size();
			auto position = this->get_position();
			int64_t x0 = std::floor((position.x - size.x / 2) / tile_size), 
				x1 = std::ceil((position.x + size.x / 2) / tile_size),
				y0 = std::floor((position.y - size.y / 2) / tile_size),
				y1 = std::ceil((position.y + size.y / 2) / tile_size);
			//every quad tile consists of 2 triangles, triangle consists of 3 points
			auto request = sf::VertexArray(sf::Triangles, (x1 - x0) * (y1 - y0) * 6);

			for (int64_t i = x0; i <= x1; i++) {
				for (int64_t j = y0; j <= y1; j++) {
					tile_t tile = tilemap->at_try(i, j);
					if (!tile.block_id)
						continue;

					size_t idx = (i + j * (x1 - x0)) * 6,
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

		Tilemap& tilemap() { return this->m_observed; }
		const Tilemap& tilemap() const { return this->m_observed; }

	protected:
		Tilemap m_observed = nullptr;
	};
}