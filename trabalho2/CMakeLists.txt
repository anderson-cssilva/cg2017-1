cmake_minimum_required(VERSION 3.6)
project(trabalho2)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES SpaceInvader.cpp
        includes/Shooter.h
        src/Enemy.cpp includes/Enemy.h
        src/Shoot.cpp includes/Shoot.h
        src/SquareEnemy.cpp includes/SquareEnemy.h
        src/CircleEnemy.cpp includes/CircleEnemy.h
        src/TriangleEnemy.cpp includes/TriangleEnemy.h
        src/Plane.cpp includes/Plane.h includes/Shooter.h)

add_executable(trabalho2 ${SOURCE_FILES})

target_link_libraries(trabalho2 libopengl32.a libglu32.a libglut32.a)