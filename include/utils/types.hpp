#ifndef _WOLFEN_UTILS_TYPES_HPP_
#define _WOLFEN_UTILS_TYPES_HPP_

#include <SDL_rect.h>
#include <cmath>

namespace wolfen {
	class Vec2 : public SDL_FPoint {
		public:
			[[nodiscard]] inline float getLenght() const {
				return std::sqrt(x * x + y * y);
			}

			inline Vec2 operator+(Vec2 vec) {
				return Vec2 { x + vec.x, y + vec.y };
			}

			inline Vec2 operator*(float value) {
				return Vec2 { x * value, y * value };
			}

			inline Vec2& operator+=(Vec2 vec) {
				x += vec.x;
				y += vec.y;

				return *this;
			}
	};
} // namespace wolfen

#endif /* _WOLFEN_TYPES_HPP_ */
