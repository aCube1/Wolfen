#ifndef _WOLFEN_CORE_DISPLAY_HPP_
#define _WOLFEN_CORE_DISPLAY_HPP_

#include <SDL_pixels.h>
#include <SDL_render.h>
#include <SDL_video.h>

namespace wolfen {
	class Display {
		public:
			static constexpr SDL_Color clear_color { 0, 0, 0, SDL_ALPHA_OPAQUE };

		public:
			Display() = default;
			~Display();

			void load(int width, int height);

			inline void beginDrawing() {
				SDL_SetRenderDrawColor(
					m_renderer, clear_color.r, clear_color.g, clear_color.b, clear_color.a
				);
				SDL_RenderClear(m_renderer);
			}

			inline void endDrawing() {
				SDL_RenderPresent(m_renderer);
			}

			inline SDL_Renderer *getRenderer() const {
				return m_renderer;
			}

		private:
			SDL_Window *m_window { nullptr };
			SDL_Renderer *m_renderer { nullptr };
	};
} // namespace wolfen

#endif /* _WOLFEN_CORE_DISPLAY_HPP_ */
