cmake_minimum_required(VERSION 3.0)

project(Malpo_pisacz)
add_compile_options(/utf-8)
set(CMAKE_CXX_STANDARD 20)

include(FetchContent)


FetchContent_Declare(
        SFML_
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG        3.0.0

)

FetchContent_MakeAvailable(SFML_)

FetchContent_Declare(
        fmt_
        GIT_REPOSITORY https://github.com/fmtlib/fmt.git
        GIT_TAG        10.2.1
        
)

FetchContent_MakeAvailable(fmt_)

add_executable(Mapo_pisacz main.cpp
        Game.cpp
        Game.h
        Cofig.cpp
        Cofig.h
        FontLoad.cpp
        FontLoad.h
        WordLoad.cpp
        WordLoad.h
        PointSystem.cpp
        PointSystem.h
)

target_link_libraries(Mapo_pisacz PRIVATE
        SFML::System
        SFML::Window
        SFML::Graphics
        fmt::fmt
)
file(COPY ${CMAKE_SOURCE_DIR}/Assets DESTINATION ${CMAKE_BINARY_DIR}/)