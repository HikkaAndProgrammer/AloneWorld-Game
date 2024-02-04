#pragma once
//std
#include <algorithm>
#include <vector>

//sf
#include <SFML/Graphics.hpp>

//nlohman
#include <nlohmann/json.hpp>

namespace game_objects {
	class TileBlank {
		template <class _TileType>
		friend class Tilemap;
	public:

	protected:
		std::shared_ptr <sf::Texture> m_texture;
	};

	template <class _TileType>
	class Tilemap {
	public:
		_TileType& at(size_t x, size_t y) {
			return this->m_content.at(x + y * this->m_width);
		}
		const _TileType& at(size_t x, size_t y) const {
			return this->m_content.at(x + y * this->m_width);
		}

		_TileType at_try(size_t x, size_t y) const {
			if (x >= 0 && x < this->m_width && y >= 0 && y < this->m_height)
				return at(x, y);
			return _TileType();
		}

		void resize_and_clear(size_t width, size_t height) {
			this->m_width = width;
			this->m_height = height;
			this->m_content.clear();
			this->m_content.resize(this->m_width * this->m_height);
		}

		bool save(std::string filename) const {
			std::ofstream file(filename, std::ios::binary);

			if (!file.is_open())
				return false;

			file.write((char*)&this->m_width, sizeof(size_t)).write((char*)&this->m_height, sizeof(size_t));

			for (size_t i = 0; i != this->m_content.size(); i++)
				file.write((char*)&this->m_content[i], sizeof(_TileType));

			file.close();
			return true;
		}
		bool load(std::string filename) {
			std::ifstream file(filename);

			if (!file.is_open())
				return false;

			file.read((char*)&this->m_width, sizeof(size_t)).read((char*)&this->m_height, sizeof(size_t));
			resize_and_clear(this->m_width, this->m_height);

			for (size_t i = 0; i != this->m_content.size(); i++)
				file.read((char*)&this->m_content[i], sizeof(_TileType));

			file.close();
			return true;
		}

		size_t width() const {
			return this->m_width;
		}
		size_t height() const {
			return this->m_height;
		}

	protected:
		std::vector <_TileType> m_content;
		std::vector <TileBlank> m_catalog;
		size_t m_width = 0, m_height = 0;
		const size_t tile_size = 16;
	};
}
