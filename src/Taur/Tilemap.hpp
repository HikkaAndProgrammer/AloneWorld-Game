#pragma once
//std
#include <vector>
#include <algorithm>

//sf
#include <SFML/Graphics.hpp>

//nlohman
#include <nlohmann/json.hpp>

namespace taur {
	enum class block_state_t : uint8_t {
		solid = 0x00,
		blank = 0x01,
		q2_lr = 0x02, //quad 2 left and right
		q2_ud = 0x03, //quad 2 upper and down
		q1_lt = 0x08, //quad 1 left
		q1_dn = 0x09, //quad 1 down
		q1_rt = 0x0A, //quad 1 right
		q1_up = 0x0B, //quad 1 upper
		q3_lt = 0x10, //quad 3 left
		q3_dn = 0x11, //quad 3 down
		q3_rt = 0x12, //quad 3 right
		q3_up = 0x13, //quad 3 upper
		q2_dl = 0x18, //quad 2 down-left
		q2_dr = 0x19, //quad 2 down-right
		q2_ur = 0x1A, //quad 2 upper-right
		q2_ul = 0x1B, //quad 2 upper-left

		t1_dr = 0x04, //triangle 1 down-right
		t1_ur = 0x05, //triangle 1 upper-right
		t1_ul = 0x06, //triangle 1 upper-left
		t1_dl = 0x07, //triangle 1 down-left
		t2_rf = 0x0C, //triangle 2 right forward
		t2_uf = 0x0D, //triangle 2 upper forward
		t2_lf = 0x0E, //triangle 2 left forward
		t2_df = 0x0F, //triangle 2 down forward
		t2_di = 0x14, //triangle 2 down inverse
		t2_ri = 0x15, //triangle 2 right inverse
		t2_ui = 0x16, //triangle 2 upper inverse
		t2_li = 0x17, //triangle 2 left inverse
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
			block_state = 0;
			wall_state = 0;
		}

		tile_t(size_t bid, uint8_t bs, size_t wid, size_t ws) {
			block_id = bid;
			block_state = bs;
			wall_id = wid;
			wall_state = ws;
		}

		size_t block_id, wall_id;
		uint8_t block_state, wall_state;
	};

	class TileBlank {
		friend class Tilemap;
	public:

	protected:
		std::shared_ptr <sf::Texture> m_texture;
	};

	class Tilemap {
	public:
		tile_t& at(size_t x, size_t y) { return m_content.at(x + y * m_width); }
		const tile_t& at(size_t x, size_t y) const { return m_content.at(x + y * m_width); }

		tile_t at_try(size_t x, size_t y) {
			if (x >= 0 && x < m_width && y >= 0 && y < m_height)
				return at(x, y);
			return nulled;
		}
		const tile_t& at_try(size_t x, size_t y) const {
			if (x >= 0 && x < m_width && y >= 0 && y < m_height)
				return at(x, y);
			return nulled;
		}

		void resize_and_clear(size_t width, size_t height);

		bool save(std::string filename) const;
		bool load(std::string filename);

		size_t width() { return m_width; }
		size_t height() { return m_height; }

	protected:
		std::vector <tile_t> m_content;
		std::vector <TileBlank> m_catalog;
		size_t m_width = 0, m_height = 0;
		const size_t tile_size = 16;
		const tile_t nulled = tile_t(0, 0, 0, 0);
	};
}
