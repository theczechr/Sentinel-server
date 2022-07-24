cmake_minimum_required(VERSION 3.19 FATAL_ERROR)

set(VCPKG_TARGET_TRIPLET "x64-windows" CACHE STRING "" FORCE)

project(KRapp-server
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++20 /W4 /O2" CACHE STRING "" FORCE)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/KRapp-server/src)

include_directories(
    ${SRC_DIR}/Account
    ${SRC_DIR}/Core
    ${SRC_DIR}/Controllers
    ${SRC_DIR}/Storage
    ${SRC_DIR}/Storage/Tables
    ${SRC_DIR}/Utils
)

file(GLOB EXEC
   ${SRC_DIR}/Account/*.cpp
   ${SRC_DIR}/Core/*.cpp
   ${SRC_DIR}/Controllers/*.cpp
   ${SRC_DIR}/*.cpp
   ${SRC_DIR}/Storage/*.cpp
   ${SRC_DIR}/Storage/Tables/*.cpp
   ${SRC_DIR}/Utils/*.cpp
)

find_package(Drogon CONFIG REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(SQLiteCpp CONFIG REQUIRED)
find_package(Boost REQUIRED)

list(INSERT CMAKE_MODULE_PATH 0 ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
find_package(Botan REQUIRED)

add_executable(${PROJECT_NAME} ${EXEC})

target_link_libraries(${PROJECT_NAME} PRIVATE
    Drogon::Drogon
    OpenSSL::SSL
    OpenSSL::Crypto
    SQLiteCpp
    ${Boost_INCLUDE_DIRS}
    Botan::Botan
)