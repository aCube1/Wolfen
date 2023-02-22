#include "core/Engine.hpp"

#include "utils/settings.hpp"

#include <SDL.h>
#include <SDL_events.h>
#include <SDL_timer.h>
#include <loguru.hpp>
#include <stdexcept>

namespace wolfen {
	Engine::Engine() : m_player { settings::PLAYER_POS, settings::PLAYER_SPEED } {
		if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
			LOG_F(ERROR, "Unable to initialize SDL2!");
			throw std::runtime_error(SDL_GetError());
		}

		m_display.load(settings::WINDOW_SIZE);

		m_map.generate();

		m_running = true;
	}

	void Engine::run() {
		while (m_running) {
			auto last_time = SDL_GetTicks64();

			processEvents();
			update();
			draw();

			m_ctx.dt = (SDL_GetTicks64() - last_time) / 1000.0;
		}
	}

	void Engine::processEvents() {
		SDL_Event e {};

		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				m_running = false;
			}
		}

		SDL_PumpEvents();
		m_ctx.keyboard = SDL_GetKeyboardState(nullptr);
	}

	void Engine::update() {
		m_player.update(m_ctx);
	}

	void Engine::draw() {
		m_display.beginDrawing();
		{
			m_player.draw(m_ctx);
			m_map.draw(m_display);
		}
		m_display.endDrawing();
	}
} // namespace wolfen
