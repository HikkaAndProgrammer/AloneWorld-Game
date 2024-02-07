#include <Taur/GameManager.hpp>

//toml
#include <toml.hpp>

namespace taur {
	//TODO: make dedicated function for loading files
	void GameManager::init(/*bool is_alloc_thread_pool, bool is_start_script_engine*/) {
		bool is_alloc_thread_pool = false;
		bool is_start_script_engine = false;

		this->flag = true;
		this->clock.restart();

		auto settings = toml::parse("res/settings.toml");
		auto engine_data = toml::find <toml::table>(settings, "engine_data");
		auto shared_table = toml::find <toml::table>(settings, "shared_data");

		//loading shared data
		for (auto& [key, val] : shared_table)
			this->shared_data.emplace(key, val.as_string());

		//loading main systems
		auto input_config_path = engine_data["input_config_path"].as_string();
		this->input_manager.reset(new InputManager());
		//this->input_manager->add_input_handler("left_click", InputType::Mouse, (size_t)sf::Mouse::Left);
		this->input_manager->load_config(input_config_path);

		auto textures_path = engine_data["textures_path"].as_string();
		this->texture_manager.reset(new TextureManager());
		this->texture_manager->load(textures_path);

		this->render_module.reset(new RenderModule());
		this->render_module->init();

		this->thread_pool.reset(new ThreadPool(20));
		if (is_alloc_thread_pool)
			this->thread_pool->init(2);

		this->state_machine.reset(new StateMachine());
		this->state_machine->init(1);

#ifdef INCLUDE_SCRIPT_ENGINE
		if (is_start_script_engine)
			this->script_engine.reset(new chai::ChaiScript());
#endif
	}
	//TODO: make dedicated function for saving files
	void GameManager::release() {
		if (this->window.isOpen())
			this->window.close();

		this->thread_pool->stop(true);

#ifdef INCLUDE_SCRIPT_ENGINE
		this->script_engine.reset();
#endif

		auto settings = toml::parse("res/settings.toml");
		auto engine_data = toml::find <toml::table>(settings, "engine_data");

		//TODO: saving shared data

		//saving main systems
		auto input_config_info = engine_data["input_config_path"].as_string();
		this->input_manager->save_config(input_config_info);
	}
}