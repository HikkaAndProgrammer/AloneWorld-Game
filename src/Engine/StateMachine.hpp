#pragma once
//std
#include <atomic>
#include <memory>
#include <mutex>
#include <queue>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

//engine
#include "Engine/Util.hpp"

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
		virtual ~BaseState () = default;

		virtual void on_enable() {}
		virtual void on_disable() {}

		virtual void on_create() {}
		virtual void on_delete() {}

	private:
		bool is_active = false;
	};
	using IState = std::shared_ptr <BaseState>;

	class StateMachine {
	public:
		void init(size_t process_levels);
		void update();

		void add_state(std::string id, IState state);

		void request_status_change(const std::string& id, StateStatus status);

		void set_update_level(const std::string& state_id, size_t level);
		void clear_update_level(size_t level);

	protected:
		std::unordered_map <std::string, IState> m_states;
		std::vector <std::tuple <std::vector <IState>, size_t>> m_process_levels;
		std::queue <std::tuple <IState, StateStatus>> m_requested_updates;

		std::mutex m_mutex;
		std::condition_variable m_cv;
		std::atomic_size_t m_active_states = 0;
	};
}