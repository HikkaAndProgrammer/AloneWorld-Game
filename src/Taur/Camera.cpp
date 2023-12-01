#include <Taur/Camera.hpp>

//sf
#include <SFML/Graphics/VertexArray.hpp>

//taur
#include <Taur/Core.hpp>
#include <Taur/Util.hpp>

namespace taur {
	void Camera::render() {
		auto& tilemap = *this->m_observed;
		auto width = tilemap.width(), height = tilemap.width();
		//every quad tile consists of 2 triangles, triangle consists of 3 points
		auto request = sf::VertexArray(sf::Triangles, width * height * 6);

		for (size_t i = 0; i != width; i++) {
			for (size_t j = 0; j != height; j++) {
				tile_t tile = tilemap.at_try(i, j);
				if (!tile.block_id)
					continue;

				size_t idx = (i + j * width) * 6, 
					x = i * core.tile_size, 
					y = j * core.tile_size, 
					tx = 2 + (tile.block_type % 8) * (core.tile_size + 2), 
					ty = 2 + (tile.block_id - 1) * (core.tile_size + 2) * 4 + size_t(tile.block_type / 8) * (core.tile_size + 2);

				request[idx + 0] = util::create_vertex(x, y + core.tile_size, tx, ty + core.tile_size);
				request[idx + 1] = util::create_vertex(x, y, tx, ty);
				request[idx + 2] = util::create_vertex(x + core.tile_size, y, tx + core.tile_size, ty);
				request[idx + 3] = util::create_vertex(x + core.tile_size, y, tx + core.tile_size, ty);
				request[idx + 4] = util::create_vertex(x + core.tile_size, y + core.tile_size, tx + core.tile_size, ty + core.tile_size);
				request[idx + 5] = util::create_vertex(x, y + core.tile_size, tx, ty + core.tile_size);
			}
		}

		core.renderer.request(std::move(request), core.textures["tiles"]);
	}
}