#include "core/Engine.hpp"

#include <cstdlib>
#include <exception>
#include <iostream>
#include <loguru.hpp>

int main(int argc, char *argv[]) {
	try {
		// I don't like this logging library, but I'm too lazy to change it.
		loguru::init(argc, argv);

		auto engine { wolfen::Engine() };
		engine.run();
	} catch (const std::exception& e) {
		LOG_F(FATAL, "%s", e.what());

		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
