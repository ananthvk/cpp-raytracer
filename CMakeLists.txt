cmake_minimum_required(VERSION 3.10)
project(raytracer)
set(CMAKE_CXX_STANDARD 14)
include_directories(
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/src
)
add_executable(raytracer src/main.cpp)
find_package(Eigen3 REQUIRED)
if(Eigen3_FOUND)
    message("Eigen3 found")
    target_include_directories(raytracer PUBLIC ${Eigen3_INCLUDE_DIRS})
    target_link_libraries(raytracer PUBLIC ${Eigen3_LIBRARIES})
elseif(NOT Eigen3_FOUND)
    error("Eigen3 not found, Please install it from https://eigen.tuxfamily.org")
endif()
