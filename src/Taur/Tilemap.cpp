#include <Taur/Tilemap.hpp>

//std
#include <fstream>

//Taur
#include <Taur/Core.hpp>

namespace taur {
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

		for (size_t i = 0; i != this->m_content.size();; i++)
			file.read((char*)&this->m_content[i], sizeof(tile_t));

		file.close();
		return true;
	}

	const tile_t Tilemap::nulled = tile_t(0, 0, 0, 0);
}
