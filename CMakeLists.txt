cmake_minimum_required(VERSION 3.5.1)
project(asteroids)

set(CMAKE_CXX_STANDARD 14)

set(SOURCES src/main.cpp src/gutils.cpp src/entity.cpp src/game.cpp
            include/gutils.h include/entity.h include/game.h
            src/target.cpp include/target.h
            src/projectile.cpp include/projectile.h
            src/ship.cpp include/ship.h
            src/hbar.cpp include/hbar.h)

find_package(glfw3 3.1.2 REQUIRED)

include_directories("include/")
add_executable(asteroids ${SOURCES})
target_link_libraries(asteroids pthread GL GLU GLEW glfw)
