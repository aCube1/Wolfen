#ifndef _WOLFEN_CORE_ENGINE_HPP_
#define _WOLFEN_CORE_ENGINE_HPP_

#include "core/Display.hpp"

namespace wolfen {
	class Engine {
		public:
			Engine();
			~Engine() = default;

			void run();

		private:
			Display m_display;
			bool m_running { false };

		private:
			void process_events();
			void update();
			void draw();
	};
} // namespace wolfen

#endif /* _WOLFEN_CORE_ENGINE_HPP_ */
