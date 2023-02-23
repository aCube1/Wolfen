#include "core/Map.hpp"

#include "utils/settings.hpp"

#include <SFML/Graphics/RectangleShape.hpp>

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

		m_initial_pos = { 64.0F, 64.0F };
	}

	void Map::draw(sf::RenderTexture& target) const {
		sf::RectangleShape tile { sf::Vector2f { TILE_WIDTH, TILE_HEIGHT } };
		tile.setFillColor(sf::Color::White);

		for (auto x { 0 }; x < m_width; x += 1) {
			for (auto y { 0 }; y < m_height; y += 1) {
				if (getTile(x, y) == TileType::Empty) {
					continue;
				}

				tile.setPosition(x * TILE_WIDTH, y * TILE_HEIGHT);
				target.draw(tile);
			}
		}
	}

	bool Map::isColliding(float x, float y) const {
		const std::uint16_t pos_x { static_cast<std::uint16_t>(x / TILE_WIDTH) };
		const std::uint16_t pos_y { static_cast<std::uint16_t>(y / TILE_HEIGHT) };

		const TileType tile { getTile(pos_x, pos_y) };

		return tile != TileType::Empty;
	}

	TileType Map::getTile(std::uint16_t x, std::uint16_t y) const {
		const auto pos_x { static_cast<int>(x) };
		const auto pos_y { static_cast<int>(y) };

		if (pos_x < 0 || pos_y < 0 || pos_x >= m_width || pos_y >= m_height) {
			return TileType::Empty;
		}

		return m_data[pos_x * m_width + pos_y];
	}
} // namespace wolfen
