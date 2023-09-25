#Cmake version
cmake_minimum_required(VERSION 3.21)

set(NAME PLOP)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(r-type)


# Server Sources
set(MAIN
        Sources/Main.cpp)
set(SRC ${SRC}
        Sources/Network/Network.cpp
        Sources/Network/Network.hpp
        Sources/Graphics/Graphics.cpp
        Sources/Graphics/Graphics.hpp
        Sources/Network/Client.cpp
        Sources/Network/Client.hpp
)
add_executable(${NAME} ${MAIN} ${SRC})

find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)

target_link_libraries(${NAME} sfml-graphics sfml-window)
