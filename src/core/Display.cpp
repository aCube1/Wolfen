#include "core/Display.hpp"

#include "utils.hpp"

#include <cstdint>
#include <loguru.hpp>
#include <stdexcept>

namespace {
	SDL_Window *createWindow(int width, int height) {
		std::int32_t flags { SDL_WINDOW_OPENGL };
		SDL_Point position { SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED };

		return SDL_CreateWindow(
			wolfen::settings::WINDOW_TITLE, position.x, position.y, width, height, flags
		);
	}

	SDL_Renderer *createRenderer(SDL_Window *window) {
		std::int32_t flags { SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED };

		return SDL_CreateRenderer(window, -1, flags);
	}
} // namespace

namespace wolfen {
	Display::~Display() {
		SDL_DestroyRenderer(m_renderer);
		SDL_DestroyWindow(m_window);
	}

	void Display::load(int width, int height) {
		m_window = createWindow(width, height);
		if (!m_window) {
			LOG_F(ERROR, "Unable to create default window!");
			throw std::runtime_error(SDL_GetError());
		}

		m_renderer = createRenderer(m_window);
		if (!m_renderer) {
			LOG_F(ERROR, "Unable to create window renderer!");
			throw std::runtime_error(SDL_GetError());
		}

		SDL_SetRenderDrawBlendMode(m_renderer, SDL_BLENDMODE_BLEND);
	}
} // namespace wolfen
