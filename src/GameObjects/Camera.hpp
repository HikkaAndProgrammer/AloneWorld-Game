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
		sf::Vector2f get_position() const { return this->m_view.getCenter(); }
		void set_position(float x, float y) { this->m_view.setCenter(x, y); }

		void move(float x, float y) { this->m_offset = { x, y }; }
		
		const sf::View& view() const { return this->m_view; }

		//TODO: every 1x + 0.5 steps position of tiles has white span
		virtual void update() {
			auto position = this->m_view.getCenter() + this->m_offset;
			auto dx = std::fabs(std::fmodf(position.x, 1.f)), dy = std::fabs(std::fmodf(position.y, 1.f));
			if (dx >= 0.48f && dx <= 0.52f) {
				position.x += this->min_sc;
				this->m_x_sc = true;
			} else if (this->m_x_sc) {
				position.x -= this->min_sc;
				this->m_x_sc = false;
			}
			if (dx >= 0.48f && dx <= 0.52f) {
				position.y += this->min_sc;
				this->m_y_sc = true;
			} else if (this->m_y_sc) {
				position.x -= this->min_sc;
				this->m_y_sc = false;
			}

			this->m_view.setCenter(position);
			this->m_offset = { 0, 0 };
		}
		virtual void render() = 0;

	protected:
		//position is center, offset is for drawing
		const float min_sc = std::powf(10, -5);
		bool m_x_sc = false, m_y_sc = false;
		sf::Vector2f m_position, m_offset;
		sf::View m_view;
	};
	using ICamera = std::shared_ptr <BaseCamera>;
}