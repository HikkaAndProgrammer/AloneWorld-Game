#include <Taur/RenderModule.hpp>

//taur
#include <Taur/GameManager.hpp>

namespace taur {
	void RenderModule::init() {
		this->m_target = &core->window;
	}

	sf::RenderTarget& RenderModule::get_target() {
		return *this->m_target;
	}

	void RenderModule::request(sf::VertexArray&& data, std::shared_ptr <sf::Texture> atlas) {
		this->m_requests.emplace_back(data, atlas);
	}
	
	void RenderModule::begin() {

	}
	void RenderModule::end() {
		this->m_requests.clear();
	}

	void RenderModule::draw() const {
		sf::RenderStates states;
		for (const auto& request : this->m_requests) {
			states.texture = request.texture.get();
			this->m_target->draw(request.vertices, states);
		}
	}
}