#pragma once
//std
#include <atomic>
#include <memory>

//sf
#include <SFML/Graphics/RenderWindow.hpp>

//taur
#include <Taur/RenderModule.hpp>
#include <Taur/StateMachine.hpp>
#include <Taur/TextureModule.hpp>
#include <Taur/ThreadPool.hpp>
#include <Taur/Tilemap.hpp>

//chaiscript
#include <chaiscript/chaiscript.hpp>

namespace chai = chaiscript;

namespace taur {
	struct core_t {
		void init(bool is_alloc_thread_pool);
		void release();

		std::atomic_bool flag;
		const size_t tile_size = 16;
		
		sf::RenderWindow window;
		sf::Clock clock;

		std::shared_ptr <Renderer> renderer;
		std::shared_ptr <TextureManager> textures;
		std::shared_ptr <ThreadPool> thread_pool;
		std::shared_ptr <StateMachine> state_machine;

		std::unique_ptr <chai::ChaiScript> engine;

		Tilemap tilemap;
	};

	extern core_t core;
}