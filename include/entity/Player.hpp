#ifndef _WOLFEN_ENTITY_PLAYER_HPP_
#define _WOLFEN_ENTITY_PLAYER_HPP_

#include "utils/common.hpp"
#include "utils/types.hpp"

namespace wolfen {
	class Player {
		private:
			const float m_maxspeed {};

			Vec2 m_position;
			Vec2 m_motion {};
			Vec2 m_velocity {};
			float m_angle { 90.0F };

		public:
			Player(const Vec2 p_position, float p_speed)
				: m_maxspeed { p_speed }, m_position { p_position } {}

			void update(const Context& ctx);
			void draw(const Context& ctx);

		private:
			void checkInput(const Uint8 *keyboard);
	};
} // namespace wolfen

#endif /* _WOLFEN_ENTITY_PLAYER_HPP_ */
