cmake_minimum_required(VERSION 3.28)
project(zGr)

#include_directories(${PROJECT_SOURCE_DIR}/thirdParty/include)
#link_directories(${PROJECT_SOURCE_DIR}/thirdParty/lib)

find_package(Vulkan REQUIRED)

set(CMAKE_CXX_STANDARD 23)

add_executable(zGr engine/src/main.cpp
        engine/src/screen.cpp
        engine/include/screen.h
        engine/src/engine.cpp
        engine/include/engine.h
        engine/src/graphic_pipeline.cpp
        engine/include/graphic_pipeline.h
)

target_link_libraries(${PROJECT_NAME} Vulkan::Vulkan -lglfw3)