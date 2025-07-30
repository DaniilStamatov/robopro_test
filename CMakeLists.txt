cmake_minimum_required(VERSION 3.16)

project(Robopro LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

include(FetchContent)
set(MAIN_SOURCES
    src/main.cc
)

add_executable(Robopro
     ${MAIN_SOURCES}
)


target_link_libraries(Robopro PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
)

target_include_directories(Robopro PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${GLM_INCLUDE_DIRS}
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)