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

	void Player::update(float dt, sf::RenderWindow& window) {
		// Turn based on the mouse position on screen.
		auto mouse_pos { sf::Mouse::getPosition(window) };
		auto turn_speed { CAMERA_FOV * (WINDOW_WIDTH / 2 - mouse_pos.x) / WINDOW_WIDTH };

		sf::Mouse::setPosition({ WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 }, window);

		// Apply rotation to the camera direction and plane.
		if (turn_speed != 0.0) {
			m_direction = vecRotate(m_direction, turn_speed * dt);
			m_plane = vecRotate(m_plane, turn_speed * dt);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			move(1.0F, dt);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			move(-1.0F, dt);
		}
	}

	void Player::move(float motion, float dt) {
		sf::Vector2f next_pos { m_position + m_direction * motion * PLAYER_SPEED * dt };

		if (!m_map.isColliding(next_pos.x, m_position.y)) {
			m_position.x = next_pos.x;
		}
		if (!m_map.isColliding(m_position.x, next_pos.y)) {
			m_position.y = next_pos.y;
		}
	}
} // namespace wolfen
