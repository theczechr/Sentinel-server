# Do powershellu dej: winget install CMake a mas latest CMake
cmake_minimum_required(VERSION 3.21)

project(Sentinel # Okay tady jsem dal uz sentinel protoze z nejakeho duvodu mi neslo same name jako dir (idk proc, prosim neptej se me, byl jsem unaveny)
        LANGUAGES CXX)
		
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(default_build_type "Release")
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
endif()

if(MSVC)
    add_compile_options("/W4" "$<$<CONFIG:RELEASE>:/O2>")
elseif()
    add_compile_options("-Wall" "-Wextra" "-Werror" "$<$<CONFIG:RELEASE>:-O3>" "-stdlib=libc++")
endif()

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/KRapp-server/src)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/KRapp-server/vendor/drogon)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/KRapp-server/vendor/sqlitecpp)

include_directories(
    ${SRC_DIR}/Account
    ${SRC_DIR}/Storage
    ${SRC_DIR}/Utils
    ${SRC_DIR}/WebSocketControllers
    ${CMAKE_CURRENT_SOURCE_DIR}/KRapp-server/vendor/boost-headers
)

file(GLOB EXEC # Nemeli bychom pouzivat GLOB x_x
   ${SRC_DIR}/Account/*.cpp
   ${SRC_DIR}/Storage/*.cpp
   ${SRC_DIR}/Utils/*.cpp
   ${SRC_DIR}/WebSocketControllers/*.cpp
   ${SRC_DIR}/*.cpp
)

find_package(Git QUIET)

# Update git submodules
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init --recursive failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()

add_executable(${PROJECT_NAME} ${EXEC})

target_link_libraries(${PROJECT_NAME} PRIVATE
    drogon
    SQLiteCpp
)
