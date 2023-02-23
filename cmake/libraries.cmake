include_guard()

set(LIBS_DIR ${PROJECT_SOURCE_DIR}/ext)

function(link_default_libraries target)
	find_package(
		SFML 2.5.1
		COMPONENTS
			window graphics audio
		REQUIRED
	)

	target_link_libraries(
		${target}
		PRIVATE
			sfml-window
			sfml-graphics
			sfml-audio
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
