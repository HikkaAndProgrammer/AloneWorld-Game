#pragma once
//engine
#include "Engine/GameManager.hpp"

//game_objects
#include "GameObjects/TilemapSystem.hpp"

namespace game {
	enum class block_state_t : uint8_t {
		solid = 0x00,
		empty = 0x01,
		q2_lr = 0x02, //quad 2 left and right
		q2_ud = 0x03, //quad 2 upper and down
		q1_lt = 0x04, //quad 1 left
		q1_dn = 0x05, //quad 1 down
		q1_rt = 0x06, //quad 1 right
		q1_up = 0x07, //quad 1 upper
		q2_dl = 0x08, //quad 2 down-left
		q2_dr = 0x09, //quad 2 down-right
		q2_ur = 0x0A, //quad 2 upper-right
		q2_ul = 0x0B, //quad 2 upper-left
		q3_lt = 0x0C, //quad 3 left
		q3_dn = 0x0D, //quad 3 down
		q3_rt = 0x0E, //quad 3 right
		q3_up = 0x0F, //quad 3 upper

		t1_dr = 0x10, //triangle 1 down-right
		t1_ur = 0x11, //triangle 1 upper-right
		t1_ul = 0x12, //triangle 1 upper-left
		t1_dl = 0x13, //triangle 1 down-left
		t2_rf = 0x14, //triangle 2 right forward
		t2_uf = 0x15, //triangle 2 upper forward
		t2_lf = 0x16, //triangle 2 left forward
		t2_df = 0x17, //triangle 2 down forward
		t2_di = 0x18, //triangle 2 down inverse
		t2_ri = 0x19, //triangle 2 right inverse
		t2_ui = 0x1A, //triangle 2 upper inverse
		t2_li = 0x1B, //triangle 2 left inverse
		t3_dr = 0x1C, //triangle 3 down-right
		t3_ur = 0x1D, //triangle 3 upper-right
		t3_ul = 0x1E, //triangle 3 upper-left
		t3_dl = 0x1F, //triangle 3 down-left

		count = 0x20
	};

	struct tile_t {
		tile_t() {
			block_id = 0;
			wall_id = 0;
			block_type = 0;
			wall_type = 0;
		}
		tile_t(size_t bid, uint8_t bs, size_t wid, size_t ws) {
			block_id = bid;
			block_type = bs;
			wall_id = wid;
			wall_type = ws;
		}

		size_t block_id, wall_id;
		uint8_t block_type, wall_type;

		void read(std::istream& is) {
			int bt, wt;
			is >> block_id >> bt >> wall_id >> wt;
			block_type = bt;
			wall_type = wt;
		}
		void write(std::ostream& os) const {
			os << block_id << ' ' << (int)block_type << ' ' << wall_id << ' ' << (int)wall_type << ' ';
		}
	};

	class GameTilemap : public game_objects::BaseTilemap <tile_t> {
	public:
		void render() const override {
			auto tile_size = this->tile_size;
			const auto& view = engine::core->camera->view();
			auto size = view.getSize();
			auto position = view.getCenter();
			int64_t x0 = std::floor((position.x - size.x / 2) / tile_size),
				x1 = std::ceil((position.x + size.x / 2) / tile_size),
				y0 = std::floor((position.y - size.y / 2) / tile_size),
				y1 = std::ceil((position.y + size.y / 2) / tile_size);
			//every quad tile consists of 2 triangles, triangle consists of 3 points
			auto request = sf::VertexArray(sf::Triangles, (x1 - x0) * (y1 - y0) * 6);

			for (int64_t i = x0; i <= x1; i++) {
				for (int64_t j = y0; j <= y1; j++) {
					tile_t tile = this->at_try(i, j);
					if (!tile.block_id)
						continue;

					size_t idx = (i + j * (x1 - x0)) * 6;
					float x = i * tile_size,
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

			engine::core->render_module->request(std::move(request), engine::core->texture_manager->at("tiles"));
		}

	private:
		const float tile_size = 16.f;
	};
}