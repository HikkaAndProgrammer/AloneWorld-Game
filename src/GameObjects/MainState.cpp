//game_objects
#include <GameObjects/MainState.hpp>

namespace game_objects {
	void MainState::update() {
		engine::core->input_manager->update();
		engine::core->event_system->update();
	}
}