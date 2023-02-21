#ifndef _WOLFEN_ENTITY_IENTITY_HPP_
#define _WOLFEN_ENTITY_IENTITY_HPP_

#include "utils/common.hpp"
#include "utils/types.hpp"

#include <SDL_events.h>

namespace wolfen {
	class IEntity {
		protected:
			Vec2 m_position;
			Vec2 m_size; // TODO: Add sprite rendering;

		public:
			IEntity(Vec2 position, Vec2 size)
				: m_position { position }, m_size { size } {}

			IEntity(float x, float y, float w, float h)
				: m_position { x, y }, m_size { w, h } {}

			virtual ~IEntity() = default;

			virtual void update(const Context& ctx) = 0;
			virtual void draw(const Context& ctx) = 0;
	};
} // namespace wolfen

#endif /* _WOLFEN_ENTITY_IENTITY_HPP_ */
