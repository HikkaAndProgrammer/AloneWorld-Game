#pragma once
//std
#include <unordered_map>
#include <list>

namespace taur {
	enum class StateUpdateStatus {
		Idle = 0,
		Active = 1,
		OnEnable,
		OnDisable,
		OnCreate,
		OnDelete,
		Count = 6
	};

	class BaseState {
	public:
		virtual ~BaseState () {}

		virtual void update() = 0;

		virtual void onEnable() {}
		virtual void onDisable() {}

		virtual void onCreate() {}
		virtual void onDetele() {}
	};

	class StateMachine {
	public:


	protected:

	};
}