
cmake_minimum_required(VERSION 3.16)

project(Minesweeper VERSION 1.0)

include(FetchContent)

set(BUILD_SHARED_LIBS OFF)
FetchContent_Declare(
	SFML
	GIT_REPOSITORY https://github.com/SFML/SFML.git
	GIT_TAG 2.5.1
)
FetchContent_MakeAvailable(SFML)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED true)

include_directories(include)

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

add_executable(
	Minesweeper
	src/main.cpp
	src/Board.cpp
	src/Random.cpp
	src/TextureManager.cpp
	src/Tile.cpp
	include/Board.h
	include/Random.h
	include/TextureManager.h
	include/Tile.h
)

target_link_libraries(
	Minesweeper
	sfml-graphics
)

install(TARGETS Minesweeper DESTINATION bin)