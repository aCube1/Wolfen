#ifndef _WOLFEN_CORE_MAP_HPP_
#define _WOLFEN_CORE_MAP_HPP_

#include <SFML/Graphics/RenderTexture.hpp>
#include <cstdint>
#include <vector>

namespace wolfen {
	enum class TileType {
		Empty = 0,
		Wall,
	};

	class Map {
		private:
			std::uint16_t m_width;
			std::uint16_t m_height;

			sf::Vector2f m_initial_pos;

			std::vector<TileType> m_data;

		public:
			Map() = default;
			~Map() = default;

			void generate();

			void draw(sf::RenderTexture& target) const;

			[[nodiscard]] bool isColliding(float x, float y) const;
			[[nodiscard]] TileType getTile(std::uint16_t x, std::uint16_t y) const;

			[[nodiscard]] inline const sf::Vector2f& getInitialPos() const {
				return m_initial_pos;
			}
	};
} // namespace wolfen

#endif /* _WOLFEN_CORE_MAP_HPP_ */
