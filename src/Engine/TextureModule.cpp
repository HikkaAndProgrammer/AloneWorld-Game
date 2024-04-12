#include "Engine/TextureModule.hpp"

//std
#include <fstream>

//toml
#include <toml.hpp>

namespace engine {
	std::shared_ptr <sf::Texture> TextureManager::operator[](const KeyType& id) {
		return this->m_storage[id];
	}

	std::shared_ptr <sf::Texture> TextureManager::at(const KeyType& id) {
		return this->m_storage[id];
	}

	void TextureManager::load(const std::string& path) {
		toml::value data = toml::parse(path);
		auto& path_prefix = data["path_prefix"].as_string();

		for (auto& it : data["atlas"].as_array()) {
			auto& key = it["key"].as_string();
			auto& filename = it["filename"].as_string();
			std::shared_ptr <sf::Texture> value(new sf::Texture());

			value->loadFromFile(path_prefix.str + filename.str);
			this->m_storage.emplace(key, std::move(value));
		}
	}
	std::unordered_map <TextureManager::KeyType, std::shared_ptr <sf::Texture>>::iterator TextureManager::begin() {
		return this->m_storage.begin();
	}
	std::unordered_map <TextureManager::KeyType, std::shared_ptr <sf::Texture>>::iterator TextureManager::end() {
		return this->m_storage.end();
	}
}