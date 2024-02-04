#include <Taur/GameManager.hpp>

//toml
#include <toml.hpp>

namespace taur {
	void GameManager::init(bool is_alloc_thread_pool, bool is_start_script_engine) {
		this->flag = true;
		this->clock.restart();

		auto settings = toml::parse("./res/settings.toml");
		auto texture_info = toml::find <std::string>(settings, "textures_path");
		auto table = toml::find <toml::table>(settings, "shared_data");
		for (auto& [key, val] : table)
			this->shared_data.emplace(key, val.as_string());

		this->input_manager.reset(new InputManager());
		this->input_manager->add_input_handler("left_click", InputType::Mouse, (size_t)sf::Mouse::Left);

		this->texture_manager.reset(new TextureManager());
		this->texture_manager->load(texture_info);

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
	void GameManager::release() {
		if (this->window.isOpen())
			this->window.close();

		this->thread_pool->stop(true);

#ifdef INCLUDE_SCRIPT_ENGINE
		this->script_engine.reset();
#endif
	}
}