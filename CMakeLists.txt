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
    ${CMAKE_CURRENT_SOURCE_DIR}/database
    ${CMAKE_CURRENT_SOURCE_DIR}/main
    ${CMAKE_CURRENT_SOURCE_DIR}/security
    ${CMAKE_CURRENT_SOURCE_DIR}/utils
    ${CMAKE_CURRENT_SOURCE_DIR}/controllers
)

file(GLOB SRC
   ${CMAKE_CURRENT_SOURCE_DIR}/account/*.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/database/*.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/main/*.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/security/*.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/utils/*.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/controllers/*.cpp
)

find_package(Drogon CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
# The package nlohmann-json can be configured to not provide implicit conversions via a custom triplet file:
# set(nlohmann-json_IMPLICIT_CONVERSIONS OFF)
# For more information, see the docs here: https://json.nlohmann.me/features/macros/#json_use_implicit_conversions
find_package(OpenSSL REQUIRED)
find_package(SQLiteCpp CONFIG REQUIRED)

add_executable(${PROJECT_NAME} ${SRC})

target_link_libraries(${PROJECT_NAME} PRIVATE
    Drogon::Drogon
    nlohmann_json::nlohmann_json
    OpenSSL::SSL
    OpenSSL::Crypto
    SQLiteCpp
)