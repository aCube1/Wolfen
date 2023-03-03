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
			float texture_x {};
	};

	enum class RaycasterType {
		NO_TEXTURES,
		TEXTURIZED,
	};

	class Raycaster : public sf::Drawable, public sf::Transformable {
		public:
			Raycaster(Player& player, Map& map, RaycasterType type)
				: m_player { player }, m_map { map }, m_raycaster_type { type } {}

			~Raycaster() override = default;

			void update();

			inline void setRaycasterType(RaycasterType type) {
				m_raycaster_type = type;
			}

			[[nodiscard]] inline RaycasterType getRaycasterType() const {
				return m_raycaster_type;
			}

		private:
			void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

			// Measures the distance to the next wall.
			//
			// Return a RayData object with distance to the wall, the tile type, if the
			// ray touched the horizontal axis of the wall, and the wall color.
			RayData getNextWall(sf::Vector2f ray_dir);

			// Get x-coordinate of the texture.
			int getTextureX(
				const RayData& raydata, sf::Vector2f ray_dir, sf::Vector2f ray_pos
			) const;

			sf::Color getColor(bool horizontal, TileType tile) const;
			sf::Vector2f getTextureCoords(TileType tile, float texture_x) const;

			// Get the vector of the camera-plane, a 2D plane that represent
			// the player's FOV(Field Of View).
			sf::Vector2f getCameraVector(float x);

			Player& m_player;
			Map& m_map;

			// FIXME:Remove hardcoded texture size.
			sf::Vector2u m_texture_size { 32 * 4, 32 };

			RaycasterType m_raycaster_type;

			sf::VertexArray m_lines { sf::Lines, SCREEN_WIDTH * 2 };
	};
} // namespace wolfen

#endif /* _WOLFEN_CORE_RAYCASTER_HPP_ */
