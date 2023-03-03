#include "core/Raycaster.hpp"

#include "core/Assets.hpp"
#include "utils/settings.hpp"

#include <cmath>

namespace wolfen {
	void Raycaster::update() {
		RayData raydata {};
		float line_height {};
		float line_start {};
		float line_end {};

		for (auto x { 0 }; x < SCREEN_WIDTH; x += 1) {
			raydata = getNextWall(getCameraVector(x));
			line_height = SCREEN_HEIGHT / raydata.distance;

			line_start = -line_height / 2.0F + SCREEN_HEIGHT / 2.0F;
			// line_start = std::max(0.0F, line_start);

			line_end = line_height / 2.0F + SCREEN_HEIGHT / 2.0F;
			// line_end = std::min(SCREEN_HEIGHT - 1.0F, line_end);

			const auto line_idx { static_cast<size_t>(x * 2) };

			// Set vertical line position and lenght.
			m_lines[line_idx].position = { static_cast<float>(x), line_start };
			m_lines[line_idx + 1].position = { static_cast<float>(x), line_end };

			if (m_raycaster_type == RaycasterType::NO_TEXTURES) {
				auto color { getColor(raydata.horizontal, raydata.tile) };

				m_lines[line_idx].color = color;
				m_lines[line_idx + 1].color = color;
			} else {
				auto tex_coords { getTextureCoords(raydata.tile, raydata.texture_x) };

				m_lines[line_idx].texCoords = { tex_coords.x, 0.0 };
				m_lines[line_idx + 1].texCoords = { tex_coords.x, TEXTURE_SIZE };
			}
		}
	}

	void Raycaster::draw(sf::RenderTarget& target, sf::RenderStates states) const {
		states.transform *= getTransform();

		states.texture = m_raycaster_type == RaycasterType::NO_TEXTURES
						   ? nullptr
						   : states.texture = Assets::getTexture("walls");

		target.draw(m_lines, states);
	}

	RayData Raycaster::getNextWall(sf::Vector2f ray_dir) {
		auto ray_pos { m_player.getPosition() / static_cast<float>(TILE_SIZE) };

		// Lenght of the ray after moving 1 cell along x-axis or y-axis.
		sf::Vector2f delta { ray_dir.x == 1 ? 0.0F : std::abs(1.0F / ray_dir.x),
							 ray_dir.y == 1 ? 0.0F : std::abs(1.0F / ray_dir.y) };

		// Which cell in the map we are in.
		sf::Vector2i map_pos { ray_pos };

		sf::Vector2i step {}; // What direction to step in. (+1 or -1 for each dimension)
		sf::Vector2f distance {}; // Distance from position to next gridline, for x and y.

		RayData raydata {};

		// X - Component
		if (ray_dir.x < 0.0) {
			distance.x = (ray_pos.x - map_pos.x) * delta.x;
			step.x = -1;
		} else {
			distance.x = (map_pos.x + 1.0 - ray_pos.x) * delta.x;
			step.x = 1;
		}

		// Y - Component
		if (ray_dir.y < 0.0) {
			distance.y = (ray_pos.y - map_pos.y) * delta.y;
			step.y = -1;
		} else {
			distance.y = (map_pos.y + 1.0 - ray_pos.y) * delta.y;
			step.y = 1;
		}

		// Get distance to the next wall.
		while (raydata.tile == TileType::Empty && raydata.lenght <= RENDER_DISTANCE) {
			if (distance.x < distance.y) {
				raydata.horizontal = true;
				raydata.lenght = distance.x;
				distance.x += delta.x;
				map_pos.x += step.x;
			} else {
				raydata.horizontal = false;
				raydata.lenght = distance.y;
				distance.y += delta.y;
				map_pos.y += step.y;
			}

			raydata.tile = m_map.getTile(map_pos.x, map_pos.y);
		}
		raydata.lenght = std::min(RENDER_DISTANCE, raydata.lenght);

		// Calculate the distance projected on the camera in a Non-euclidean way, this
		// prevent fisheye effect.
		if (raydata.horizontal) {
			raydata.distance = (map_pos.x - ray_pos.x + (1.0 - step.x) / 2.0) / ray_dir.x;
		} else {
			raydata.distance = (map_pos.y - ray_pos.y + (1.0 - step.y) / 2.0) / ray_dir.y;
		}

		// If the raycaster is texturized, then calculate texture X position.
		if (m_raycaster_type == RaycasterType::TEXTURIZED) {
			raydata.texture_x = getTextureX(raydata, ray_dir, ray_pos);
		}

		return raydata;
	}

	int Raycaster::getTextureX(
		const RayData& raydata, sf::Vector2f ray_dir, sf::Vector2f ray_pos
	) const {
		double wall_x {};
		int texture_x {};

		if (raydata.horizontal) {
			wall_x = ray_pos.y + raydata.distance * ray_dir.y;
		} else {
			wall_x = ray_pos.x + raydata.distance * ray_dir.x;
		}
		wall_x -= std::floor(wall_x);

		texture_x = static_cast<int>(wall_x * static_cast<double>(TEXTURE_SIZE));

		// Flip the texture if we see it on the other side of us, this prevent mirrored
		// effect.
		if ((raydata.horizontal && ray_dir.x <= 0.0) ||
			(!raydata.horizontal && ray_dir.y >= 0.0)) {
			texture_x = TEXTURE_SIZE - texture_x - 1;
		}

		return texture_x;
	}

	sf::Color Raycaster::getColor(bool horizontal, TileType tile) const {
		sf::Color color;

		switch (tile) {
		case TileType::Wall1:
			color = sf::Color::Red;
			break;
		case TileType::Wall2:
			color = sf::Color::Green;
			break;
		case TileType::Wall3:
			color = sf::Color::Blue;
			break;
		case TileType::Wall4:
			color = sf::Color::White;
			break;
		default:
			color = sf::Color::Yellow;
			break;
		}

		// Give horizontal walls a different brightness.
		if (horizontal) {
			color.r /= 2;
			color.g /= 2;
			color.b /= 2;
		}

		return color;
	}

	sf::Vector2f Raycaster::getTextureCoords(TileType tile, float texture_x) const {
		sf::Vector2f coords {};

		switch (tile) {
		case TileType::Wall1:
			coords = { 0.0, 0.0 };
			break;
		case TileType::Wall2:
			coords = { 32.0, 0.0 };
			break;
		case TileType::Wall3:
			coords = { 64.0, 0.0 };
			break;
		case TileType::Wall4:
			coords = { 96.0, 0.0 };
			break;
		default:
			return { 0.0, 0.0 };
		}
		coords.x += texture_x;

		return coords;
	}

	sf::Vector2f Raycaster::getCameraVector(float x) {
		auto camera_x { 2.0F * x / SCREEN_WIDTH - 1.0F };
		return m_player.getDirection() + m_player.getPlane() * camera_x;
	}
} // namespace wolfen
