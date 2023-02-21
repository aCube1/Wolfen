#include "entity/Player.hpp"

#include "utils/common.hpp"
#include "utils/settings.hpp"

#include <SDL_render.h>
#include <cmath>

static wolfen::Vec2 point { 0.0, 0.0 };

namespace wolfen {
	void Player::input(const Uint8 *keyboard) {
		// Apply movement rotation.
		if (keyboard[SDL_SCANCODE_A]) {
			m_rotation -= settings::PLAYER_ROTATION_SPEED;
		}
		if (keyboard[SDL_SCANCODE_D]) {
			m_rotation += settings::PLAYER_ROTATION_SPEED;
		}

		// Calculate movement direction.
		if (keyboard[SDL_SCANCODE_W]) {
			m_motion.x += std::cos(deg2rad(m_rotation));
			m_motion.y += std::sin(deg2rad(m_rotation));
		}
		if (keyboard[SDL_SCANCODE_S]) {
			m_motion.x += std::cos(deg2rad(m_rotation));
			m_motion.y += std::sin(deg2rad(m_rotation));
		}
	}

	void Player::update(double dt) {
		m_velocity = m_motion.normalize() * m_maxspeed * dt;
		m_motion = Vec2 { 0.0, 0.0 };

		m_position += m_velocity;

		// TEST: Test the player rotation.
		point.x = m_position.x + std::cos(deg2rad(m_rotation)) * 64.0;
		point.y = m_position.y + std::sin(deg2rad(m_rotation)) * 64.0;
	}

	void Player::draw(Display& display) {
		// Draw player rect.
		display.setColor(0, 255, 0).fillRect(m_position - m_size / 2, m_size);

		display.setColor(255, 0, 0).drawLine(m_position, point);
	}
} // namespace wolfen
