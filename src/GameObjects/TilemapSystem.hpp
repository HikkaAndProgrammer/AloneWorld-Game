#pragma once
//std
#include <memory>
#include <vector>

//engine
#include "Engine/Util.hpp"

namespace game_objects {
	class TileBlank {
		template <class _TileType>
		friend class Tilemap;
	public:

	protected:
		std::shared_ptr <sf::Texture> m_texture;
	};

	//TODO: remake it with toml
	template <class _TileType>
	class BaseTilemap : public util::Renderable {
	public:
		_TileType& at(int64_t x, int64_t y) {
			return this->m_content.at(x + y * this->m_width);
		}
		const _TileType& at(int64_t x, int64_t y) const {
			return this->m_content.at(x + y * this->m_width);
		}

		_TileType at_try(int64_t x, int64_t y) const {
			if (x >= 0 && x < this->m_width && y >= 0 && y < this->m_height)
				return at(x, y);
			return _TileType();
		}

		void resize_and_clear(int64_t width, int64_t height) {
			this->m_width = width;
			this->m_height = height;
			this->m_content.clear();
			this->m_content.resize(this->m_width * this->m_height);
		}

		bool save(const std::string& filename) const {
			std::ofstream file(filename, std::ios::binary);

			if (!file.is_open())
				return false;

			file << this->m_width << ' ' << this->m_height << '\n';
			for (auto& it : this->m_content)
				it.write(file);

			file.close();
			return true;
		}
		bool load(const std::string& filename) {
			std::ifstream file(filename);

			if (!file.is_open())
				return false;

			file >> this->m_width >> this->m_height;
			this->resize_and_clear(this->m_width, this->m_height);
			for (auto& it : this->m_content)
				it.read(file);

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
	};
	
	template <class _TileType>
	using ITilemap = std::shared_ptr <BaseTilemap <_TileType>>;
}
