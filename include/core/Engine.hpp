#ifndef _WOLFEN_CORE_ENGINE_HPP_
#define _WOLFEN_CORE_ENGINE_HPP_

#include "core/Display.hpp"
#include "entity/Player.hpp"

namespace wolfen {
	class Engine {
		private:
			Display m_display;
			const Uint8 *m_keyboard { nullptr };
			double m_deltatime { 0.0 };
			bool m_running { false };

			// TODO: Create a entity manager.
			Player m_player;

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
