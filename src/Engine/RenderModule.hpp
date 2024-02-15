#pragma once
//std
#include <memory>
#include <list>

//sf
#include <SFML/Graphics.hpp>

namespace engine {
	struct request_t {
		sf::VertexArray vertices;
		std::shared_ptr <sf::Texture> texture;
	};

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
		std::list <request_t> m_requests;
	};
}