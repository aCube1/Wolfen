#include "core/Engine.hpp"

#include <cstdlib>
#include <exception>
#include <iostream>
#include <loguru.hpp>

int main(int argc, char *argv[]) {
	try {
		loguru::init(argc, argv);

		auto engine { wolfen::Engine() };
		engine.run();
	} catch (const std::exception& e) {
		LOG_F(FATAL, "%s", e.what());

		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
