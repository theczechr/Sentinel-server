cmake_minimum_required(VERSION 3.21)

project(Sentinel
        LANGUAGES CXX)
		
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
    add_compile_options("/W3" "/O2" "/std:c++20")
elseif()
    add_compile_options("-Wall" "-Wextra" "-Werror" "-O3" "-std=c++20")
endif()

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/sqlitecpp)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/drogon)

include_directories(
    ${SRC_DIR}/Account
    ${SRC_DIR}/Storage
    ${SRC_DIR}/Utils
    ${SRC_DIR}/WebSocketControllers
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/boost-headers
)

file(GLOB EXEC # We shouldn't use GLOB
   ${SRC_DIR}/Account/*.cpp
   ${SRC_DIR}/Storage/*.cpp
   ${SRC_DIR}/Utils/*.cpp
   ${SRC_DIR}/WebSocketControllers/*.cpp
   ${SRC_DIR}/*.cpp
)

add_executable(${PROJECT_NAME} ${EXEC})
target_link_libraries(${PROJECT_NAME} PRIVATE
    SQLiteCpp
    drogon
)
