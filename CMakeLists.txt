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

# Пути к исходникам
set(MAIN_SOURCES
    src/RobotMath.cc
    src/UI/JointEditorWidget.cc
)
add_executable(Robopro
    src/main.cc
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

# GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Основной исполняемый файл



add_executable(robotmath_test
    tests/robot_math_test.cc
    ${MAIN_SOURCES}

)

target_link_libraries(robotmath_test PRIVATE
    gtest_main
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
)


target_include_directories(robotmath_test PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${GLM_INCLUDE_DIRS}
)

# Регистрируем тесты из robotmath_test для CTest
include(GoogleTest)
gtest_discover_tests(robotmath_test)

# Опционально можно задать отдельный вывод бинарников для тестов:
set_target_properties(robotmath_test PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/tests
)
