#ifndef _WOLFEN_CORE_MAP_HPP_
#define _WOLFEN_CORE_MAP_HPP_

#include "core/Display.hpp"

#include <cstdint>
#include <vector>

namespace wolfen {
	enum class TileType {
		empty = 0,
		wall,
	};

	class Map {
		private:
			std::uint16_t m_width;
			std::uint16_t m_height;

			std::vector<TileType> m_data;

		public:
			Map() = default;
			~Map() = default;

			void generate();

			void draw(Display& display) const;

			[[nodiscard]] TileType getTile(Vec2 pos) const;
			[[nodiscard]] TileType getTile(std::uint16_t x, std::uint16_t y) const;
	};
} // namespace wolfen

#endif /* _WOLFEN_CORE_MAP_HPP_ */
