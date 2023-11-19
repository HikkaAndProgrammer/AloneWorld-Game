#include <Taur/RenderModule.hpp>
#include <Taur/Core.hpp>

namespace taur {
	void Renderer::init() {
		m_target = &core.window;
		for (auto& it : core.textures) {
			m_requests.emplace(it.second, std::list <sf::VertexArray>());
		}
	}

	sf::RenderTarget& Renderer::get_target() {
		return *m_target;
	}

	void Renderer::request(sf::VertexArray&& data, std::shared_ptr<sf::Texture> atlas) {
		m_requests[atlas].push_back(data);
	}
	
	void Renderer::begin() {

	}
	void Renderer::end() {
		for (auto& it : m_requests) {
			it.second.clear();
		}
	}

	void Renderer::draw() const {
		sf::RenderStates states;
		for (const auto& it : m_requests) {
			for (const auto& jt : it.second) {
				states.texture = it.first.get();
				m_target->draw(jt, states);
			}
		}
	}
}