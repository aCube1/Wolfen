#include "core/Engine.hpp"

#include "core/Assets.hpp"
#include "utils/settings.hpp"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <loguru.hpp>
#include <stdexcept>

namespace wolfen {
	Engine::Engine()
		: m_player { m_map }, m_raycaster(m_player, m_map, RaycasterType::TEXTURIZED) {
		const sf::View view { sf::FloatRect { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT } };
		const sf::VideoMode video { WINDOW_WIDTH, WINDOW_HEIGHT };

		m_window.create(video, WINDOW_TITLE, sf::Style::Titlebar | sf::Style::Close);
		m_window.setView(view);
		m_window.setMouseCursorVisible(false); // Hide mouse, I don't want to see it.

		// TODO: Make vertical sync optional;
		m_window.setVerticalSyncEnabled(true);

		if (!m_framebuffer.create(SCREEN_WIDTH, SCREEN_HEIGHT)) {
			throw std::runtime_error("Unable to create framebuffer for rendering!");
		}
		m_buffersprite.setTexture(m_framebuffer.getTexture());

		Assets::loadAllTextures("assets");

		m_map.generate();
		m_player.setPosition(m_map.getInitialPos());

		m_running = true;
	}

	void Engine::run() {
		sf::Clock clock {};

		while (m_window.isOpen() && m_running) {
			auto dt = clock.restart().asSeconds();

			processEvents();

			if (m_window.hasFocus()) {
				update(dt);
			}

			draw();
		}

		m_window.close();
	}

	void Engine::processEvents() {
		sf::Event e;

		while (m_window.pollEvent(e)) {
			if (e.type == sf::Event::Closed) {
				m_running = false;
			}

			// If Escape key is pressed, just exit.
			if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Escape) {
				m_running = false;
			}

			// Switch raycaster type.
			if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::R) {
				if (m_raycaster.getRaycasterType() == RaycasterType::NO_TEXTURES) {
					m_raycaster.setRaycasterType(RaycasterType::TEXTURIZED);
				} else {
					m_raycaster.setRaycasterType(RaycasterType::NO_TEXTURES);
				}
			}
		}
	}

	void Engine::update(float dt) {
		auto mouse_pos { sf::Mouse::getPosition(m_window) };
		sf::Mouse::setPosition({ WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 }, m_window);

		m_player.update(dt, mouse_pos);

		m_raycaster.update();
	}

	void Engine::draw() {
		m_framebuffer.clear();
		// Draw the raycaster to a framebuffer.
		// I could draw it directly to the window, but... I don't want.
		m_framebuffer.draw(m_raycaster);
		m_framebuffer.display();

		m_window.clear();
		m_window.draw(m_buffersprite);
		m_window.display();
	}
} // namespace wolfen
