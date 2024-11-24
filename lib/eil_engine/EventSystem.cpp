#include "EventSystem.hpp"

namespace eil::engine {
	void EventManager::insert_listener(const key_type& id, const IListener& listener) {
		m_listeners.emplace(id, listener);
	}
	void EventManager::remove_listener(const key_type& id) {
		m_listeners.erase(id);
	}

	void EventManager::call(const key_type& id, const std::any& data) const {
		auto [begin, end] = m_listeners.equal_range(id);
		for (auto it = begin; it != end; ++it)
			it->second->call(data);
	}

	void EventManager::insert_event(const key_type& id, const IEvent& event) {
		m_events.emplace(id, event);
	}
	void EventManager::remove_event(const key_type& id) {
		m_events.erase(id);
	}

	void EventManager::update() const {
		for (auto& it : m_events)
			it.second->update();
	}
}
