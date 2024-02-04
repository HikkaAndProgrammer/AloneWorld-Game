#pragma once
//taur
#include <Taur/StateMachine.hpp>

//game_objects
#include <GameObjects/Camera.hpp>

namespace game {
	class RenderState : public taur::BaseState {
	public:
		void update() final override;

		void onCreate() final override;

	private:
		game_objects::ICamera camera;
	};
}
