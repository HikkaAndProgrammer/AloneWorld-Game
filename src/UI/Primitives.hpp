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

namespace ui {
	//TODO: make every event to be triggered with std::function and chaiscript
	class BasicUiUnit : public util::Renderable {
	public:
		virtual ~BasicUiUnit() = default;
	};
	using IUiUnit = std::shared_ptr <BasicUiUnit>;
	using ui_page_t = std::list <IUiUnit>;

	class IClickable {
	public:
		virtual ~IClickable() = default;

		virtual bool is_clicked(sf::Vector2i point) = 0;
		virtual void on_click() {}
	};

	//TODO: layers of rendering of ui_pages
	class UiManager {
	public:
		void add_constructor(const std::string& key, const std::function <IUiUnit(toml::value&)>& value) {
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

		const ui_page_t& at(const std::string& key) const { return this->m_elements.at(key); }

	protected:
		std::unordered_map <std::string, ui_page_t> m_elements;
		std::unordered_map <std::string, std::function <IUiUnit(toml::value&)>> m_constructors;
	};
}

namespace util {
	sf::Color to_color(const toml::value& value);
}