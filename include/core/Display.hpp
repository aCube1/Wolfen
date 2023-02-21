#ifndef _WOLFEN_CORE_DISPLAY_HPP_
#define _WOLFEN_CORE_DISPLAY_HPP_

#include "utils/types.hpp"

#include <SDL_pixels.h>
#include <SDL_render.h>
#include <SDL_video.h>

namespace wolfen {
	class Display {
		private:
			SDL_Window *m_window { nullptr };
			SDL_Renderer *m_renderer { nullptr };

			static constexpr SDL_Color clear_color { 0, 0, 0, SDL_ALPHA_OPAQUE };

		public:
			Display() = default;
			~Display();

			void load(int width, int height);
			void beginDrawing();
			void endDrawing();

			Display& fillRect(const Vec2& pos, const Vec2& size);
			Display& drawLine(const Vec2& from, const Vec2& to);

			Display& setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a = SDL_ALPHA_OPAQUE);
			Display& setColor(SDL_Color color);

			[[nodiscard]] inline SDL_Renderer *getRenderer() const {
				return m_renderer;
			}
	};
} // namespace wolfen

#endif /* _WOLFEN_CORE_DISPLAY_HPP_ */
