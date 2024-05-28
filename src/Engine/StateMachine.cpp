#include "Engine/StateMachine.hpp"

#include <ranges>

namespace engine {
	void StateMachine::init(size_t process_levels) {
		this->m_process_levels.resize(process_levels);
	}

	void StateMachine::update() {
		bool is_recalculate_active_states = !this->m_requested_updates.empty();

		while(!this->m_requested_updates.empty()) {
			auto& [state, status] = this->m_requested_updates.front();
			
			using enum StateStatus;
			switch (status) {
			case OnCreate:
				state->on_create();
				break;
			case OnDelete:
				state->on_delete();
				break;
			case OnEnable:
				state->on_enable();
				state->is_active = true;
				break;
			case OnDisable:
				state->on_disable();
				state->is_active = false;
				break;
			}

			this->m_requested_updates.pop();
		}

		if (is_recalculate_active_states) {
			for (auto& [container, active_count] : this->m_process_levels) {
				active_count = 0;
				for (const auto& state : container)
					if (state->is_active)
						active_count++;
			}
		}

		for (auto& container : this->m_process_levels | std::views::keys) {
			auto& state = container.front();
			if (state->is_active)
				state->update();
		}
	}

	void StateMachine::add_state(std::string id, IState state) {
		this->m_states.emplace(id, state);
		this->request_status_change(id, StateStatus::OnCreate);
		state->is_active = false;
	}

	void StateMachine::request_status_change(const std::string& id, StateStatus status) {
		this->m_requested_updates.emplace(this->m_states[id], status);
	}

	void StateMachine::set_update_level(const std::string& state_id, size_t level) {
		auto state = m_states[state_id];
		auto& [container, flag] = this->m_process_levels[level];
		container.push_back(state);
	}
	void StateMachine::clear_update_level(size_t level) {
		auto& [container, flag] = this->m_process_levels[level];
		container.clear();
		flag = 0;
	}
}
