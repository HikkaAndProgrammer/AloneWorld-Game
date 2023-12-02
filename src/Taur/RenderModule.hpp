#pragma once
//std
#include <memory>
#include <list>
#include <unordered_map>

//sf
#include <SFML/Graphics.hpp>

namespace taur {
	class RenderModule {
	public:
		sf::RenderTarget& get_target();

		void init();

		void request(sf::VertexArray&& data, std::shared_ptr <sf::Texture> atlas);

		void begin();
		void end();

		void draw() const;

	protected:
		sf::RenderTarget* m_target;
		std::unordered_map <std::shared_ptr <sf::Texture>, std::list <sf::VertexArray>> m_requests;
	};
}