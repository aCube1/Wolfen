#ifndef _WOLFEN_ENTITY_PLAYER_HPP_
#define _WOLFEN_ENTITY_PLAYER_HPP_

#include "entity/IEntity.hpp"

namespace wolfen {
	class Player : public IEntity {
		private:
			const float m_maxspeed { 200.0 };

			Vec2 m_motion {};
			Vec2 m_velocity {};

		public:
			Player(float x, float y) : IEntity(x, y, 32.0, 32.0) {}

			void input(const Uint8 *keyboard) override;
			void update(double dt) override;
			void draw(Display& display) override;
	};
} // namespace wolfen

#endif /* _WOLFEN_ENTITY_PLAYER_HPP_ */
