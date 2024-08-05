cmake_minimum_required(VERSION 3.28)
project(zGr)

include_directories(${PROJECT_SOURCE_DIR}/thirdParty/include)
link_directories(${PROJECT_SOURCE_DIR}/thirdParty/lib)

find_package(Vulkan REQUIRED)

set(CMAKE_CXX_STANDARD 23)

add_executable(zGr main.cpp)

target_link_libraries(${PROJECT_NAME} Vulkan::Vulkan -lglfw3)