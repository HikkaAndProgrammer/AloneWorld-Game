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
			for (auto it : *this->m_page) {
				if (it->type() == ui::UiUnitType::Clickable) {
					auto cursor_position = game::core->input_manager->get_cursor()->get_position();
					auto clickable = std::dynamic_pointer_cast <ui::IClickable>(it);
					if (clickable->is_clicked(cursor_position))
						clickable->on_click();
				}
			}

			//than render
			for (auto it : *this->m_page)
				it->render();
		}

	protected:
		const ui::ui_page_t* m_page = nullptr;
	};
}
