#ifndef _WOLFEN_UTILS_COMMON_HPP_
#define _WOLFEN_UTILS_COMMON_HPP_

#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>
#include <cmath>

namespace wolfen {
	template <typename T>
	inline sf::Vector2<T> vecRotate(const sf::Vector2<T>& vec, T value) {
		return { vec.x * std::cos(value) - vec.y * std::sin(value),
				 vec.x * std::sin(value) + vec.y * std::cos(value) };
	}

	[[nodiscard]] inline float deg2rad(float deg) {
		return (deg * M_PI) / 180.0F;
	}

	[[nodiscard]] inline float rad2deg(float rad) {
		return (rad * 180.0F) / M_PI;
	}
} // namespace wolfen

#endif /* _WOLFEN_UTILS_COMMON_HPP_ */
