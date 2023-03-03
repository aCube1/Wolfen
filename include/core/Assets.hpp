#ifndef _WOLFEN_CORE_ASSETS_HPP_
#define _WOLFEN_CORE_ASSETS_HPP_

#include <SFML/Graphics/Texture.hpp>
#include <memory>
#include <string>
#include <unordered_map>

namespace wolfen {
	// NOTE: I don't like this way of loading and getting textures.
	class Assets {
		public:
			using UniqueTexture = std::unique_ptr<sf::Texture>;

			Assets() = default;
			~Assets() = default;

			static void loadAllTextures(const std::string& folder);
			static void loadTexture(const std::string& name, const std::string& filepath);

			[[nodiscard]] static sf::Texture *getTexture(const std::string& name);

		private:
			static std::unordered_map<std::string, UniqueTexture> m_textures;
	};
} // namespace wolfen

#endif /* _WOLFEN_CORE_ASSETS_HPP_ */
