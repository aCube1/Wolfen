#ifndef _WOLFEN_UTILS_SETTINGS_HPP_
#define _WOLFEN_UTILS_SETTINGS_HPP_

#include "utils/types.hpp"

namespace wolfen::settings {
	constexpr auto WINDOW_TITLE { "Wolfen" };
	constexpr Vec2 WINDOW_SIZE { 960, 640 };
	constexpr Vec2 SCREEN_SIZE { 480, 320 };

	constexpr Vec2 PLAYER_POS { 64, 64 };
	constexpr auto PLAYER_SPEED { 200 };
	constexpr auto PLAYER_ROTATION_SPEED { 5.0F };

	constexpr Vec2 TILE_SIZE { 16, 16 };
} // namespace wolfen::settings

#endif /* _WOLFEN_UTILS_HPP_ */
