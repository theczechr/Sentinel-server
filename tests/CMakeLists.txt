cmake_minimum_required(VERSION 3.21)

add_executable(SentinelTests
    Base64Tests.cpp
    RateLimiterTests.cpp
    E2ETests.cpp
)

target_include_directories(SentinelTests PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(SentinelTests PRIVATE OpenSSL::SSL OpenSSL::Crypto)

