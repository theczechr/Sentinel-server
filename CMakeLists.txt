cmake_minimum_required(VERSION 3.20 FATAL_ERROR)

project(KRapp
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17 /W4 /O2" CACHE STRING "" FORCE)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

file(GLOB SRC
   ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

find_package(nlohmann_json CONFIG REQUIRED)
find_package(OpenSSL REQUIRED)

add_executable(${PROJECT_NAME} ${SRC})

target_link_libraries(${PROJECT_NAME} PRIVATE
    nlohmann_json
    nlohmann_json::nlohmann_json
    OpenSSL::SSL
    OpenSSL::Crypto
)