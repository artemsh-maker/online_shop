cmake_minimum_required(VERSION 3.15)
project(CrowProject)

# Найти пакет Boost, указывая на необходимые компоненты (log и log_setup)
find_package(Boost REQUIRED COMPONENTS log log_setup)

set(INCLUDE_PATHS
    include/Crow-1.2.0/include
    include
)

# include_directories(include)
include_directories(${INCLUDE_PATHS} ${Boost_INCLUDE_DIRS})
file(GLOB SOURCES "src/*.cpp")

add_executable(CrowProject ${SOURCES})

# target_include_directories(CrowProject PUBLIC ${INCLUDE_PATHS})

# Связать исполняемый файл с библиотеками Boost
target_link_libraries(CrowProject ${Boost_LIBRARIES})