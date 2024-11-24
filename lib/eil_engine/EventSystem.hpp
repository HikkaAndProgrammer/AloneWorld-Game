#pragma once
//std
#include <any>
#include <memory>
#include <string>
#include <unordered_map>

namespace eil::engine {
	using event_id_t = size_t;

	class BaseListener {
	public:
		virtual ~BaseListener() = default;

		virtual void call(const std::any& data) = 0;
	};
	using IListener = std::shared_ptr<BaseListener>;

	class BasePublisher {
	public:
		virtual ~BasePublisher() = default;

		virtual void post(const std::any& data) = 0;
	};
	using IPublisher = std::shared_ptr<BasePublisher>;

	//do listener and publisher functions at the same time
	//needed to make external event systems works
	class BaseEvent {
	public:
		virtual ~BaseEvent() = default;

		virtual void update() = 0;
	};
	using IEvent = std::shared_ptr<BaseEvent>;

	class EventManager {
		using key_type = std::string;
	public:
		void insert_listener(const key_type& id, const IListener& listener);
		void remove_listener(const key_type& id);
		void call(const key_type& id, const std::any& data = {}) const;

		void insert_event(const key_type& id, const IEvent& event);
		void remove_event(const key_type& id);
		void update() const;

	protected:
		std::unordered_multimap<key_type, IListener> m_listeners;
		std::unordered_map<key_type, IEvent> m_events;
	};
}
