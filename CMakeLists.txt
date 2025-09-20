cmake_minimum_required(VERSION 3.16)
project(cpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/Shape.cpp
    src/simulation.cpp
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_SOURCE_DIR}/include
)

link_directories(${CMAKE_SOURCE_DIR}/lib)

target_link_libraries(${PROJECT_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/lib/libglfw3.a"
    opengl32
    gdi32
    user32
    shell32
)
