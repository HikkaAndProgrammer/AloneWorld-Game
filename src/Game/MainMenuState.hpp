#pragma once
//engine
#include <Engine/StateMachine.hpp>

//game
#include <Game/Core.hpp>

//ui
#include <UI/Primitives.hpp>

namespace game {
	class MainMenuState : public engine::BaseState {
	public:
		void on_create() override {
			this->m_page = &game::core->ui_manager->at("main_menu");
		}

		void update() override {
			//firstly update
			auto cursor_position = game::core->input_manager->get_cursor()->get_position();
			for (auto it : *this->m_page) {
				if (it->is_clicked(cursor_position))
					it->on_click();
			}

			//than render
			for (auto it : *this->m_page)
				it->render();
		}

	protected:
		const ui::ui_page_t* m_page = nullptr;
	};
}
