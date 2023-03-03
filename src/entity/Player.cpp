#include "entity/Player.hpp"

#include "utils/common.hpp"
#include "utils/settings.hpp"

#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <algorithm>
#include <loguru.hpp>

namespace wolfen {
	Player::Player(Map& map) : m_map { map } {
		m_direction = { -1.0, 0.0 };
		m_plane = { 0.0, std::tan(deg2rad(CAMERA_FOV / 2.0F)) };
	}

	void Player::update(float dt, const sf::Vector2i& mouse_pos) {
		// Turn based on the mouse position on screen.
		auto turn_speed = CAMERA_FOV * (WINDOW_WIDTH / 2 - mouse_pos.x) / WINDOW_WIDTH;

		// Apply rotation to the camera direction and plane.
		if (turn_speed != 0.0) {
			m_direction = vecRotate(m_direction, turn_speed * dt);
			m_plane = vecRotate(m_plane, turn_speed * dt);
		}

		// Move forward and backward.
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			move(-1.0F, dt);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			move(1.0F, dt);
		}

		// Strafe to the left and right.
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			strafe(-1.0F, dt);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			strafe(1.0F, dt);
		}
	}

	void Player::move(float motion, float dt) {
		sf::Vector2f velocity { m_direction * PLAYER_SPEED * motion * dt };
		vecNormalize(velocity);

		if (!m_map.isColliding(m_position.x - velocity.x, m_position.y)) {
			m_position.x -= velocity.x;
		}
		if (!m_map.isColliding(m_position.x, m_position.y - velocity.y)) {
			m_position.y -= velocity.y;
		}
	}

	void Player::strafe(float side, float dt) {
		sf::Vector2f velocity { side * m_plane * PLAYER_SPEED * dt };
		vecNormalize(velocity);

		if (!m_map.isColliding(m_position.x + velocity.x, m_position.y)) {
			m_position.x += velocity.x;
		}
		if (!m_map.isColliding(m_position.x, m_position.y + velocity.y)) {
			m_position.y += velocity.y;
		}
	}
} // namespace wolfen
