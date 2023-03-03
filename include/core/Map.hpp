#ifndef _WOLFEN_CORE_MAP_HPP_
#define _WOLFEN_CORE_MAP_HPP_

#include <SFML/System/Vector2.hpp>
#include <cstdint>
#include <vector>

namespace wolfen {
	enum class TileType {
		Empty = '.',
		PlayerPos = '@',
		Wall1 = '!',
		Wall2 = '*',
		Wall3 = '%',
		Wall4 = '#',
	};

	class Map {
		public:
			Map() = default;
			~Map() = default;

			void generate();

			[[nodiscard]] bool isColliding(float x, float y) const;
			[[nodiscard]] TileType getTile(std::uint16_t x, std::uint16_t y) const;

			[[nodiscard]] inline const sf::Vector2f& getInitialPos() const {
				return m_initial_pos;
			}

		private:
			std::uint16_t m_width;
			std::uint16_t m_height;

			sf::Vector2f m_initial_pos;

			std::vector<TileType> m_data;
	};
} // namespace wolfen

#endif /* _WOLFEN_CORE_MAP_HPP_ */
