#ifndef _WOLFEN_CORE_ENGINE_HPP_
#define _WOLFEN_CORE_ENGINE_HPP_

#include "core/Display.hpp"
#include "core/Map.hpp"
#include "entity/Player.hpp"

namespace wolfen {
	class Engine {
		private:
			Display m_display;
			Context m_ctx { m_display, 0.0, nullptr };
			bool m_running { false };

			// TODO: Create a entity manager.
			Player m_player;
			Map m_map;

		public:
			Engine();
			~Engine() = default;

			void run();

		private:
			void processEvents();
			void update();
			void draw();
	};
} // namespace wolfen

#endif /* _WOLFEN_CORE_ENGINE_HPP_ */
