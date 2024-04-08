#pragma once
//std
#include <memory>
#include <cmath>

//sf
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/View.hpp>

namespace game_objects {
	class BaseCamera {
	public:
		sf::Vector2f get_size() const { return this->m_view.getSize(); }
		void set_size(float width, float height) { this->m_view.setSize(width, height); }
		sf::Vector2f get_position() const { return this->m_position; }
		void set_position(float x, float y) {
			this->m_position = { x, y };
			this->_update_position();
		}

		void move(float x, float y) { this->m_offset = { x, y }; }
		
		const sf::View& view() const { return this->m_view; }

		virtual void update() {
			this->m_position += this->m_offset;
			this->_update_position();
			this->m_offset = { 0, 0 };
		}
		virtual void render() = 0;

	protected:
		sf::Vector2f m_position, m_offset;
		sf::View m_view;

	private:
		void _update_position() {
			if (std::fmodf(this->m_position.x, 1.f) != 0)
				this->m_position.x = std::roundf(this->m_position.x);
			if (std::fmodf(this->m_position.y, 1.f) != 0)
				this->m_position.y = std::roundf(this->m_position.y);
			this->m_view.setCenter(this->m_position);
		}
	};
	using ICamera = std::shared_ptr <BaseCamera>;
}