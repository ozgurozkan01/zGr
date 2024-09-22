cmake_minimum_required(VERSION 3.28)
project(zGr)

set(CMAKE_CXX_STANDARD 17)

add_executable(
        zGr
        main.cpp
        # IMGUI 3RD PARTY
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
        # FILE DIALOG 3RD PARTY
        3rdParty/imgui_file_dialog/dirent/dirent.h
        3rdParty/imgui_file_dialog/file_dialog/ImGuiFileDialog.cpp
        3rdParty/imgui_file_dialog/file_dialog/ImGuiFileDialog.h
        3rdParty/imgui_file_dialog/file_dialog/ImGuiFileDialogConfig.h
        3rdParty/imgui_file_dialog/stb/stb_image.h
        3rdParty/imgui_file_dialog/stb/stb_image.c
)

target_link_libraries(${PROJECT_NAME} PRIVATE opengl32 glfw3)