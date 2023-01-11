# Autore: Alessandro Rotondo (2032447)

cmake_minimum_required(VERSION 2.84)
set(CMAKE_CXX_STANDARD 11)
project(BattagliaNavale)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS_RELEASE "-O2")

include_directories(include)

add_library(${PROJECT_NAME}
    src/FilesIO.cpp
    src/Pos.cpp
    src/AttackField.cpp
    src/DefenceField.cpp
    src/Player.cpp
    src/Ship.cpp
    src/BattleShip.cpp
    src/HealShip.cpp
    src/Submarine.cpp
    src/DummyPlayer.cpp
    src/Computer.cpp)

add_executable(battaglia_navale src/Main.cpp)
add_executable(replay src/Replay.cpp)

target_link_libraries(battaglia_navale ${PROJECT_NAME})
target_link_libraries(replay ${PROJECT_NAME})