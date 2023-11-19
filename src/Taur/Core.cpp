//taur
#include <Taur/Core.hpp>
//toml
#include <toml.hpp>

namespace taur {
	core_t core;

	void core_t::init() {
		auto settings = toml::parse("./res/settings.toml");

		auto texture_info = toml::find <std::string>(settings, "textures_path");
		textures.load(texture_info);

		renderer.init();

		engine = std::make_unique <script::ChaiScript>();
	}
	void core_t::release() {
		if (window.isOpen())
			window.close();
		engine = nullptr;
	}
}