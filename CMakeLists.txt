cmake_minimum_required(VERSION 3.28)
project(zGr)

set(CMAKE_CXX_STANDARD 17)

set(IMGUI_DIR 3rdParty/imgui)
set(CEREAL_ARCHIVE_DIR 3rdParty/cereal/archives)
set(FILE_DIALOG_DIR 3rdParty/fileDialog)
set(STB_DIR 3rdParty/stb)
set(SCRIPTS_DIR scripts)

set(IMGUI_FILES
        ${IMGUI_DIR}/imgui.cpp
        ${IMGUI_DIR}/imgui_demo.cpp
        ${IMGUI_DIR}/imgui_draw.cpp
        ${IMGUI_DIR}/imgui_tables.cpp
        ${IMGUI_DIR}/imgui_widgets.cpp
        ${IMGUI_DIR}/imgui_impl_glfw.cpp
        ${IMGUI_DIR}/imgui_impl_opengl3.cpp
        ${IMGUI_DIR}/imgui.h
        ${IMGUI_DIR}/imconfig.h
        ${IMGUI_DIR}/imgui_internal.h
        ${IMGUI_DIR}/imstb_textedit.h
        ${IMGUI_DIR}/imstb_rectpack.h
        ${IMGUI_DIR}/imstb_truetype.h
        ${IMGUI_DIR}/imgui_impl_glfw.h
        ${IMGUI_DIR}/imgui_impl_opengl3.h
        ${IMGUI_DIR}/imgui_impl_opengl3_loader.h
)

set(FILE_DIALOG_FILES
        ${FILE_DIALOG_DIR}/ImGuiFileDialog.cpp
        ${FILE_DIALOG_DIR}/ImGuiFileDialog.h
        ${FILE_DIALOG_DIR}/ImGuiFileDialogConfig.h
)

set(STB_FILES
        ${STB_DIR}/stb_image.c
        ${STB_DIR}/stb_image.h
        ${STB_DIR}/stb_image_resize2.h
        scripts/editor/src/NewProjectGenerator.cpp
        scripts/editor/include/NewProjectGenerator.h
        scripts/editor/include/NewProjectGenerator.h
)

find_package(SDL2 CONFIG REQUIRED)

add_executable(
        zGr
        main.cpp
        # IMGUI 3RD PARTY
        ${IMGUI_FILES}
        ${FILE_DIALOG_FILES}
        ${STB_FILES}
        # PROJECT CUSTOM CLASSES
        scripts/serialize/include/Serialize.h
        scripts/serialize/src/Serialize.cpp
        scripts/editor/src/Launcher.cpp
        scripts/editor/include/Launcher.h
        scripts/ZGR.cpp
        scripts/ZGR.h
        scripts/editor/src/ProjectTemplate.cpp
        scripts/editor/include/ProjectTemplate.h
)

target_link_libraries(${PROJECT_NAME} PRIVATE opengl32 glfw3 -lmingw32 -lSDL2main -lSDL2 -mwindows)