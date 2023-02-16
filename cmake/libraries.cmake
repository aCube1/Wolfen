include_guard()

set(LIBS_DIR ${PROJECT_SOURCE_DIR}/ext)

function(link_default_libraries target)
	find_package(SDL2 2.24.2 REQUIRED)

	target_link_libraries(
		${target}
		SDL2::SDL2
	)
endfunction()
