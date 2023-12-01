//taur
#include <Taur/Core.hpp>
#include <Taur/TextureModule.hpp>

//json
#include <nlohmann/json.hpp>

namespace taur {
	std::shared_ptr <sf::Texture> TextureManager::operator[](KeyType id) {
		return this->m_storage[id];
	}

	void TextureManager::load(std::string path) {
		std::ifstream file(path);
		nlohmann::json data = nlohmann::json::parse(file);
		file.close();

		auto path_prefix = data["path_prefix"].get <std::string>();
		const auto& atlas = data["atlas"].get <std::vector <nlohmann::json>>();
		for (const auto& it : atlas) {
			const auto& key = it["key"].get <std::string>();
			const auto& filename = it["val"].get <std::string>();
			std::shared_ptr <sf::Texture> value(new sf::Texture());
			
			value->loadFromFile(path_prefix + filename);
			this->m_storage.emplace(key, std::move(value));
		}
	}
}