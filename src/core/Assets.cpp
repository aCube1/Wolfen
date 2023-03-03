#include "core/Assets.hpp"

#include <loguru.hpp>
#include <stdexcept>

namespace wolfen {
	std::unordered_map<std::string, Assets::UniqueTexture> Assets::m_textures;

	void Assets::loadAllTextures(const std::string& folder) {
		loadTexture("walls", folder + "/walls.png");
	}

	void Assets::loadTexture(const std::string& name, const std::string& filepath) {
		m_textures[name] = std::make_unique<sf::Texture>();

		if (!m_textures.at(name)->loadFromFile(filepath)) {
			LOG_F(ERROR, "Unable to load texture: %s", filepath.c_str());
			throw std::runtime_error("Error loading texture.");
		}
	}

	sf::Texture *Assets::getTexture(const std::string& name) {
		try {
			return m_textures.at(name).get();
		} catch (const std::out_of_range& e) {
			LOG_F(ERROR, "Unable to get Texture: %s", name.c_str());
			return nullptr;
		}
	}
} // namespace wolfen
