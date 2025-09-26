cmake_minimum_required(VERSION 3.21)

project(Sentinel
        LANGUAGES CXX)

# Set C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
    add_compile_options("/W4" "/Ox")
elseif()
    add_compile_options("-Wall" "-Wextra" "-Wshadow" "-Wconversion" "-Wpedantic" "-Werror" "-O3")
endif()

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

file(GLOB EXEC
   ${SRC_DIR}/*/*.cpp
   ${SRC_DIR}/Storage/*.cpp
   ${SRC_DIR}/Utils/*.cpp
   ${SRC_DIR}/WebSocketControllers/*.cpp
   ${SRC_DIR}/*.cpp
)

find_package(Drogon CONFIG REQUIRED)
find_package(OpenSSL REQUIRED)

add_executable(${PROJECT_NAME} ${EXEC})

target_link_libraries(${PROJECT_NAME} PRIVATE Drogon::Drogon OpenSSL::SSL OpenSSL::Crypto)

# Tests
add_subdirectory(tests)