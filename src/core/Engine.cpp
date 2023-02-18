#include "core/Engine.hpp"

#include "utils.hpp"

#include <SDL.h>
#include <loguru.hpp>
#include <stdexcept>

namespace wolfen {
	Engine::Engine() {
		if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
			LOG_F(ERROR, "Unable to initialize SDL2!");
			throw std::runtime_error(SDL_GetError());
		}

		m_display.load(settings::WINDOW_WIDTH, settings::WINDOW_HEIGHT);

		m_running = true;
	}

	void Engine::run() {
		while (m_running) {
			processEvents();
			update();
			draw();
		}
	}

	void Engine::processEvents() {
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
		{}
		m_display.endDrawing();
	}
} // namespace wolfen
