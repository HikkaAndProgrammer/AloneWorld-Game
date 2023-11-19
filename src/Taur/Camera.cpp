#include "Camera.hpp"

//sf
#include <SFML/Graphics/VertexArray.hpp>

//taur
#include <Taur/Core.hpp>
#include <Taur/Util.hpp>

namespace taur {
	void Camera::render() {
		auto& tilemap = *m_observed;
		auto width = tilemap.width(), height = tilemap.width();
		//every quad tile consists of 2 triangles, triangle consists of 3 points
		auto request = sf::VertexArray(sf::Triangles, width * height * 6);

		for (size_t i = 0; i != height; i++) {
			for (size_t j = 0; j != width; j++) {
				tile_t tile = tilemap.at_try(j, i);
				size_t idx = (i * width + j) * 6, x = j * 8, y = i * 8, tx = 1 + (tile.block_state % 8) * 9, ty = 1 + tile.block_id * 36 + size_t(tile.block_state / 2) * 9;
				request[idx + 0] = util::create_vertex(x, y + 8, tx, ty + 8);
				request[idx + 1] = util::create_vertex(x, y, tx, ty);
				request[idx + 2] = util::create_vertex(x + 8, y, tx + 8, ty);
				request[idx + 3] = util::create_vertex(x + 8, y, tx + 8, ty);
				request[idx + 4] = util::create_vertex(x + 8, y + 8, tx + 8, ty + 8);
				request[idx + 5] = util::create_vertex(x, y + 8, tx, ty + 8);
			}
		}

		core.renderer.request(std::move(request), core.textures["tiles"]);
	}
}