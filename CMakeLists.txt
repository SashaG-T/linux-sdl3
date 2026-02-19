cmake_minimum_required(VERSION 3.16)
project(game)
include(FetchContent)

# set the output directory for built objects.
# This makes sure that the dynamic library goes into the build directory automatically.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

set(CMAKE_BUILD_TYPE Debug)

# This assumes the SDL source is available in vendored/SDL
FetchContent_Declare(
	SDL3
	GIT_REPOSITORY 	https://github.com/libsdl-org/SDL.git
	GIT_TAG			main
	GIT_SHALLOW		TRUE
	GIT_PROGRESS	TRUE
)
FetchContent_MakeAvailable(SDL3)
# add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)

# Create your game executable target as usual
add_executable(game main.c unittest.c array.c time.c vector.c transform.c object.c list.c texture.c sprite.c scene.c)

# Link to the actual SDL3 library.
target_link_libraries(game 
	PRIVATE SDL3::SDL3 png z m
)

target_compile_features(game PRIVATE c_std_11)

