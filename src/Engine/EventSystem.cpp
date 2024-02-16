//engine
#include <Engine/EventSystem.hpp>

namespace engine {
	//TODO: check boundaries in insert and remove

	void EventControlBlock::insert_listener(event_id id, IListener listener) {
		this->m_listeners.emplace(id, listener);
	}
	void EventControlBlock::remove_listener(event_id id, IListener listener) {
		auto range = this->m_listeners.equal_range(id);
		for (auto it = range.first; it != range.second; it++)
			this->m_listeners.erase(it);
	}

	void EventControlBlock::insert_event(IEvent event) {
		this->m_events.push_back(event);
	}
	void EventControlBlock::remove_event(IEvent event) {
		auto it = std::find(this->m_events.begin(), this->m_events.end(), event);
		this->m_events.erase(it);
	}

	event_id EventControlBlock::get_event_id(std::string event_name) {
		auto it = this->m_id_table.find(event_name);
		if (it == this->m_id_table.end())
			this->m_id_table.emplace(event_name, this->m_hasher(event_name));
		return this->m_id_table[event_name];
	}

	void EventControlBlock::update() {
		for (auto& it : this->m_events)
			it->update();
	}
	
	void EventControlBlock::call(event_id id, std::any data) {
		auto range = this->m_listeners.equal_range(id);
		for (auto it = range.first; it != range.second; it++)
			it->second->call(data);
	}
}