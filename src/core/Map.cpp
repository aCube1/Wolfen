#include "core/Map.hpp"

#include "utils/settings.hpp"

#include <array>
#include <cmath>

namespace wolfen {
	void Map::generate() {
		// clang-format off
		// TODO: Load map from files.
		std::array<char, 16 * 16> data = {
			'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#',
			'#', '.', '.', '#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#',
			'#', '.', '.', '#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#',
			'#', '.', '.', '#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#', '.', '#',
			'#', '.', '.', '.', '.', '.', '#', '.', '.', '.', '.', '.', '.', '#', '.', '#',
			'#', '.', '.', '#', '.', '.', '.', '.', '.', '#', '.', '.', '.', '.', '.', '#',
			'#', '.', '.', '#', '.', '.', '#', '.', '.', '.', '#', '.', '.', '.', '.', '#',
			'#', '#', '#', '#', '.', '.', '.', '.', '.', '#', '.', '.', '.', '#', '.', '#',
			'#', '.', '.', '.', '.', '.', '#', '.', '.', '.', '.', '.', '.', '.', '.', '#',
			'#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#',
			'#', '.', '.', '.', '.', '.', '.', '.', '#', '.', '#', '.', '.', '#', '.', '#',
			'#', '#', '#', '#', '.', '#', '#', '#', '.', '#', '.', '.', '#', '#', '.', '#',
			'#', '.', '.', '.', '@', '.', '.', '#', '.', '.', '.', '#', '#', '.', '.', '#',
			'#', '.', '.', '.', '.', '.', '.', '#', '.', '.', '.', '.', '.', '.', '.', '#',
			'#', '.', '.', '.', '.', '.', '.', '#', '.', '.', '.', '.', '.', '.', '.', '#',
			'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#',
		};
		// clang-format on

		m_width = 16;
		m_height = 16;
		for (auto x { 0 }; x < m_width; x += 1) {
			for (auto y { 0 }; y < m_height; y += 1) {
				TileType tile { data[x * m_width + y] };

				if (tile == TileType::PlayerPos) {
					m_initial_pos = { x * TILE_SIZE + TILE_SIZE / 2.0F,
									  y * TILE_SIZE + TILE_SIZE / 2.0F };
					m_data.push_back(TileType::Empty);
					continue;
				}

				m_data.push_back(static_cast<TileType>(tile));
			}
		}
	}

	bool Map::isColliding(float x, float y) const {
		const auto pos_x { static_cast<std::uint16_t>(x / TILE_SIZE) };
		const auto pos_y { static_cast<std::uint16_t>(y / TILE_SIZE) };

		const TileType tile { getTile(pos_x, pos_y) };
		return tile != TileType::Empty;
	}

	TileType Map::getTile(std::uint16_t x, std::uint16_t y) const {
		if (x < 0 || y < 0 || x >= m_width || y >= m_height) {
			return TileType::Empty;
		}

		return m_data.at(x * m_width + y);
	}
} // namespace wolfen
