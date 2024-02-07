#pragma once
//taur
#include <Taur/StateMachine.hpp>

//game
#include <Game/TilemapCamera.hpp>

namespace game {
	class RenderState : public taur::BaseState {
	public:
		void update() final override;

		void onCreate() final override;

	private:
		TilemapCamera camera;
	};
}
