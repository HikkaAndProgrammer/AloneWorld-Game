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
#include <queue>

//taur
#include <Taur/Util.hpp>

namespace taur {
	enum class StateStatus {
		OnEnable = 0,
		OnDisable = 1,
		OnCreate,
		OnDelete,
		Count
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
		bool is_active;
	};
	using IState = std::shared_ptr <BaseState>;

	class StateMachine {
	public:
		void init(size_t process_levels) { this->m_process_levels.resize(process_levels); }
		//void startup();
		void update();

		void add_state(std::string id, IState state) {
			this->m_states.emplace(id, state);
			this->request_status_change(id, StateStatus::OnCreate);
			state->is_active = false;
		}

		void request_status_change(std::string id, StateStatus status) {
			this->m_requested_updates.emplace(this->m_states[id], status);
		}

		void set_render_level(std::string state_id, size_t level) {
			auto state = m_states[state_id];
			this->m_process_levels[level].push_back(state);
		}
		void clear_render_level(size_t level) {
			this->m_process_levels[level].clear();
		}

	protected:
		std::unordered_map <std::string, IState> m_states;
		std::vector <std::vector <IState>> m_process_levels;
		std::queue <std::pair <IState, StateStatus>> m_requested_updates;

		std::mutex m_mutex;
		std::condition_variable m_cv;
		std::atomic_size_t m_active_states = 0;
	};
}