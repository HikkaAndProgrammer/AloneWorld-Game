#pragma once
//engine
#include <Engine/StateMachine.hpp>
#include <Engine/GameManager.hpp>

namespace game_objects {
	class MainState : public engine::BaseState {
	public:
		void update() override;
	};
}