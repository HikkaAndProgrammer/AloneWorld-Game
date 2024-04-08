#pragma once
//std
#include <memory>

//sf
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/View.hpp>

namespace game_objects {
	class BaseCamera {
	public:
		sf::Vector2f get_size() const { return this->m_view.getSize(); }
		void set_size(float width, float height) { this->m_view.setSize(width, height); }
		sf::Vector2f get_position() const { return this->m_view.getCenter(); }
		void set_position(float x, float y) { this->m_view.setCenter(x, y); }

		void move(float x, float y) { this->m_offset = { x, y }; }
		
		const sf::View& view() const { return this->m_view; }

		virtual void update() {
			this->m_view.move(this->m_offset);
			this->m_offset = { 0, 0 };
		}
		virtual void render() = 0;

	protected:
		//position is center, offset is for drawing
		sf::Vector2f m_offset;
		sf::View m_view;
	};
	using ICamera = std::shared_ptr <BaseCamera>;
}