#pragma once
//engine
#include "Engine/GameManager.hpp"

//game_objects
#include "Game/GameTilemap.hpp"
#include "GameObjects/SfmlEvent.hpp"

//engine::ui
#include "UI/Primitives.hpp"

namespace game {
	class Core : public engine::GameManager {
		friend class engine::BaseState;
	public:
		size_t tile_size = 16; //in px

		std::shared_ptr <engine::ui::UiManager> ui_manager;
		std::shared_ptr <GameTilemap> tilemap;

		//TODO: remake tilemap io
		void init() override {
			engine::GameManager::init();
			this->tilemap.reset(new GameTilemap());
			this->tilemap->load("res/saves/Admin/main.sav");

			this->event_system->insert_event(std::make_shared <game_objects::SfmlEvent>());

			this->load_ui();
		}

		void release() override {
			engine::GameManager::release();
			this->tilemap->save("res/saves/Admin/main.sav");
		}

		void load_ui() {
			this->ui_manager.reset(new engine::ui::UiManager());
			this->ui_manager->add_constructor("rect_button", [](toml::value value) {
				auto result = std::make_shared <engine::ui::RectangleUiUnit>();
				auto& rect = value["rect"].as_array();
				auto rect_size = sf::Vector2f(rect[2].as_integer(), rect[3].as_integer());

				result->box().setPosition(rect[0].as_integer(), rect[1].as_integer());
				result->box().setSize(rect_size);
				if (value.contains("text"))
					result->set_text(value["text"]["content"].as_string(), value["text"]["size"].as_integer());
				return result;
			});
			this->ui_manager->load(this->m_settings["engine_data"]["ui_path"].as_string());
		}
	};

	extern std::shared_ptr <Core> core;
}