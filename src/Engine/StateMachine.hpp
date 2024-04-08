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

//engine
#include <Engine/Util.hpp>

namespace engine {
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

		virtual void on_enable() {}
		virtual void on_disable() {}

		virtual void on_create() {}
		virtual void on_delete() {}

	private:
		bool is_active;
	};
	using IState = std::shared_ptr <BaseState>;

	class StateMachine {
	public:
		void init(size_t process_levels);
		void update();

		void add_state(std::string id, IState state);

		void request_status_change(std::string id, StateStatus status);

		void set_update_level(std::string state_id, size_t level);
		void clear_update_level(size_t level);

	protected:
		std::unordered_map <std::string, IState> m_states;
		std::vector <std::pair <std::vector <IState>, size_t>> m_process_levels;
		std::queue <std::pair <IState, StateStatus>> m_requested_updates;

		std::mutex m_mutex;
		std::condition_variable m_cv;
		std::atomic_size_t m_active_states = 0;
	};
}