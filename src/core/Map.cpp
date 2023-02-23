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

	void Map::draw_map(sf::RenderWindow& window) const {
		for (auto x { 0 }; x < m_width; x += 1) {
			for (auto y { 0 }; y < m_height; y += 1) {
				if (getTile(x, y) == TileType::empty) {
					continue;
				}

				// TODO: Render minimap here
				(void)window;
			}
		}
	}

	TileType Map::getTile(std::uint16_t x, std::uint16_t y) const {
		if (x < 0 || y < 0 || x >= m_width || y >= m_height) {
			return TileType::empty;
		}

		const auto pos_x { static_cast<int>(x) };
		const auto pos_y { static_cast<int>(y) };

		return m_data[pos_x * m_width + pos_y];
	}
} // namespace wolfen
