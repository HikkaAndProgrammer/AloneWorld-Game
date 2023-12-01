#include <Taur/Core.hpp>

//toml
#include <toml.hpp>

namespace taur {
	core_t core;

	void core_t::init(bool is_alloc_thread_pool) {
		this->flag = true;
		this->clock.restart();

		auto settings = toml::parse("./res/settings.toml");
		auto texture_info = toml::find <std::string>(settings, "textures_path");

		this->textures.reset(new TextureManager());
		this->textures->load(texture_info);

		this->renderer.reset(new Renderer());
		this->renderer->init();

		this->thread_pool.reset(new ThreadPool(20));
		if (is_alloc_thread_pool)
			this->thread_pool->init(2);

		this->state_machine.reset(new StateMachine());
		this->state_machine->init(1);

		//this->engine.reset(new chai::ChaiScript());
	}
	void core_t::release() {
		if (this->window.isOpen())
			this->window.close();

		this->thread_pool->stop(true);

		this->engine.reset();
	}
}