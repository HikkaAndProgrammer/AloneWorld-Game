#include <Taur/StateMachine.hpp>

//taur
#include <Taur/Core.hpp>

namespace taur {
	void StateMachine::update() {
		core.clock.restart();

		for (const auto& [state, new_status] : this->m_pending)
			state->m_new_status = new_status;


		float delta = core.clock.getElapsedTime().asSeconds();
		for (auto& level : m_process_levels) {
			for (auto& [state, flag] : level) {
				if (state->m_current_status != state->m_new_status) {
					using enum StateStatus;
					switch (state->m_new_status) {
					case Idle:
						state->onDisable();
						break;
					case Active:
						state->onEnable();
						break;
					case OnCreate:
						state->onCreate();
						break;
					case OnDelete:
						state->onDetele();
						break;
					}
				}

				core.thread_pool->push([delta, state, &flag](size_t id) {
					flag = false;
					state->update(delta);
				});
			}

			std::unique_lock lock(this->m_mutex);
			m_cv.wait(lock, [level]() {
				bool flag = true;
				for (const auto& [_, state_flag] : level)
					flag *= state_flag;
				return flag;
			});
		}
	}
}