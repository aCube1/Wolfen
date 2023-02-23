#ifndef _WOLFEN_UTILS_COMMON_HPP_
#define _WOLFEN_UTILS_COMMON_HPP_

#include <SFML/System/Vector2.hpp>
#include <cmath>

namespace wolfen {
	class Display;

	template <typename T>
	[[nodiscard]] inline T getLenght(const sf::Vector2<T> vec) {
		return std::sqrt(vec.x * vec.x + vec.y * vec.y);
	}

	template <typename T>
	inline void normalize(sf::Vector2<T>& vec) {
		auto lenght { getLenght(vec) };
		if (lenght > 0) {
			vec /= lenght;
		}
	}

	[[nodiscard]] inline float deg2rad(float deg) {
		return (deg * M_PI) / 180.0F;
	}

	[[nodiscard]] inline float rad2deg(float rad) {
		return (rad * 180.0F) / M_PI;
	}
} // namespace wolfen

#endif /* _WOLFEN_UTILS_COMMON_HPP_ */
