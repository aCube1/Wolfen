#ifndef _WOLFEN_CORE_ENGINE_HPP_
#define _WOLFEN_CORE_ENGINE_HPP_

#include "core/Display.hpp"

namespace wolfen {
	class Engine {
		private:
			Display m_display;
			bool m_running { false };

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
