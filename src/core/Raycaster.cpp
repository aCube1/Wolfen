#include "core/Raycaster.hpp"

#include "utils/settings.hpp"

#include <cmath>
#include <loguru.hpp>

namespace wolfen {
	void Raycaster::update() {
		for (auto x { 0 }; x < SCREEN_WIDTH; x += 1) {
			auto ray_data { getNextWall(getCameraVector(x)) };
			auto line_height { SCREEN_HEIGHT / ray_data.distance };

			auto line_start { -line_height / 2.0F + SCREEN_HEIGHT / 2.0F };
			line_start = std::max(0.0F, line_start);

			auto line_end { line_height / 2.0F + SCREEN_HEIGHT / 2.0F };
			line_end = std::min(SCREEN_HEIGHT - 1.0F, line_end);

			size_t line_index { static_cast<size_t>(x * 2) };

			m_lines[line_index].position = { static_cast<float>(x), line_start };
			m_lines[line_index + 1].position = { static_cast<float>(x), line_end };

			m_lines[line_index].color = ray_data.color;
			m_lines[line_index + 1].color = ray_data.color;
		}
	}

	void Raycaster::draw(sf::RenderTarget& target, sf::RenderStates states) const {
		states.transform *= getTransform();
		states.texture = nullptr;

		target.draw(m_lines, states);
	}

	sf::Vector2f Raycaster::getCameraVector(float x) {
		auto camera_x { 2.0F * x / SCREEN_WIDTH - 1.0F };
		return m_player.getDirection() + m_player.getPlane() * camera_x;
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

		RayData collision {};

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
		while (collision.tile == TileType::Empty && collision.lenght <= RENDER_DISTANCE) {
			if (distance.x <= distance.y) {
				collision.lenght = distance.x;
				distance.x += delta.x;
				map_pos.x += step.x;
				collision.horizontal = false;
			} else {
				collision.lenght = distance.y;
				distance.y += delta.y;
				map_pos.y += step.y;
				collision.horizontal = true;
			}

			collision.tile = m_map.getTile(map_pos.x, map_pos.y);
		}

		collision.lenght = std::min(RENDER_DISTANCE, collision.lenght);

		// Calculate the distance projected on the camera in a Non-euclidean way to
		// Prevent fisheye effect.
		if (!collision.horizontal) {
			collision.distance = (map_pos.x - ray_pos.x + (1.0 - step.x) / 2.0) /
								 ray_dir.x;
		} else {
			collision.distance = (map_pos.y - ray_pos.y + (1.0 - step.y) / 2.0) /
								 ray_dir.y;
		}

		// Get tile color.
		switch (collision.tile) {
		case TileType::Wall:
			collision.color = sf::Color::Red;
			break;
		default:
			collision.color = sf::Color::Yellow;
			break;
		}

		// Give horizontal lines a different brightness.
		if (collision.horizontal) {
			collision.color.r /= 2;
			collision.color.g /= 2;
			collision.color.b /= 2;
		}

		return collision;
	}
} // namespace wolfen
