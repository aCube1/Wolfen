#include "core/Engine.hpp"

#include <cstdlib>
#include <exception>
#include <iostream>

int main() {
	try {
		auto engine { wolfen::Engine() };
		engine.run();
	} catch (const std::exception& e) {
		std::cerr << "ERROR: " << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
