cmake_minimum_required(VERSION 3.28)
project(zGr)

set(CMAKE_CXX_STANDARD 23)

add_executable(
        zGr
        main.cpp
        3rdParty/imgui/imgui.cpp
        3rdParty/imgui/imgui_demo.cpp
        3rdParty/imgui/imgui_draw.cpp
        3rdParty/imgui/imgui_tables.cpp
        3rdParty/imgui/imgui_widgets.cpp
        3rdParty/imgui/imconfig.h
        3rdParty/imgui/imgui_internal.h
        3rdParty/imgui/imstb_textedit.h
        3rdParty/imgui/imstb_rectpack.h
        3rdParty/imgui/imstb_truetype.h
        3rdParty/imgui/imstb_truetype.h
        3rdParty/imgui/imgui_impl_glfw.cpp
        3rdParty/imgui/imgui_impl_glfw.h
        3rdParty/imgui/imgui_impl_opengl3.cpp
        3rdParty/imgui/imgui_impl_opengl3.h
        3rdParty/imgui/imgui_impl_opengl3_loader.h
        scripts/editor/src/Launcher.cpp
        scripts/editor/include/Launcher.h
)

target_link_libraries(${PROJECT_NAME} PRIVATE opengl32 glfw3)