#ifndef _WOLFEN_UTILS_SETTINGS_HPP_
#define _WOLFEN_UTILS_SETTINGS_HPP_

namespace wolfen::settings {
	constexpr auto WINDOW_TITLE { "Wolfen" };
	constexpr auto WINDOW_WIDTH { 960 };
	constexpr auto WINDOW_HEIGHT { 640 };

	constexpr auto PLAYER_X { WINDOW_WIDTH / 2.0F };
	constexpr auto PLAYER_Y { WINDOW_HEIGHT / 2.0F };
	constexpr auto PLAYER_WIDTH { 32.0F };
	constexpr auto PLAYER_HEIGHT { 32.0F };

	constexpr auto PLAYER_SPEED { 300.0F };
	constexpr auto PLAYER_ROTATION_SPEED { 5.0F };

	constexpr auto MAP_WIDTH { 8 };
	constexpr auto MAP_HEIGHT { 8 };
	constexpr auto MAP_SIZE { MAP_WIDTH * MAP_HEIGHT };

	constexpr auto TILE_WIDTH { 32.0F };
	constexpr auto TILE_HEIGHT { 32.0F };
} // namespace wolfen::settings

#endif /* _WOLFEN_UTILS_HPP_ */
