#pragma once
//std
#include <atomic>
#include <memory>

//sf
#include <SFML/Graphics/RenderWindow.hpp>

//taur
#include <Taur/InputManager.hpp>
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
		void init(bool is_alloc_thread_pool, bool is_start_script_engine);
		void release();

		std::atomic_bool flag;
		const size_t tile_size = 16;
		
		sf::RenderWindow window;
		sf::Clock clock;

		std::shared_ptr <InputManager> input_manager;
		std::shared_ptr <RenderModule> render_module;
		std::shared_ptr <TextureManager> texture_manager;
		std::shared_ptr <ThreadPool> thread_pool;
		std::shared_ptr <StateMachine> state_machine;

		std::unique_ptr <chai::ChaiScript> script_engine;

		Tilemap tilemap;
	};

	extern core_t core;
}