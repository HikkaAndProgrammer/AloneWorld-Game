#pragma once
//taur
#include <Taur/Camera.hpp>
#include <Taur/Core.hpp>
#include <Taur/StateMachine.hpp>
#include <Taur/Tilemap.hpp>

namespace game {
	class RenderState : public taur::BaseState {
	public:
		void update(float dt) final override;

		void onCreate() final override;

	private:
		taur::Camera camera;
	};
}
