#pragma once
#pragma warning

//std
#include <atomic>
#include <memory>
#include <unordered_map>

//sf
#include <SFML/Graphics/RenderWindow.hpp>

//taur
#include <Taur/InputManager.hpp>
#include <Taur/RenderModule.hpp>
#include <Taur/StateMachine.hpp>
#include <Taur/TextureModule.hpp>
#include <Taur/ThreadPool.hpp>

//chaiscript
#ifdef INCLUDE_SCRIPT_ENGINE
#include <chaiscript/chaiscript.hpp>
namespace chai = chaiscript;
#endif

namespace taur {
	//Singleton
	class GameManager {
	public:
		virtual void init(/*bool is_alloc_thread_pool, bool is_start_script_engine*/);
		virtual void release();

		std::atomic_bool flag;
		std::unordered_map <std::string, std::string> shared_data;
		
		sf::RenderWindow window;
		sf::Clock clock;

		std::shared_ptr <InputManager> input_manager;
		std::shared_ptr <RenderModule> render_module;
		std::shared_ptr <TextureManager> texture_manager;
		std::shared_ptr <ThreadPool> thread_pool;
		std::shared_ptr <StateMachine> state_machine;

#ifdef INCLUDE_CHAI_SCRIPT
		std::unique_ptr <chai::ChaiScript> script_engine;
#endif
	};

	extern std::shared_ptr <GameManager> core;
}