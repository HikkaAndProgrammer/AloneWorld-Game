#pragma once
//std
#include <memory>
#include <cmath>

//sf
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/View.hpp>

namespace engine {
	class Camera {
	public:
		sf::Vector2f get_size() const;
		void set_size(float width, float height);
		sf::Vector2f get_position() const;
		void set_position(float x, float y);

		void move(float x, float y);
		
		const sf::View& view() const;

		virtual void update();

	protected:
		sf::Vector2f m_position, m_offset;
		sf::View m_view;

	private:
		void _correct_position();
	};
	using ICamera = std::shared_ptr <Camera>;
}