#include "core/Display.hpp"

#include "utils/settings.hpp"

#include <SDL_render.h>
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

	void Display::beginDrawing() {
		setColor(clear_color);
		if (SDL_RenderClear(m_renderer) < 0) {
			LOG_F(ERROR, "Unable to clear display!");
			throw std::runtime_error(SDL_GetError());
		}
	}

	void Display::endDrawing() {
		SDL_RenderPresent(m_renderer);
	}

	Display& Display::fillRect(const Vec2& pos, const Vec2& size) {
		SDL_FRect rect { pos.x, pos.y, size.x, size.y };
		if (SDL_RenderFillRectF(m_renderer, &rect) < 0) {
			LOG_F(ERROR, "Unable to set color!");
			throw std::runtime_error(SDL_GetError());
		}
		return *this;
	}

	Display& Display::setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
		if (SDL_SetRenderDrawColor(m_renderer, r, g, b, a) < 0) {
			LOG_F(ERROR, "Unable to set color!");
			throw std::runtime_error(SDL_GetError());
		}
		return *this;
	}

	Display& Display::setColor(SDL_Color color) {
		return setColor(color.r, color.g, color.b, color.a);
	}
} // namespace wolfen
