#include "TextureManager.hpp"

//toml
#include <toml.hpp>

namespace eil::engine {
	bool TextureManager::init(const std::string& folder_path) {
		bool result = true;
		toml::value data = toml::parse(folder_path + "info.toml");

		for (const auto& it : data.at("atlas").as_array()) {
			auto key = it.at("key").as_string();
			auto filename = it.at("filename").as_string();
			auto val = std::make_shared<sf::Texture>();

			val->loadFromFile(folder_path + filename);
			m_storage.emplace(key, val);
		}

		return result;
	}

	texture_ptr TextureManager::at(const std::string& id) const {
		return m_storage.at(id);
	}
}
