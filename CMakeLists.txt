cmake_minimum_required(VERSION 3.16)
project(TheOnlyRuleIsBattle)
set(CMAKE_C_STANDARD 11)

set(CMAKE_C_FLAGS "-D_DEFAULT_SOURCE -D_XOPEN_SOURCE=600 -lncurses -ltinfo ${CMAKE_C_FLAGS}")

include_directories(${PROJECT_SOURCE_DIR}/include)
file(GLOB_RECURSE SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.c)
add_executable(torib ${SRC_FILES})
target_link_libraries(torib raylib)
