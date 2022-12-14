cmake_minimum_required(VERSION 3.21)

project(Sentinel
        LANGUAGES CXX)

if(MSVC)
    add_compile_options("/W3" "/Ox")
elseif()
    add_compile_options("-Wall" "-Wextra" "-Werror" "-O3")
endif()

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/third_party/drogon)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

file(GLOB EXEC
   ${SRC_DIR}/Account/*.cpp
   ${SRC_DIR}/Storage/*.cpp
   ${SRC_DIR}/Utils/*.cpp
   ${SRC_DIR}/WebSocketControllers/*.cpp
   ${SRC_DIR}/*.cpp
)

add_executable(${PROJECT_NAME} ${EXEC})

target_link_libraries(${PROJECT_NAME} PRIVATE
    drogon
)
