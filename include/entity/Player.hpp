#ifndef _WOLFEN_ENTITY_PLAYER_HPP_
#define _WOLFEN_ENTITY_PLAYER_HPP_

#include "entity/IEntity.hpp"

namespace wolfen {
	class Player : public IEntity {
		private:
			const float m_maxspeed {};

			Vec2 m_motion {};
			Vec2 m_velocity {};
			float m_rotation {};

		public:
			Player(float x, float y, float speed)
				: IEntity { x, y, 32.0, 32.0 }, m_maxspeed { speed } {}

			void input(const Uint8 *keyboard) override;
			void update(double dt) override;
			void draw(Display& display) override;
	};
} // namespace wolfen

#endif /* _WOLFEN_ENTITY_PLAYER_HPP_ */
