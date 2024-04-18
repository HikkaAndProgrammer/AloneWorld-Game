#pragma once
//std
#include <functional>
#include <list>
#include <vector>

//sf
#include <SFML/Graphics.hpp>

//toml
#include <toml.hpp>

//engine
#include "Engine/GameManager.hpp"
#include "Engine/Util.hpp"

namespace engine::ui {
	//TODO: make every event to be triggered with std::function and chaiscript
	class BasicUiUnit : public sf::Transformable, public util::Renderable {
	public:
		virtual bool is_clicked(sf::Vector2i point) = 0;
		virtual void on_click() {}
	};
	using IUiUnit = std::shared_ptr <BasicUiUnit>;

	class UiManager {
	public:
		void add_constructor(const std::string& key, const std::function <IUiUnit(toml::value)>& value) {
			this->m_constructors.emplace(key, value);
		}

		void load(const std::string& path) {
			auto value = toml::parse(path);
			auto pages = toml::find <std::vector <std::string>>(value, "pages");
			auto starting_page = value["starting_page"].as_string();

			for (auto& page_name : pages) {
				for (auto& it : value[page_name].as_array()) {
					auto val = this->m_constructors[it["type"].as_string()](it);
					this->m_elements[page_name].emplace_back(val);
				}
			}
		}

	protected:
		std::unordered_map <std::string, std::list <IUiUnit>> m_elements;
		std::unordered_map <std::string, std::function <IUiUnit(const toml::value&)>> m_constructors;
	};

	class RectangleUiUnit : public BasicUiUnit {
	public:
		bool is_clicked(sf::Vector2i point) override {
			return this->m_box.getLocalBounds().contains(point.x, point.y);
		}

		const sf::String& get_text() const {
			return this->m_text.getString();
		}
		void set_text(const std::string& text, uint16_t size) {
			this->m_text.setCharacterSize(size);
			this->m_text.setString(text);
			this->_set_text_to_center();
		}
		
		sf::RectangleShape& box() { return this->m_box; }
		const sf::RectangleShape& box() const { return this->m_box; }

		void render() const override {
			game_manager->window->draw(this->m_box);
			game_manager->window->draw(this->m_text);
		}

	protected:
		sf::RectangleShape m_box;
		sf::Text m_text;

	private:
		void _set_text_to_center() {
			auto box_position = this->m_box.getLocalBounds();
			auto text_position = this->m_text.getLocalBounds();
			this->m_text.setPosition(box_position.left + (box_position.width - text_position.width) / 2, 
				box_position.top + (box_position.height - text_position.height) / 2);
		}
	};
}