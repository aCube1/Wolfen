#ifndef _WOLFEN_ENTITY_PLAYER_HPP_
#define _WOLFEN_ENTITY_PLAYER_HPP_

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>

namespace wolfen {
	class Player {
		private:
			sf::VertexArray m_line { sf::Lines, 2 };

			sf::Vector2f m_position;
			sf::Vector2f m_motion {};
			sf::Vector2f m_velocity {};

			float m_angle { 90.0F };

		public:
			Player() = default;

			void update(float dt);
			void draw(sf::RenderTexture& target);

			inline void setPosition(sf::Vector2f pos) {
				m_position = pos;
			}

		private:
			void checkInput();
	};
} // namespace wolfen

#endif /* _WOLFEN_ENTITY_PLAYER_HPP_ */
