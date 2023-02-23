#include "entity/Player.hpp"

#include "utils/common.hpp"
#include "utils/settings.hpp"

#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <cmath>
#include <loguru.hpp>

namespace wolfen {
	void Player::update(float dt) {
		checkInput();
		normalize(m_motion);

		m_velocity = m_motion * PLAYER_SPEED * dt;
		m_motion = { 0.0, 0.0 };

		m_position += m_velocity;
	}

	void Player::draw(sf::RenderTexture& target) {
		// Draw player direction.

		m_line[0].color = sf::Color::Red;
		m_line[0].position = m_position;

		m_line[1].color = sf::Color::Red;
		m_line[1].position = sf::Vector2f {
			m_position.x - std::cos(deg2rad(m_angle)) * 16.0F,
			m_position.y - std::sin(deg2rad(m_angle)) * 16.0F
		};

		target.draw(m_line);
	}

	void Player::checkInput() {
		// Apply movement rotation.
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			m_angle -= PLAYER_ROTATION_SPEED;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			m_angle += PLAYER_ROTATION_SPEED;
		}

		// Calculate horizontal movement direction.
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			m_motion.x -= std::cos(deg2rad(m_angle - 90.0));
			m_motion.y -= std::sin(deg2rad(m_angle - 90.0));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			m_motion.x += std::cos(deg2rad(m_angle - 90.0));
			m_motion.y += std::sin(deg2rad(m_angle - 90.0));
		}

		// Calculate vertical movement direction.
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			m_motion.x -= std::cos(deg2rad(m_angle));
			m_motion.y -= std::sin(deg2rad(m_angle));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			m_motion.x += std::cos(deg2rad(m_angle));
			m_motion.y += std::sin(deg2rad(m_angle));
		}
	}
} // namespace wolfen
