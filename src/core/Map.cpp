#include "core/Map.hpp"

#include "utils/settings.hpp"

namespace wolfen {
	void Map::generate() {
		// clang-format off
		auto data = {
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
			1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
			1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1,
			1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
			1, 0, 0, 1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1,
			1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
			1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1,
			1, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
			1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1,
			1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
			1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1,
			1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1,
			1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1,
			1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1,
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		};
		// clang-format on

		for (auto tile : data) {
			m_data.push_back(static_cast<TileType>(tile));
		}

		m_width = 16;
		m_height = 16;
	}

	void Map::draw(Display& display) const {
		for (auto x { 0 }; x < m_width; x += 1) {
			for (auto y { 0 }; y < m_height; y += 1) {
				if (getTile(x, y) == TileType::empty) {
					continue;
				}

				display.setColor(0, 255, 255)
					.fillRect(
						x * settings::TILE_SIZE.x, y * settings::TILE_SIZE.y,
						settings::TILE_SIZE.x, settings::TILE_SIZE.y
					);
			}
		}
	}

	TileType Map::getTile(Vec2 pos) const {
		if (pos.x < 0 || pos.y < 0 || pos.x >= m_width || pos.y >= m_height) {
			return TileType::empty;
		}

		const auto pos_x { static_cast<int>(pos.x) };
		const auto pos_y { static_cast<int>(pos.y) };

		return m_data[pos_x * m_width + pos_y];
	}

	TileType Map::getTile(std::uint16_t x, std::uint16_t y) const {
		return getTile(Vec2 { static_cast<float>(x), static_cast<float>(y) });
	}
} // namespace wolfen
