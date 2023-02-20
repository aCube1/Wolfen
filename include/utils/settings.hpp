#ifndef _WOLFEN_UTILS_SETTINGS_HPP_
#define _WOLFEN_UTILS_SETTINGS_HPP_

namespace wolfen::settings {
	constexpr auto WINDOW_TITLE { "Wolfen" };
	constexpr auto WINDOW_WIDTH { 960 };
	constexpr auto WINDOW_HEIGHT { 640 };

	constexpr auto PLAYER_X { WINDOW_WIDTH / 2.0F };
	constexpr auto PLAYER_Y { WINDOW_HEIGHT / 2.0F };
	constexpr auto PLAYER_SPEED { 300.0F };
} // namespace wolfen::settings

#endif /* _WOLFEN_UTILS_HPP_ */
