#pragma once
//std
#include <memory>
#include <string>
#include <unordered_map>

//sf
#include <SFML/Graphics/Texture.hpp>

namespace eil::engine {
	using texture_ptr = std::shared_ptr<sf::Texture>;

	class TextureManager {
	public:
		bool init(const std::string& folder_path);

		texture_ptr at(const std::string& id) const;

	private:
		std::unordered_map<std::string, texture_ptr> m_storage;
	};
}