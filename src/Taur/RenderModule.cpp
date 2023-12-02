#include <Taur/Core.hpp>
#include <Taur/RenderModule.hpp>

namespace taur {
	void RenderModule::init() {
		this->m_target = &core.window;
		for (auto& it : *core.texture_manager) {
			this->m_requests.emplace(it.second, std::list <sf::VertexArray>());
		}
	}

	sf::RenderTarget& RenderModule::get_target() {
		return *this->m_target;
	}

	void RenderModule::request(sf::VertexArray&& data, std::shared_ptr<sf::Texture> atlas) {
		this->m_requests[atlas].push_back(data);
	}
	
	void RenderModule::begin() {

	}
	void RenderModule::end() {
		for (auto& it : this->m_requests) {
			it.second.clear();
		}
	}

	void RenderModule::draw() const {
		sf::RenderStates states;
		for (const auto& it : this->m_requests) {
			for (const auto& jt : it.second) {
				states.texture = it.first.get();
				this->m_target->draw(jt, states);
			}
		}
	}
}