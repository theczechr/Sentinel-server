cmake_minimum_required(VERSION 3.19 FATAL_ERROR)

set(VCPKG_TARGET_TRIPLET "x64-windows" CACHE STRING "" FORCE)

project(KRapp-server
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17 /W4 /O2" CACHE STRING "" FORCE)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/account
    ${CMAKE_CURRENT_SOURCE_DIR}/controllers
    ${CMAKE_CURRENT_SOURCE_DIR}/database
    ${CMAKE_CURRENT_SOURCE_DIR}/utils
)

file(GLOB SRC
   ${CMAKE_CURRENT_SOURCE_DIR}/account/*.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/controllers/*.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/database/*.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/main/*.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/utils/*.cpp
)

find_package(Drogon CONFIG REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(SQLiteCpp CONFIG REQUIRED)
find_package(Boost REQUIRED)

add_executable(${PROJECT_NAME} ${SRC})

target_link_libraries(${PROJECT_NAME} PRIVATE
    Drogon::Drogon
    OpenSSL::SSL
    OpenSSL::Crypto
    SQLiteCpp
    ${Boost_INCLUDE_DIRS}
)