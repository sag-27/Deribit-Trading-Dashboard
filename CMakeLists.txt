include("C:/vcpkg/scripts/buildsystems/vcpkg.cmake")
cmake_minimum_required(VERSION 3.10)
project(DeribitAPI)

set(CMAKE_CXX_STANDARD 17)

find_package(CURL REQUIRED)
find_package(websocketpp CONFIG REQUIRED)
find_package(Boost REQUIRED)
find_package(JsonCpp REQUIRED)

add_executable(DeribitAPI 
    src/main.cpp
    src/DeribitAPI.cpp
    src/websocketpp.cpp
    src/utils.cpp
)

target_include_directories(DeribitAPI PRIVATE include)

target_link_libraries(DeribitAPI PRIVATE CURL::libcurl)
target_link_libraries(DeribitAPI PRIVATE websocketpp::websocketpp)
target_link_libraries(DeribitAPI PRIVATE JsonCpp::JsonCpp)
target_link_libraries(DeribitAPI PRIVATE Boost::boost)

