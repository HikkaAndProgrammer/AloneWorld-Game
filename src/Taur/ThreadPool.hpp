#pragma once
//std
#include <vector>
#include <thread>
#include <atomic>
#include <memory>
#include <exception>
#include <future>
#include <mutex>
#include <functional>

//boost
#include <boost/lockfree/queue.hpp>

namespace taur {
	using Task = std::function <void(size_t id)>;

	class ThreadPool {
	public:
		ThreadPool() { init(); }
		ThreadPool(size_t threads_count, size_t queue_size); 
		~ThreadPool() { stop(true); }

		size_t size() const { return m_threads.size(); }
		size_t idle_count() const { return m_idle_count; }
		std::thread& operator[](size_t id) { return *m_threads[id]; }

		void resize(size_t threads_count);

		void clear_queue();
		Task pop();

		void stop(bool is_wait = false);

		template <class _Func, class ..._Args>
		auto push(_Func&& func, _Args&&... args) -> std::future <decltype(func(0, args...))> {
			auto pck = std::make_shared <std::packaged_task <decltype(func(0, args...))(size_t)>>(
				std::bind(std::forward <_Func>(func), std::placeholders::_1, std::forward <_Args>(args)...));
			
			m_queue.push(new Task([pck](size_t id) {
				(*pck)(id);
			}));

			std::unique_lock lock(m_mutex);
			m_cv.notify_one();

			return pck->get_future();
		}
		template <class _Func>
		auto push(_Func&& func) -> std::future <decltype(func(0))> {
			auto pck = std::make_shared <std::packaged_task <decltype(func(0))(size_t)>>(std::forward <_Func>(func));

			m_queue.push(new Task([pck](size_t id) {
				(*pck)(id);
			}));

			std::unique_lock lock(m_mutex);
			m_cv.notify_one();

			return pck->get_future();
		}

	protected:
		void set_thread(size_t id);

		void init() {
			m_idle_count = 0;
			m_is_stop = false;
			m_is_done = false;
		}

		std::vector <std::unique_ptr <std::thread>> m_threads;
		std::vector <std::shared_ptr <std::atomic_bool>> m_flags;
		mutable boost::lockfree::queue <Task*> m_queue;
		std::atomic_bool m_is_done, m_is_stop;
		std::atomic_size_t m_idle_count;

		std::mutex m_mutex;
		std::condition_variable m_cv;

	private:
		ThreadPool(const ThreadPool&) = delete;
		ThreadPool(ThreadPool&&) = delete;
		ThreadPool& operator=(const ThreadPool&) = delete;
		ThreadPool& operator=(ThreadPool&&) = delete;
	};
}