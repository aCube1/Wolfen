#include "entity/Player.hpp"

#include "utils/common.hpp"
#include "utils/settings.hpp"

#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <algorithm>

namespace wolfen {
	void Player::update(float dt, sf::RenderWindow& window) {
		(void)window;
		(void)m_map;
		float turn_dir {};

		// Turn to Left.
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			turn_dir += 1.0;
		}
		// Turn to Right.
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			turn_dir -= 1.0;
		}

		// TODO: Add movement.

		// Apply rotation to the camera direction and plane.
		if (turn_dir != 0.0) {
			auto turn_force { turn_dir * PLAYER_TURN_SPEED * dt };

			m_direction = vecRotate(m_direction, turn_force);
			m_plane = vecRotate(m_plane, turn_force);
		}
	}
} // namespace wolfen
