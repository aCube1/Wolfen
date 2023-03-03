#ifndef _WOLFEN_CORE_ENGINE_HPP_
#define _WOLFEN_CORE_ENGINE_HPP_

#include "core/Map.hpp"
#include "core/Raycaster.hpp"
#include "entity/Player.hpp"

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace wolfen {
	class Engine {
		public:
			Engine();
			~Engine() = default;

			void run();

		private:
			void processEvents();
			void update(float dt);
			void draw();

			sf::RenderWindow m_window;

			// Framebuffer
			sf::RenderTexture m_framebuffer;
			sf::Sprite m_buffersprite;

			bool m_running { false };

			// TODO: Create a entity manager.
			Player m_player;
			Map m_map;
			Raycaster m_raycaster;
	};
} // namespace wolfen

#endif /* _WOLFEN_CORE_ENGINE_HPP_ */
