#pragma once
//sf
#include <SFML/System/Vector2.hpp>

//taur
#include <Taur/Tilemap.hpp>

namespace taur {
	class Camera {
	public:
		void link(Tilemap* observed) {
			m_observed = observed;
		}

		void set_offset(sf::Vector2f offset) {
			this->m_offset = offset;
		}
		void set_size(sf::Vector2f size) {
			this->m_size = size;
			m_view.setSize(size);
		}
		void set_position(sf::Vector2f position) {
			m_position = position;
			m_view.setCenter(position);
		}

		sf::View& get_view() {
			return m_view;
		}
		const sf::View& get_view() const {
			return m_view;
		}

		void move(sf::Vector2f offset) {
			m_position.x += offset.x;
			m_position.y += offset.y;
		}

		void render();

	protected:
		//position is center, offset is for drawing
		sf::Vector2f m_position, m_size, m_offset;
		sf::View m_view;
		Tilemap* m_observed;
	};
}