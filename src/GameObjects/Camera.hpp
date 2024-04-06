#pragma once
//std
#include <memory>

//sf
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/View.hpp>

namespace game_objects {
	class BaseCamera {
	public:
		void set_size(sf::Vector2f size);
		void set_size(float width, float height);
		void set_position(sf::Vector2f position);
		void set_position(float x, float y);

		sf::Vector2f& offset() {
			return this->m_offset;
		}
		const sf::Vector2f& offset() const {
			return this->m_offset;
		}
		sf::View& view() {
			return this->m_view;
		}
		const sf::View& view() const {
			return this->m_view;
		}

		virtual void render() = 0;

	protected:
		//position is center, offset is for drawing
		sf::Vector2f m_position, m_size, m_offset;
		sf::View m_view;
	};
	using ICamera = std::shared_ptr <BaseCamera>;
}