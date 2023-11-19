#pragma once
//std
#include <memory>

//sf
#include <SFML/Graphics/RenderWindow.hpp>

//taur
#include <Taur/RenderModule.hpp>
#include <Taur/TextureModule.hpp>

//chaiscript
#include <chaiscript/chaiscript.hpp>

namespace script = chaiscript;

namespace taur {
	struct core_t {
		void init();
		void release();

		sf::RenderWindow window;
		Renderer renderer;
		TextureManager textures;
		std::unique_ptr <script::ChaiScript> engine;
	};

	extern core_t core;
}