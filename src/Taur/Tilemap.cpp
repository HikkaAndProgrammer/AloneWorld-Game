#include "Tilemap.hpp"

//std
#include <fstream>

//Taur
#include <Taur/Core.hpp>

namespace taur {
	void Tilemap::resize_and_clear(size_t width, size_t height) {
		m_width = width;
		m_height = height;
		m_content.clear();
		m_content.resize(m_width * m_height);
	}

	bool Tilemap::save(std::string path) const {
		std::ofstream file(path, std::ios::binary);

		if (!file.is_open())
			return false;

		file.write((char*)&m_width, sizeof(size_t)).write((char*)&m_height, sizeof(size_t));

		for (size_t i = 0; i != m_width * m_height; i++)
			file.write((char*)&m_content[i], sizeof(tile_t));

		file.close();
		return true;
	}
	bool Tilemap::load(std::string path) {
		std::ifstream file(path);

		if (!file.is_open())
			return false;

		file.read((char*)&m_width, sizeof(size_t)).read((char*)&m_height, sizeof(size_t));
		resize_and_clear(m_width, m_height);

		for (size_t i = 0; i != m_width * m_height; i++)
			file.read((char*)&m_content[i], sizeof(tile_t));

		file.close();
		return true;
	}
}
