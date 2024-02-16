#include <GameObjects/Camera.hpp>

//sf
#include <SFML/Graphics/VertexArray.hpp>

//engine
#include <Engine/GameManager.hpp>
#include <Engine/Util.hpp>

namespace game_objects {
	void BaseCamera::set_offset(sf::Vector2f offset) {
		this->m_offset = offset;
	}
	void BaseCamera::set_size(sf::Vector2f size) {
		this->m_size = size;
		this->m_view.setSize(size);
	}
	void BaseCamera::set_position(sf::Vector2f position) {
		this->m_position = position;
		this->m_view.setCenter(position);
	}

	sf::View& BaseCamera::get_view() {
		return this->m_view;
	}
	const sf::View& BaseCamera::get_view() const {
		return this->m_view;
	}

	void BaseCamera::move(sf::Vector2f offset) {
		this->m_position.x += offset.x;
		this->m_position.y += offset.y;
	}
}