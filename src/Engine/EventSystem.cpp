#include "Engine/EventSystem.hpp"

namespace engine {
	//TODO: check boundaries in insert and remove

	void EventControlBlock::insert_listener(event_id_t id, const IListener& listener) {
		this->m_listeners.emplace(id, listener);
	}
	void EventControlBlock::insert_listener(const std::string& event_name, const IListener& listener) {
		event_id_t id = this->get_event_id(event_name);
		this->insert_listener(id, listener);
	}
	void EventControlBlock::remove_listener(event_id_t id) {
		auto range = this->m_listeners.equal_range(id);
		for (auto it = range.first; it != range.second; it++)
			this->m_listeners.erase(it);
	}
	void EventControlBlock::remove_listener(const std::string& event_name, const IListener& listener) {
		event_id_t id = this->get_event_id(event_name);
		this->remove_listener(id);
	}

	void EventControlBlock::insert_event(const IEvent& event) {
		this->m_events.push_back(event);
	}
	void EventControlBlock::remove_event(const IEvent& event) {
		auto it = std::find(this->m_events.begin(), this->m_events.end(), event);
		this->m_events.erase(it);
	}

	event_id_t EventControlBlock::get_event_id(const std::string& event_name) {
		auto it = this->m_id_table.find(event_name);
		if (it == this->m_id_table.end())
			this->m_id_table.emplace(event_name, this->m_hasher(event_name));
		return this->m_id_table[event_name];
	}

	void EventControlBlock::update() {
		for (auto& it : this->m_events)
			it->update();
	}
	
	void EventControlBlock::call(event_id_t id, const std::any& data) {
		auto range = this->m_listeners.equal_range(id);
		for (auto it = range.first; it != range.second; it++)
			it->second->call(data);
	}
	void EventControlBlock::call(const std::string& event_name, const std::any& data) {
		event_id_t id = this->get_event_id(event_name);
		this->call(id, data);
	}
}