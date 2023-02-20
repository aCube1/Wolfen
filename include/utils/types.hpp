#ifndef _WOLFEN_UTILS_TYPES_HPP_
#define _WOLFEN_UTILS_TYPES_HPP_

#include <SDL_rect.h>
#include <cmath>

namespace wolfen {
	class Vec2 : public SDL_FPoint {
		public:
			[[nodiscard]] float getLenght() const;
			Vec2& normalize();

			Vec2 operator+(Vec2 vec);
			Vec2 operator*(float value);
			Vec2 operator/(float value);

			Vec2& operator+=(Vec2 vec);
	};
} // namespace wolfen

#endif /* _WOLFEN_TYPES_HPP_ */
