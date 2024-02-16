#pragma once
//game_objects
#include <GameObjects/MainState.hpp>

namespace game {
	class GameState : public game_objects::MainState {
	public:
		void update() override {
			game_objects::MainState::update();
		}
	};
}