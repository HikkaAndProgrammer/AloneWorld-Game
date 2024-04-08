#include <Engine/GameManager.hpp>

namespace engine {
	void GameManager::init() {
		this->flag = true;

		this->m_settings = toml::parse("res/settings.toml");

		auto shared_table = this->m_settings["shared_data"].as_table();
		for (auto& [key, val] : shared_table)
			this->shared_data.emplace(key, val.as_string());

		this->load_systems();
		this->load_window();
		this->load_thread_pool();
		this->load_script_engine();
	}
	void GameManager::release() {
		if (this->window.isOpen())
			this->window.close();

		this->thread_pool->stop(true);

#ifdef INCLUDE_SCRIPT_ENGINE
		this->script_engine.reset();
#endif

		this->save_systems();
	}

	void GameManager::load_systems() {
		auto input_config_path = this->m_settings["engine_data"]["input_config_path"].as_string();
		this->input_manager.reset(new InputManager());
		this->input_manager->load_config(input_config_path);
		this->input_event.reset(new InputEvent(*this->input_manager));

		auto textures_path = this->m_settings["engine_data"]["textures_path"].as_string();
		this->texture_manager.reset(new TextureManager());
		this->texture_manager->load(textures_path);

		size_t process_levels = this->m_settings["engine_data"]["state_machine"]["process_levels"].as_integer();
		this->state_machine.reset(new StateMachine());
		this->state_machine->init(process_levels);

		this->render_module.reset(new RenderModule());
		this->render_module->init();

		this->event_system.reset(new EventControlBlock());
		this->event_system->insert_event(this->input_event);
	}
	void GameManager::load_window() {
		auto window_data = this->m_settings["engine_data"]["window"];

		std::string title = window_data["title"].as_string();
		size_t width = window_data["width"].as_integer(),
			height = window_data["height"].as_integer(),
			framerate = window_data["framerate"].as_integer();

		core->window.create(sf::VideoMode(width, height), title);
		core->window.setFramerateLimit(framerate);
	}
	void GameManager::load_thread_pool() {
		auto thread_pool_data = this->m_settings["engine_data"]["thread_pool"];
		size_t threads_count = thread_pool_data["threads_count"].as_integer(),
			queue_size = thread_pool_data["queue_size"].as_integer();
		this->thread_pool.reset(new ThreadPool(queue_size));
		if (threads_count)
			this->thread_pool->init(threads_count);
	}
	void GameManager::load_script_engine() {
#ifdef INCLUDE_SCRIPT_ENGINE
		auto script_engine_data = this->m_settings["engine_data"]["script_engine"];
		bool is_start_script_engine = script_engine_data["is_start_script_engine"].as_boolean();
		if (is_start_script_engine)
			this->script_engine.reset(new chai::ChaiScript());
#endif
	}

	void GameManager::save_systems() {
		auto input_config_info = this->m_settings["engine_data"]["input_config_path"].as_string();
		this->input_manager->save_config(input_config_info);
	}
}