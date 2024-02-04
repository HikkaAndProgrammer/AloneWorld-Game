#pragma once
//taur
#include <Taur/GameManager.hpp>

//game_objects
#include <GameObjects/Tilemap.hpp>

//game
#include <Game/Tile.hpp>

namespace game {
	using Tilemap = game_objects::BaseTilemap <tile_t>;

	class Engine : public taur::GameManager {
	public:
		//in px
		size_t tile_size = 16;
	};

	extern std::shared_ptr <Engine> engine;
}