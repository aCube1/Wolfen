#include "utils/types.hpp"

namespace wolfen {
	[[nodiscard]] float Vec2::getLenght() const {
		return std::sqrt(x * x + y * y);
	}

	Vec2& Vec2::normalize() {
		const float lenght { getLenght() };
		if (lenght > 0.0) {
			*this = *this / lenght;
		}

		return *this;
	}

	Vec2 Vec2::operator+(Vec2 vec) {
		return Vec2 { x + vec.x, y + vec.y };
	}

	Vec2 Vec2::operator-(Vec2 vec) {
		return Vec2 { x - vec.x, y - vec.y };
	}

	Vec2 Vec2::operator*(float value) {
		return Vec2 { x * value, y * value };
	}

	Vec2 Vec2::operator/(float value) {
		return Vec2 { x / value, y / value };
	}

	Vec2& Vec2::operator+=(Vec2 vec) {
		x += vec.x;
		y += vec.y;

		return *this;
	}
} // namespace wolfen
