#include <Taur/RenderModule.hpp>
#include <Taur/Core.hpp>

namespace taur {
	void Renderer::init() {
		this->m_target = &core.window;
		for (auto& it : core.textures) {
			this->m_requests.emplace(it.second, std::list <sf::VertexArray>());
		}
	}

	sf::RenderTarget& Renderer::get_target() {
		return *this->m_target;
	}

	void Renderer::request(sf::VertexArray&& data, std::shared_ptr<sf::Texture> atlas) {
		this->m_requests[atlas].push_back(data);
	}
	
	void Renderer::begin() {

	}
	void Renderer::end() {
		for (auto& it : this->m_requests) {
			it.second.clear();
		}
	}

	void Renderer::draw() const {
		sf::RenderStates states;
		for (const auto& it : this->m_requests) {
			for (const auto& jt : it.second) {
				states.texture = it.first.get();
				this->m_target->draw(jt, states);
			}
		}
	}
}