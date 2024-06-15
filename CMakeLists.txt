cmake_minimum_required(VERSION 3.15)
project(CrowProject)

set(INCLUDE_PATHS include/boost_1_85_0/boost include/boost_1_85_0 include/Crow-1.2.0/include)

include_directories(include)
file(GLOB SOURCES "src/*.cpp")

add_executable(CrowProject ${SOURCES})

target_include_directories(CrowProject PUBLIC ${INCLUDE_PATHS})
