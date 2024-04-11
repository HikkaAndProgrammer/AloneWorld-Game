#pragma once
//engine
#include "Engine/GameManager.hpp"

//game_objects
#include "Game/GameTilemap.hpp"
#include "GameObjects/SfmlEvent.hpp"

namespace game {
	class Core : public engine::GameManager {
		friend class engine::BaseState;
	public:
		size_t tile_size = 16; //in px

		std::shared_ptr <GameTilemap> tilemap;

		//TODO: remake tilemap io
		void init() override {
			engine::GameManager::init();
			this->tilemap.reset(new GameTilemap());
			this->tilemap->load("res/saves/Admin/main.sav");

			this->event_system->insert_event(std::make_shared <game_objects::SfmlEvent>());
		}

		void release() override {
			engine::GameManager::release();
			this->tilemap->save("res/saves/Admin/main.sav");
		}
	};

	extern std::shared_ptr <Core> core;
}