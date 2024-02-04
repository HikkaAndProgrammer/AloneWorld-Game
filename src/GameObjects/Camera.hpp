#pragma once
//std
#include <memory>

//sf
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/View.hpp>

namespace game_objects {
	class BaseCamera {
	public:
		void set_offset(sf::Vector2f offset);
		void set_size(sf::Vector2f size);
		void set_position(sf::Vector2f position);

		sf::View& get_view();
		const sf::View& get_view() const;

		void move(sf::Vector2f offset);

		virtual void render() = 0;

	protected:
		//position is center, offset is for drawing
		sf::Vector2f m_position, m_size, m_offset;
		sf::View m_view;
	};
	using ICamera = std::shared_ptr <BaseCamera>;
}