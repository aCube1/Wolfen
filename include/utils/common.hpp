#ifndef _WOLFEN_UTILS_COMMON_HPP_
#define _WOLFEN_UTILS_COMMON_HPP_

#include <cmath>

namespace wolfen {
	[[nodiscard]] inline float deg2rad(float deg) {
		return (deg * M_PI) / 180.0F;
	}

	[[nodiscard]] inline float rad2deg(float rad) {
		return (rad * 180.0F) / M_PI;
	}
} // namespace wolfen

#endif /* _WOLFEN_UTILS_COMMON_HPP_ */
