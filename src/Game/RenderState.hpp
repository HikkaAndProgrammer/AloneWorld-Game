#pragma once
//engine
#include <Engine/StateMachine.hpp>

//game
#include <Game/TilemapCamera.hpp>

namespace game {
	class RenderState : public engine::BaseState {
	public:
		void update() final override;

		void on_create() final override;

	private:
		TilemapCamera camera;
	};
}
