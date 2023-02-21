#ifndef _WOLFEN_ENTITY_PLAYER_HPP_
#define _WOLFEN_ENTITY_PLAYER_HPP_

#include "entity/IEntity.hpp"
#include "utils/settings.hpp"

namespace wolfen {
	class Player : public IEntity {
		private:
			const float m_maxspeed {};

			Vec2 m_motion {};
			Vec2 m_velocity {};
			float m_rotation {};

		public:
			Player(float x, float y, float speed)
				: IEntity { x, y, settings::PLAYER_WIDTH, settings::PLAYER_HEIGHT },
				  m_maxspeed { speed } {}

			void update(const Context& ctx) override;
			void draw(const Context& ctx) override;

		private:
			void checkInput(const Uint8 *keyboard);
	};
} // namespace wolfen

#endif /* _WOLFEN_ENTITY_PLAYER_HPP_ */
