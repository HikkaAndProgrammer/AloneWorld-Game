#pragma once
//engine
#include <Engine/StateMachine.hpp>

//game
#include <Game/TilemapCamera.hpp>

namespace game {
	class RenderState : public engine::BaseState {
	public:
		void update() final override;

		void onCreate() final override;

	private:
		TilemapCamera camera;
	};
}
