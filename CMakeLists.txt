cmake_minimum_required (VERSION 3.8)

project ("krapp")
add_executable (PaypalFinal "PaypalFinal.cpp")
find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(PaypalFinal PRIVATE nlohmann_json nlohmann_json::nlohmann_json libssl libcrypto)
