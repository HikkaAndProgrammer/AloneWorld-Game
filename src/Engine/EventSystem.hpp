#pragma once
//std
#include <any>
#include <list>
#include <memory>
#include <string>
#include <unordered_map>

namespace engine {
	using event_id_t = size_t;

	class BaseListener {
	public:
		virtual ~BaseListener() = default;

		virtual void call(std::any data) = 0;
	};
	using IListener = std::shared_ptr <BaseListener>;

	class BasePublisher {
	public:
		virtual ~BasePublisher() = default;

		virtual void post() = 0;
	};
	using IPublisher = std::shared_ptr <BasePublisher>;

	//do listener and publisher functions at the same time
	//needed to make external event systems works
	class BaseEvent {
	public:
		virtual ~BaseEvent() = default;

		virtual void update() = 0;
	};
	using IEvent = std::shared_ptr <BaseEvent>;

	class EventControlBlock {
	public:
		void insert_listener(event_id_t id, const IListener& listener);
		void insert_listener(const std::string& event_name, const IListener& listener);
		void remove_listener(event_id_t id);
		void remove_listener(const std::string& event_name, const IListener& listener);

		void insert_event(const IEvent& event);
		void remove_event(const IEvent& event);

		//TODO: custom inserting ids for event's names
		event_id_t get_event_id(const std::string& event_name);

		void update();

		void call(event_id_t id, const std::any& data);
		void call(const std::string& event_name, const std::any& data);

	protected:
		std::unordered_multimap <event_id_t, IListener> m_listeners;
		std::list <IEvent> m_events;
		std::unordered_map <std::string, event_id_t> m_id_table;

	private:
		std::hash <std::string> m_hasher;
	};
}