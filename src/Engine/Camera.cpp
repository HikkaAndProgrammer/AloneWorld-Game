#include "Engine/Camera.hpp"

//std
#include <cmath>

namespace engine {
	sf::Vector2f Camera::get_size() const { 
		return this->m_view.getSize(); 
	}
	void Camera::set_size(float width, float height) { 
		this->m_view.setSize(width, height); 
	}

	sf::Vector2f Camera::get_position() const { 
		return this->m_position; 
	}
	void Camera::set_position(float x, float y) {
		this->m_position = { x, y };
		this->_correct_position();
	}

	void Camera::move(float x, float y) { 
		this->m_offset = { x, y }; 
	}

	const sf::View& Camera::view() const { 
		return this->m_view; 
	}

	void Camera::update() {
		this->m_position += this->m_offset;
		this->_correct_position();
		this->m_offset = { 0, 0 };
	}

	void Camera::_correct_position() {
		if (std::fmodf(this->m_position.x, 1.f) != 0)
			this->m_position.x = std::roundf(this->m_position.x);
		if (std::fmodf(this->m_position.y, 1.f) != 0)
			this->m_position.y = std::roundf(this->m_position.y);
		this->m_view.setCenter(this->m_position);
	}
}