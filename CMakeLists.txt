
project(itertools)

cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall")

include_directories(${PROJECT_SOURCE_DIR}/include)


enable_testing()

file(GLOB test_srcs "test/*" )
foreach(test_src ${test_srcs})
    get_filename_component(test_name ${test_src} NAME_WE)
    add_executable(${test_name} ${test_src})
    add_test(${test_name} ${test_name})
endforeach()
