#pragma once
//taur
#include <Taur/GameManager.hpp>

//game_objects
#include <GameObjects/Tilemap.hpp>

//game
#include <Game/Tile.hpp>

namespace game {
	using Tilemap = game_objects::ITilemap <tile_t>;

	class Engine : public taur::GameManager {
		friend class taur::BaseState;
	public:
		size_t tile_size = 16; //in px

		Tilemap tilemap;

		//TODO: remake tilemap io
		void init() override {
			taur::GameManager::init();
			this->tilemap.reset(new game_objects::BaseTilemap <tile_t>());
			this->tilemap->load("res/saves/Admin/main.sav");
		}

		void release() override {
			taur::GameManager::release();
			this->tilemap->save("res/saves/Admin/main.sav");
		}
	};

	extern std::shared_ptr <Engine> engine;
}