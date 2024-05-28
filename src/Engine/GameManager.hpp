#pragma once
#pragma warning

//std
#include <atomic>
#include <memory>
#include <unordered_map>

//sf
#include <SFML/Graphics/RenderWindow.hpp>

//util
#include "Engine/Util.hpp"

//engine
#include "Engine/Camera.hpp"
#include "Engine/EventSystem.hpp"
#include "Engine/InputManager.hpp"
#include "Engine/RenderModule.hpp"
#include "Engine/StateMachine.hpp"
#include "Engine/TextureModule.hpp"
#include "Engine/ThreadPool.hpp"

//chaiscript
#ifdef INCLUDE_SCRIPT_ENGINE
#include <chaiscript/chaiscript.hpp>
namespace chai = chaiscript;
#endif

//toml
#include <toml.hpp>

namespace engine {
	//Singleton and you can call load and save functions only once after init
	class GameManager : public util::Updatable {
	public:
		virtual ~GameManager() = default;

		virtual void init();
		virtual void release();

		void load_systems();
		void load_window();
		void load_thread_pool();
		void load_script_engine();

		void save_systems();

		std::atomic_bool flag;
		std::unordered_map <std::string, std::string> shared_data;
		
		std::shared_ptr <sf::RenderWindow> window;
		sf::Vector2u window_size;
		std::shared_ptr <sf::Font> font;

		//game systems
		std::shared_ptr <ThreadPool> thread_pool;
		std::shared_ptr <StateMachine> state_machine;

		//logic systems
		std::shared_ptr <InputManager> input_manager;
		std::shared_ptr <InputEvent> input_event;
		std::shared_ptr <EventControlBlock> event_system;

		//graphics systems
		std::shared_ptr <RenderModule> render_module;
		std::shared_ptr <TextureManager> texture_manager;
		std::shared_ptr <Camera> camera;

#ifdef INCLUDE_CHAI_SCRIPT
		std::unique_ptr <chai::ChaiScript> script_engine;
#endif
	protected:
		toml::value m_settings;
	};

	extern std::shared_ptr <GameManager> game_manager;
}