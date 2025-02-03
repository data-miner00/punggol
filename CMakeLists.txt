cmake_minimum_required(VERSION 3.10)

project(
  punggol

  VERSION 0.1.0.0
  DESCRIPTION "Trying to Pong"
  LANGUAGES CXX
)

set(AUTHOR_NAME shaun)

# set(CMAKE_CXX_STANDARD 11)
# set(CMAKE_CXX_STANDARD_REQUIRED True)
# set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS True)

file(GLOB SOURCES "*.cpp")

add_executable(
  ${PROJECT_NAME}
  ${SOURCES}
)

set(RAYLIB_PATH "D:/src/raylib/src")
set(RAYGUI_PATH "D:/src/raygui/src")

target_include_directories(
  ${PROJECT_NAME}
  PUBLIC "include"
  PUBLIC ${RAYLIB_PATH}
  PUBLIC ${RAYGUI_PATH}
)

target_link_directories(
  ${PROJECT_NAME}
  PUBLIC ${RAYLIB_PATH}
)

target_link_libraries(
  ${PROJECT_NAME}
  PUBLIC raylib opengl32 gdi32 winmm
)

