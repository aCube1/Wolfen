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
			Vec2 operator-(Vec2 vec);

			Vec2 operator*(float value);
			Vec2 operator/(float value);

			Vec2& operator+=(Vec2 vec);
	};

	class Rect : public SDL_FRect {};

	class Color : public SDL_Color {
		public:
			Uint8 r { 0 };
			Uint8 g { 0 };
			Uint8 b { 0 };
			Uint8 a { SDL_ALPHA_OPAQUE };

			Color(Uint8 p_r, Uint8 p_g, Uint8 p_b, Uint8 p_a) noexcept
				: r { p_r }, g { p_g }, b { p_b }, a { p_a } {};
			Color(SDL_Color p_color) noexcept
				: Color { p_color.r, p_color.g, p_color.b, p_color.a } {};
	};
} // namespace wolfen

#endif /* _WOLFEN_TYPES_HPP_ */
