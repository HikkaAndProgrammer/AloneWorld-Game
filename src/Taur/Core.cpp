//taur
#include <Taur/Core.hpp>
//toml
#include <toml.hpp>

namespace taur {
	core_t core;

	void core_t::init() {
		auto settings = toml::parse("./res/settings.toml");

		auto texture_info = toml::find <std::string>(settings, "textures_path");
		this->textures.load(texture_info);

		this->renderer.init();

		this->engine = std::make_unique <script::ChaiScript>();
	}
	void core_t::release() {
		if (this->window.isOpen())
			this->window.close();
		this->engine = nullptr;
	}
}