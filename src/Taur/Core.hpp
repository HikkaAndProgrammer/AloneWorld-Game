#pragma once
//std
#include <memory>

//sf
#include <SFML/Graphics/RenderWindow.hpp>

//taur
#include <Taur/RenderModule.hpp>
#include <Taur/TextureModule.hpp>
#include <Taur/ThreadPool.hpp>

//chaiscript
#include <chaiscript/chaiscript.hpp>

namespace chai = chaiscript;

namespace taur {
	struct core_t {
		void init();
		void release();

		const size_t tile_size = 16;
		
		sf::RenderWindow window;
		sf::Clock clock;

		std::shared_ptr <Renderer> renderer;
		std::shared_ptr <TextureManager> textures;
		std::shared_ptr <ThreadPool> thread_pool;

		std::unique_ptr <chai::ChaiScript> engine;
	};

	extern core_t core;
}