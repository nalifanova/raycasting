cmake_minimum_required(VERSION 3.28)
project(raycasting)

# require C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# ensure -std=c++XX instead of -std=g++xx
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wno-reorder")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
#option(SFML_BUILD_AUDIO "Build audio" OFF)
FetchContent_MakeAvailable(SFML)

include_directories(include)

add_executable(raycasting
    main.cpp
    include/Vec2.hpp
    include/RayCasting.hpp
    src/RayCasting.cpp
    include/Physics.hpp
    include/Physics.hpp
    src/Physics.cpp
    include/Data.hpp
    src/Vec2.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

# copy assets to binary directory
file(
    COPY ${CMAKE_SOURCE_DIR}/assets/fonts/tech.ttf
    DESTINATION ${CMAKE_BINARY_DIR}/bin/assets/fonts
)