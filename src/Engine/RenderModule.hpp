#pragma once
//std
#include <list>
#include <memory>
#include <variant>

//sf
#include <SFML/Graphics.hpp>

//engine
#include <Engine/Util.hpp>

namespace engine {
	struct batch_t {
		sf::VertexArray vertices;
		std::shared_ptr <sf::Texture> texture;
	};
	using request_t = std::variant <batch_t, util::IDrawable>;

	class RenderModule {
	public:
		sf::RenderTarget& get_target() const;

		void init();

		void request(sf::VertexArray&& data, const std::shared_ptr <sf::Texture>& atlas);
		void request(util::IDrawable drawable);

		void begin();
		void end();

		void draw() const;

	protected:
		std::shared_ptr <sf::RenderTarget> m_target;
		std::list <request_t> m_requests;
	};
}