cmake_minimum_required(VERSION 3.21)
project(wolfen CXX)

include(cmake/base.cmake)
include(cmake/warnings.cmake)
include(cmake/libraries.cmake)

add_executable(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)

target_compile_features(
	${PROJECT_NAME}
	PRIVATE
		cxx_std_17
)

target_sources(
	${PROJECT_NAME}
	PRIVATE
		src/main.cpp

		src/core/Engine.cpp
		src/core/Display.cpp

		src/entity/Player.cpp
)

target_include_directories(
	${PROJECT_NAME}
	PRIVATE
		${PROJECT_SOURCE_DIR}/include
)

# target_precompile_headers(
# 	${PROJECT_NAME}
# 	PRIVATE
# )

set_default_warnings(${PROJECT_NAME})

link_default_libraries(${PROJECT_NAME})
