#include "ThreadPool.hpp"

namespace taur {
	ThreadPool::ThreadPool(size_t threads_count, size_t queue_size) : m_queue(queue_size) {
		init();
		resize(threads_count);
	}

	void ThreadPool::resize(size_t size) {
		if (!this->m_is_stop && !this->m_is_done) {
			size_t _size = this->m_threads.size();
			if (_size <= size) {
				this->m_threads.resize(size);
				this->m_flags.resize(size);

				for (size_t i = _size; i != size; i++) {
					this->m_flags[i] = std::make_shared <std::atomic_bool>(false);
					set_thread(i);
				}
			} else {
				for (size_t i = size; i != _size; i++) {
					this->m_flags[i]->store(true);
					this->m_threads[i]->detach();
				}
				{
					std::unique_lock lock(this->m_mutex);
					this->m_cv.notify_all();
				}
				this->m_threads.resize(size);
				this->m_flags.resize(size);
			}
		}
	}

	void ThreadPool::clear_queue() {
		Task* task;
		while (this->m_queue.pop(task))
			delete task;
	}

	Task ThreadPool::pop() {
		Task* task = nullptr;
		this->m_queue.pop(task);
		std::unique_ptr <Task> func(task);

		Task wraped_task;
		if (task)
			wraped_task = *task;
		return wraped_task;
	}

	void ThreadPool::stop(bool is_wait) {
		if (!is_wait) {
			if (!this->m_is_stop)
				return;

			this->m_is_stop = true;
			for (size_t i = 0, size = this->m_threads.size(); i != size; i++)
				m_flags[i]->store(true);
			clear_queue();
		} else {
			if (this->m_is_stop || this->m_is_done)
				return;
			this->m_is_done = true;
		}
		{
			std::unique_lock lock(this->m_mutex);
			this->m_cv.notify_all();
		}
		
		for (size_t i = 0; i != this->m_threads.size(); i++)
			if (this->m_threads[i]->joinable())
				this->m_threads[i]->join();

		clear_queue();
		this->m_threads.clear();
		this->m_flags.clear();
	}

	void ThreadPool::set_thread(size_t id) {
		auto flag = m_flags[id];
		auto thread_loop = [this, id, flag]() {
			std::atomic_bool& _flag = *flag;
			Task* task;
			bool is_pop = this->m_queue.pop(task);

			while (true) {
				while (is_pop) {
					std::unique_ptr <Task> func(task);
					(*task)(id);

					if (_flag)
						return;;
					is_pop = this->m_queue.pop(task);
				}

				std::unique_lock lock(this->m_mutex);
				this->m_idle_count++;
				this->m_cv.wait(lock, [this, &task, &is_pop, &_flag]() {
					is_pop = this->m_queue.pop(task);
					return is_pop || this->m_is_done || _flag;
				});
				this->m_idle_count--;

				if (!is_pop)
					return;;
			}
		};
		this->m_threads[id].reset(new std::thread(thread_loop));
	}
}