#include "ThreadPool.hpp"

namespace taur {
	ThreadPool::ThreadPool(size_t threads_count, size_t queue_size) : m_queue(queue_size) {
		init();
		resize(threads_count);
	}

	void ThreadPool::resize(size_t size) {
		if (!m_is_stop && !m_is_done) {
			size_t _size = m_threads.size();
			if (_size <= size) {
				m_threads.resize(size);
				m_flags.resize(size);

				for (size_t i = _size; i != size; i++) {
					m_flags[i] = std::make_shared <std::atomic_bool>(false);
					set_thread(i);
				}
			} else {
				for (size_t i = size; i != _size; i++) {
					m_flags[i]->store(true);
					m_threads[i]->detach();
				}
				{
					std::unique_lock lock(m_mutex);
					m_cv.notify_all();
				}
				m_threads.resize(size);
				m_flags.resize(size);
			}
		}
	}

	void ThreadPool::clear_queue() {
		Task* task;
		while (m_queue.pop(task))
			delete task;
	}

	Task ThreadPool::pop() {
		Task* task = nullptr;
		m_queue.pop(task);
		std::unique_ptr <Task> func(task);

		Task wraped_task;
		if (task)
			wraped_task = *task;
		return wraped_task;
	}

	void ThreadPool::stop(bool is_wait) {
		if (!is_wait) {
			if (!m_is_stop)
				return;

			m_is_stop = true;
			for (size_t i = 0, size = m_threads.size(); i != size; i++)
				m_flags[i]->store(true);
			clear_queue();
		} else {
			if (m_is_stop || m_is_done)
				return;
			m_is_done = true;
		}
		{
			std::unique_lock lock(m_mutex);
			m_cv.notify_all();
		}
		
		for (size_t i = 0; i != m_threads.size(); i++)
			if (m_threads[i]->joinable())
				m_threads[i]->join();

		clear_queue();
		m_threads.clear();
		m_flags.clear();
	}

	void ThreadPool::set_thread(size_t id) {
		auto flag = m_flags[id];
		auto thread_loop = [this, id, flag]() {
			std::atomic_bool& _flag = *flag;
			Task* task;
			bool is_pop = m_queue.pop(task);

			while (true) {
				while (is_pop) {
					std::unique_ptr <Task> func(task);
					(*task)(id);

					if (_flag)
						return;;
					is_pop = m_queue.pop(task);
				}

				std::unique_lock lock(m_mutex);
				m_idle_count++;
				m_cv.wait(lock, [this, &task, &is_pop, &_flag]() {
					is_pop = m_queue.pop(task);
					return is_pop || m_is_done || _flag;
				});
				m_idle_count--;

				if (!is_pop)
					return;;
			}
		};
		m_threads[id].reset(new std::thread(thread_loop));
	}
}