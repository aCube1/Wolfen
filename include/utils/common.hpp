#ifndef _WOLFEN_UTILS_COMMON_HPP_
#define _WOLFEN_UTILS_COMMON_HPP_

#include <SDL_stdinc.h>
#include <cmath>

namespace wolfen {
	class Display;

	struct Context {
		public:
			Display& display;
			double dt;
			const Uint8 *keyboard;
	};

	[[nodiscard]] inline float deg2rad(float deg) {
		return (deg * M_PI) / 180.0F;
	}

	[[nodiscard]] inline float rad2deg(float rad) {
		return (rad * 180.0F) / M_PI;
	}
} // namespace wolfen

#endif /* _WOLFEN_UTILS_COMMON_HPP_ */
