#pragma once
//std
#include <atomic>
#include <condition_variable>
#include <list>
#include <memory>
#include <mutex>
#include <string>
#include <unordered_map>
#include <vector>

//taur
#include <Taur/Util.hpp>

namespace taur {
	enum class StateStatus {
		Idle = 0,
		Active = 1,
		OnCreate,
		OnDelete,
		Count = 6
	};

	class BaseState : public util::Updatable {
		friend class StateMachine;
	public:
		virtual ~BaseState () {}

		virtual void onEnable() {}
		virtual void onDisable() {}

		virtual void onCreate() {}
		virtual void onDetele() {}

	private:
		StateStatus m_current_status, m_new_status;
	};
	using IState = std::shared_ptr <BaseState>;

	class StateMachine {
	public:
		void init(size_t render_levels) { this->m_process_levels.resize(render_levels); }

		void update();

		void request(std::string id, StateStatus status) {
			auto state = this->m_states[id];
			if (state->m_current_status != status && state->m_new_status != status)
				this->m_pending.emplace_back(state, status);
		}

		void set_render_level(std::string state_id, size_t level) {
			auto state = m_states[state_id];
			this->m_process_levels[level].push_back({ state, false });
		}
		void clear_render_level(size_t level) {
			this->m_process_levels[level].clear();
		}

	protected:
		std::unordered_map <std::string, IState> m_states;
		std::vector <std::list <std::pair <IState, std::atomic_bool>>> m_process_levels;
		std::list <std::pair <IState, StateStatus>> m_pending;

		std::mutex m_mutex;
		std::condition_variable m_cv;
	};
}