#include "Engine/RenderModule.hpp"

//engine
#include "Engine/GameManager.hpp"

namespace engine {
	void RenderModule::init() {
		this->m_target = core->window;
	}

	sf::RenderTarget& RenderModule::get_target() const {
		return *this->m_target;
	}

	void RenderModule::request(sf::VertexArray&& data, const std::shared_ptr <sf::Texture>& atlas) {
		this->m_requests.emplace_back(batch_t{ data, atlas });
	}

	void RenderModule::request(util::IDrawable drawable) {
		this->m_requests.emplace_back(drawable);
	}
	
	void RenderModule::begin() {}
	void RenderModule::end() {
		this->m_requests.clear();
	}

	void RenderModule::draw() const {
		sf::RenderStates states;
		for (const auto& request : this->m_requests) {
			std::visit(util::overload{
				[&](const batch_t& batch) {
					states.texture = batch.texture.get();
					this->m_target->draw(batch.vertices, states);
				},
				[&](const util::IDrawable& drawable) {
					this->m_target->draw(*drawable, states);
				}
			}, request);
		}
	}
}