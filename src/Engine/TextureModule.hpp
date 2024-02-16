#pragma once
//std
#include <fstream>
#include <memory>
#include <string>
#include <unordered_map>

//sf
#include <SFML/Graphics/Texture.hpp>

namespace engine {
	

	class TextureManager {
	public:
		using KeyType = std::string;

		std::shared_ptr <sf::Texture> operator[](KeyType id);
		std::shared_ptr <sf::Texture> at(KeyType id);

		//void init();
		void load(std::string path);

		std::unordered_map <KeyType, std::shared_ptr <sf::Texture>>::iterator begin();
		std::unordered_map <KeyType, std::shared_ptr <sf::Texture>>::iterator end();

	private:
		std::unordered_map <KeyType, std::shared_ptr <sf::Texture>> m_storage;
	};
}