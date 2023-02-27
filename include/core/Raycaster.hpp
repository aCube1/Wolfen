#ifndef _WOLFEN_CORE_RAYCASTER_HPP_
#define _WOLFEN_CORE_RAYCASTER_HPP_

#include "core/Map.hpp"
#include "entity/Player.hpp"
#include "utils/settings.hpp"

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/VertexArray.hpp>

namespace wolfen {
	struct RayData {
		public:
			TileType tile { TileType::Empty };
			bool horizontal {};
			float distance {}; // Wall perpendicular distance
			float lenght {};
			sf::Color color {};
	};

	class Raycaster : public sf::Drawable, public sf::Transformable {
		public:
			Raycaster(Player& player, Map& map)
				: m_player { player }, m_map { map }, m_lines { sf::Lines,
																SCREEN_WIDTH * 2 } {}

			~Raycaster() override = default;

			void update();

		private:
			void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

			// Get the vector of the camera-plane, a 2D plane that represent
			// the player's FOV(Field Of View).
			sf::Vector2f getCameraVector(float x);

			// Measures the distance to the next wall.
			//
			// Return a RayData object with distance to the wall, the tile type, if the
			// ray touched the horizontal axis of the wall, and the wall color.
			RayData getNextWall(sf::Vector2f ray);

			Player& m_player;
			Map& m_map;
			sf::VertexArray m_lines;
	};
} // namespace wolfen

#endif /* _WOLFEN_CORE_RAYCASTER_HPP_ */
