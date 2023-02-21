#include "entity/Player.hpp"

#include "utils/common.hpp"
#include "utils/settings.hpp"

#include <cmath>

namespace wolfen {
	void Player::checkInput(const Uint8 *keyboard) {
		// Apply movement rotation.
		if (keyboard[SDL_SCANCODE_Q]) {
			m_rotation -= settings::PLAYER_ROTATION_SPEED;
		}
		if (keyboard[SDL_SCANCODE_E]) {
			m_rotation += settings::PLAYER_ROTATION_SPEED;
		}

		// Calculate horizontal movement direction.
		if (keyboard[SDL_SCANCODE_A]) {
			m_motion.x -= std::cos(deg2rad(m_rotation - 90.0));
			m_motion.y -= std::sin(deg2rad(m_rotation - 90.0));
		}
		if (keyboard[SDL_SCANCODE_D]) {
			m_motion.x += std::cos(deg2rad(m_rotation - 90.0));
			m_motion.y += std::sin(deg2rad(m_rotation - 90.0));
		}

		// Calculate vertical movement direction.
		if (keyboard[SDL_SCANCODE_W]) {
			m_motion.x -= std::cos(deg2rad(m_rotation));
			m_motion.y -= std::sin(deg2rad(m_rotation));
		}
		if (keyboard[SDL_SCANCODE_S]) {
			m_motion.x += std::cos(deg2rad(m_rotation));
			m_motion.y += std::sin(deg2rad(m_rotation));
		}
	}

	void Player::update(const Context& ctx) {
		checkInput(ctx.keyboard);

		m_velocity = m_motion.normalize() * m_maxspeed * ctx.dt;
		m_motion = Vec2 { 0.0, 0.0 };

		m_position += m_velocity;
	}

	void Player::draw(const Context& ctx) {
		// Draw player rect.
		ctx.display.setColor(0, 255, 0).fillRect(m_position - m_size / 2, m_size);

		// TEST: Draw player direction.
		const wolfen::Vec2 point { m_position.x - std::cos(deg2rad(m_rotation)) * 48.0F,
								   m_position.y - std::sin(deg2rad(m_rotation)) * 48.0F };
		ctx.display.setColor(255, 0, 0).drawLine(m_position, point);
	}
} // namespace wolfen
