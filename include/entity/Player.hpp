#ifndef _WOLFEN_ENTITY_PLAYER_HPP_
#define _WOLFEN_ENTITY_PLAYER_HPP_

#include "core/Map.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>

namespace wolfen {
	class Player {
		public:
			Player(Map& map);

			void update(float dt, sf::RenderWindow& window);

			inline void setPosition(sf::Vector2f pos) {
				m_position = pos;
			}

			[[nodiscard]] inline const sf::Vector2f& getPosition() const {
				return m_position;
			}

			[[nodiscard]] inline const sf::Vector2f& getDirection() const {
				return m_direction;
			}

			[[nodiscard]] inline const sf::Vector2f& getPlane() const {
				return m_plane;
			}

		private:
			void move(float motion, float dt);
			void strafe(float side, float dt);

			Map& m_map;

			sf::Vector2f m_position {};
			sf::Vector2f m_direction {};
			sf::Vector2f m_plane {};
	};
} // namespace wolfen

#endif /* _WOLFEN_ENTITY_PLAYER_HPP_ */
