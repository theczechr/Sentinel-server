cmake_minimum_required(VERSION 3.20 FATAL_ERROR)

project(KRapp
        LANGUAGES CXX
)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

file(GLOB SRC
   ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

find_package(nlohmann_json CONFIG REQUIRED)

add_executable (${PROJECT_NAME} ${SRC})

target_link_libraries(${PROJECT_NAME} PRIVATE
    nlohmann_json
    nlohmann_json::nlohmann_json
    libssl
    libcrypto
)