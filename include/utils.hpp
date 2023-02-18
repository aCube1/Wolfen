#ifndef _WOLFEN_UTILS_HPP_
#define _WOLFEN_UTILS_HPP_

#include <SDL_rect.h>

namespace wolfen {
	using Vector2 = SDL_FPoint;

	namespace settings {
		constexpr auto WINDOW_TITLE { "Wolfen" };
		constexpr auto WINDOW_WIDTH { 960 };
		constexpr auto WINDOW_HEIGHT { 640 };

		constexpr auto PLAYER_X { WINDOW_WIDTH / 2.0 };
		constexpr auto PLAYER_Y { WINDOW_HEIGHT / 2.0 };
	} // namespace settings
} // namespace wolfen

#endif /* _WOLFEN_UTILS_HPP_ */
