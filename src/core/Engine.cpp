#include "core/Engine.hpp"

#include <SDL.h>
#include <stdexcept>

namespace {
	constexpr auto WINDOW_WIDTH { 960 };
	constexpr auto WINDOW_HEIGHT { 640 };
} // namespace

namespace wolfen {
	Engine::Engine() {
		if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
			// TODO: Better logging.
			throw std::runtime_error(SDL_GetError());
		}

		m_display.load(WINDOW_WIDTH, WINDOW_HEIGHT);

		m_running = true;
	}

	void Engine::run() {
		while (m_running) {
			process_events();
			update();
			draw();
		}
	}

	void Engine::process_events() {
		SDL_Event e {};

		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				m_running = false;
			}
		}
	}

	void Engine::update() {}

	void Engine::draw() {
		m_display.beginDrawing();
		{
			constexpr auto rect_dest { SDL_Rect { 64, 64, 32, 32 } };

			SDL_SetRenderDrawColor(m_display.getRenderer(), 255, 0, 0, 255);
			SDL_RenderFillRect(m_display.getRenderer(), &rect_dest);
		}
		m_display.endDrawing();
	}
} // namespace wolfen
