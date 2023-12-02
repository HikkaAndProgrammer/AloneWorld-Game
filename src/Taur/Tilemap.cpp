#include <Taur/Tilemap.hpp>

//std
#include <fstream>

//Taur
#include <Taur/Core.hpp>

namespace taur {
	//tile_t

	tile_t::tile_t() {
		block_id = 0;
		wall_id = 0;
		block_type = 0;
		wall_type = 0;
	}
	tile_t::tile_t(size_t bid, uint8_t bs, size_t wid, size_t ws) {
		block_id = bid;
		block_type = bs;
		wall_id = wid;
		wall_type = ws;
	}

	//Tilemap

	tile_t& Tilemap::at(size_t x, size_t y) { 
		return this->m_content.at(x + y * this->m_width); 
	}
	const tile_t& Tilemap::at(size_t x, size_t y) const { 
		return this->m_content.at(x + y * this->m_width); 
	}

	tile_t Tilemap::at_try(size_t x, size_t y) const {
		if (x >= 0 && x < this->m_width && y >= 0 && y < this->m_height)
			return at(x, y);
		return nulled;
	}

	void Tilemap::resize_and_clear(size_t width, size_t height) {
		this->m_width = width;
		this->m_height = height;
		this->m_content.clear();
		this->m_content.resize(this->m_width * this->m_height);
	}

	bool Tilemap::save(std::string path) const {
		std::ofstream file(path, std::ios::binary);

		if (!file.is_open())
			return false;

		file.write((char*)&this->m_width, sizeof(size_t)).write((char*)&this->m_height, sizeof(size_t));

		for (size_t i = 0; i != this->m_content.size(); i++)
			file.write((char*)&this->m_content[i], sizeof(tile_t));

		file.close();
		return true;
	}
	bool Tilemap::load(std::string path) {
		std::ifstream file(path);

		if (!file.is_open())
			return false;

		file.read((char*)&this->m_width, sizeof(size_t)).read((char*)&this->m_height, sizeof(size_t));
		resize_and_clear(this->m_width, this->m_height);

		for (size_t i = 0; i != this->m_content.size(); i++)
			file.read((char*)&this->m_content[i], sizeof(tile_t));

		file.close();
		return true;
	}

	size_t Tilemap::width() const { 
		return this->m_width; 
	}
	size_t Tilemap::height() const { 
		return this->m_height; 
	}

	const tile_t Tilemap::nulled = tile_t(0, 0, 0, 0);
}
