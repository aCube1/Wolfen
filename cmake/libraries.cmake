include_guard()

set(LIBS_DIR ${PROJECT_SOURCE_DIR}/ext)

function(link_default_libraries target)
	find_package(SDL2 2.24.2 REQUIRED)

	target_link_libraries(
		${target}
		PRIVATE
			SDL2::SDL2
	)

	target_sources(
		${target}
		PRIVATE
			${LIBS_DIR}/loguru/loguru.cpp
	)
	target_include_directories(
		${target}
		PRIVATE
			${LIBS_DIR}/loguru
	)
endfunction()
