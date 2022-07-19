cmake_minimum_required(VERSION 3.19 FATAL_ERROR)

if(CMAKE_HOST_WIN32)
    set(VCPKG_TARGET_TRIPLET "x64-windows" CACHE STRING "" FORCE)
elseif(CMAKE_HOST_UNIX)
    set(CMAKE_TOOLCHAIN_FILE "/home/karlos/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
    set(VCPKG_TARGET_TRIPLET "x64-linux" CACHE STRING "" FORCE)
endif()

project(KRapp-server
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17 /W4 /O2" CACHE STRING "" FORCE)
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -O3" CACHE STRING "" FORCE)
endif()

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/account
    ${CMAKE_CURRENT_SOURCE_DIR}/controllers
    ${CMAKE_CURRENT_SOURCE_DIR}/storage
    ${CMAKE_CURRENT_SOURCE_DIR}/storage/tables
    ${CMAKE_CURRENT_SOURCE_DIR}/utils
)

file(GLOB SRC
   ${CMAKE_CURRENT_SOURCE_DIR}/account/*.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/controllers/*.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/main/*.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/storage/*.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/storage/tables/*.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/utils/*.cpp
)

find_package(Drogon CONFIG REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(SQLiteCpp CONFIG REQUIRED)
find_package(Boost REQUIRED)

find_package(PkgConfig)
pkg_check_modules(BOTAN2 botan-2)

list(INSERT CMAKE_MODULE_PATH 0 ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
find_package(Botan REQUIRED)

add_executable(${PROJECT_NAME} ${SRC})

target_link_libraries(${PROJECT_NAME} PRIVATE
    Drogon::Drogon
    OpenSSL::SSL
    OpenSSL::Crypto
    SQLiteCpp
    ${Boost_INCLUDE_DIRS}
)

if(BOTAN2_FOUND) 
    if (WIN32)
        target_link_libraries(${PROJECT_NAME} PRIVATE
            Botan::Botan
        )
    else()

      target_link_libraries(${PROJECT_NAME} PRIVATE
        ${BOTAN2_LIBRARIES}
        ${BOTAN2_LDFLAGS}
      )

      target_include_directories(${PROJECT_NAME} PRIVATE
            ${BOTAN2_INCLUDE_DIRS}
        )
      target_compile_options(${PROJECT_NAME} PRIVATE
            ${BOTAN2_CFLAGS_OTHER}
      )
  endif()
endif()