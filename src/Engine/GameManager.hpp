#pragma once
#pragma warning

//std
#include <atomic>
#include <memory>
#include <unordered_map>

//sf
#include <SFML/Graphics/RenderWindow.hpp>

//engine
#include <Engine/InputManager.hpp>
#include <Engine/RenderModule.hpp>
#include <Engine/StateMachine.hpp>
#include <Engine/TextureModule.hpp>
#include <Engine/ThreadPool.hpp>
#include <Engine/EventSystem.hpp>

//chaiscript
#ifdef INCLUDE_SCRIPT_ENGINE
#include <chaiscript/chaiscript.hpp>
namespace chai = chaiscript;
#endif

namespace engine {
	//Singleton
	class GameManager {
	public:
		virtual void init();
		virtual void release();

		std::atomic_bool flag;
		std::unordered_map <std::string, std::string> shared_data;
		
		sf::RenderWindow window;
		sf::Clock clock;

		//core systems
		std::shared_ptr <ThreadPool> thread_pool;
		std::shared_ptr <StateMachine> state_machine;

		//logic systems
		std::shared_ptr <InputManager> input_manager;
		std::shared_ptr <EventControlBlock> event_system;

		//graphics systems
		std::shared_ptr <RenderModule> render_module;
		std::shared_ptr <TextureManager> texture_manager;

#ifdef INCLUDE_CHAI_SCRIPT
		std::unique_ptr <chai::ChaiScript> script_engine;
#endif
	};

	extern std::shared_ptr <GameManager> core;
}