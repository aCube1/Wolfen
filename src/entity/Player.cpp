#include "entity/Player.hpp"

#include <SDL_render.h>

namespace wolfen {
	void Player::input(const Uint8 *keyboard) {
		if (keyboard[SDL_SCANCODE_A]) {
			m_motion.x -= 1.0;
		}
		if (keyboard[SDL_SCANCODE_D]) {
			m_motion.x += 1.0;
		}

		if (keyboard[SDL_SCANCODE_W]) {
			m_motion.y -= 1.0;
		}
		if (keyboard[SDL_SCANCODE_S]) {
			m_motion.y += 1.0;
		}
	}

	void Player::update(double dt) {
		m_velocity = m_motion.normalize() * m_maxspeed * dt;
		m_motion = Vec2 { 0.0, 0.0 };

		m_position += m_velocity;
	}

	void Player::draw(Display& display) {
		display.setColor(0, 255, 0).fillRect(m_position, m_size);
	}
} // namespace wolfen
