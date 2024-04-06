#include <GameObjects/Camera.hpp>

//sf
#include <SFML/Graphics/VertexArray.hpp>

//engine
#include <Engine/GameManager.hpp>
#include <Engine/Util.hpp>

namespace game_objects {
	void BaseCamera::set_size(sf::Vector2f size) {
		this->m_size = size;
		this->m_view.setSize(this->m_size);
	}
	void BaseCamera::set_size(float width, float height) {
		this->m_size = sf::Vector2f(width, height);
		this->m_view.setSize(this->m_size);
	}
	void BaseCamera::set_position(sf::Vector2f position) {
		this->m_position = position;
		this->m_view.setCenter(this->m_position);
	}
	void BaseCamera::set_position(float x, float y) {
		this->m_position = sf::Vector2f(x, y);
		this->m_view.setCenter(this->m_position);
	}
}