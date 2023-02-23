#include "core/Engine.hpp"

#include "utils/settings.hpp"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <loguru.hpp>
#include <stdexcept>

namespace wolfen {
	Engine::Engine() {
		const sf::View view { sf::FloatRect { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT } };
		const sf::VideoMode video { WINDOW_WIDTH, WINDOW_HEIGHT };

		m_window.create(video, WINDOW_TITLE, sf::Style::Titlebar | sf::Style::Close);
		m_window.setView(view);

		// TODO: Make vertical sync optional;
		m_window.setVerticalSyncEnabled(true);

		if (!m_framebuffer.create(SCREEN_WIDTH, SCREEN_HEIGHT)) {
			throw std::runtime_error("Unable to create framebuffer for rendering!");
		}
		m_buffersprite.setTexture(m_framebuffer.getTexture());

		m_map.generate();

		m_running = true;
	}

	void Engine::run() {
		sf::Clock clock {};

		while (m_window.isOpen() && m_running) {
			m_deltatime = clock.restart().asSeconds();

			processEvents();
			update();
			draw();
		}
	}

	void Engine::processEvents() {
		sf::Event e;

		while (m_window.pollEvent(e)) {
			if (e.type == sf::Event::Closed) {
				m_window.close();
				m_running = false;
			}
		}
	}

	void Engine::update() {
		m_player.update(m_deltatime);
	}

	void Engine::draw() {
		m_framebuffer.clear();
		{ m_player.draw(m_framebuffer); }
		m_framebuffer.display();

		m_window.clear();
		{ m_window.draw(m_buffersprite); }
		m_window.display();
	}
} // namespace wolfen
