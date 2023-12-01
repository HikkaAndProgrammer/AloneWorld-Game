#include <Taur/StateMachine.hpp>

//taur
#include <Taur/Core.hpp>

namespace taur {
	void StateMachine::update() {
		core.clock.restart();

		while(!this->m_requested_updates.empty()) {
			auto& [state, status] = this->m_requested_updates.front();
			
			using enum StateStatus;
			switch (status) {
			case OnCreate:
				state->onCreate();
				state->is_active = true;
				break;
			case OnDelete:
				state->onDetele();
				state->is_active = false;
				break;
			case OnEnable:
				state->onEnable();
				state->is_active = true;
				break;
			case OnDisable:
				state->onDisable();
				state->is_active = false;
				break;
			}

			this->m_requested_updates.pop();
		}

		float delta = core.clock.getElapsedTime().asSeconds();
		auto& active = this->m_active_states;
		auto& mutex = this->m_mutex;
		auto& cv = this->m_cv;

		for (auto& level : this->m_process_levels) {
			for (size_t i = 1; i < level.size(); i++) {
				auto& state = level[i];
				if (state->is_active) {
					core.thread_pool->push([delta, state, &active, &mutex, &cv](size_t id) {
						std::unique_lock lock(mutex);
						active++;
						state->update(delta);
						active--;
						cv.notify_one();
					});
				}
			}

			auto& state = level.front();
			if (state->is_active)
				state->update(delta);

			if (level.size() > 1) {
				std::unique_lock lock(mutex);
				this->m_cv.wait(lock, [&active]() { return active == 0; });
			}
		}
	}
}