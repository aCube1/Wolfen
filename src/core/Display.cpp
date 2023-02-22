#include "core/Display.hpp"

#include "utils/settings.hpp"

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

	void Display::load(Vec2 window_size) {
		m_window = createWindow(window_size.x, window_size.y);
		if (!m_window) {
			LOG_F(ERROR, "Unable to create default window!");
			throw std::runtime_error(SDL_GetError());
		}

		m_renderer = createRenderer(m_window);
		if (!m_renderer) {
			LOG_F(ERROR, "Unable to create window renderer!");
			throw std::runtime_error(SDL_GetError());
		}

		SDL_RenderSetLogicalSize(
			m_renderer, settings::SCREEN_SIZE.x, settings::SCREEN_SIZE.y
		);
		SDL_SetRenderDrawBlendMode(m_renderer, SDL_BLENDMODE_BLEND);
	}

	void Display::beginDrawing() {
		setColor(0, 0, 0);
		if (SDL_RenderClear(m_renderer) < 0) {
			LOG_F(ERROR, "Unable to clear display!");
			throw std::runtime_error(SDL_GetError());
		}
	}

	void Display::endDrawing() {
		SDL_RenderPresent(m_renderer);
	}

	Display& Display::fillRect(float x, float y, float w, float h) {
		SDL_FRect rect { x, y, w, h };
		if (SDL_RenderFillRectF(m_renderer, &rect) < 0) {
			LOG_F(ERROR, "Unable to draw rect!");
			throw std::runtime_error(SDL_GetError());
		}

		return *this;
	}

	Display& Display::fillRect(const Vec2& pos, const Vec2& size) {
		return fillRect(pos.x, pos.y, size.x, size.y);
	}

	Display& Display::drawLine(const Vec2& from, const Vec2& to) {
		if (SDL_RenderDrawLineF(m_renderer, from.x, from.y, to.x, to.y) < 0) {
			LOG_F(ERROR, "Unable to draw line!");
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
