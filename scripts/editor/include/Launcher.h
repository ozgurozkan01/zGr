//
// Created by ozgur on 9/15/2024.
//

#ifndef ZGR_LAUNCHER_H
#define ZGR_LAUNCHER_H

#include "../../../3rdParty/imgui/imgui_impl_glfw.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdint>
#include <vector>
#include <map>

namespace zgr::editor
{
    enum class launcher_mode : uint8_t
    {
        new_project,
        open_project
    };

    enum class project_type : uint8_t
    {
        empty,
        third_person,
        first_person
    };

    class Launcher {
    public:
        explicit Launcher(int x_res = 0, int y_res = 0, const char* w_name = "");
        ~Launcher();

        void init();
        void close();
        void render();
        bool window_should_close();

        // Launcher Editor Base
        void render_launch_default();
        GLuint load_texture(const std::string& path);
        [[nodiscard]] std::string project_type_enum_to_string(const project_type& type) const;
        // Create New Project
        void render_new_project();
        // Open Exist Project
        void render_open_project();
        void render_file_browser();

    private:
        launcher_mode mode = launcher_mode::new_project;

        const int x_resolution;
        const int y_resolution;
        const char* window_name;

        char fileName[128] = "New Project";
        char filePath[256];
        project_type project_types[3] = {project_type::empty, project_type::first_person, project_type::third_person};
        std::vector<std::string> existed_projects;
        std::map<project_type, GLuint> image_ids;

        int selected_exist_project = 0;
        int selected_project_type = 0;

        bool isBrowsing;

        GLFWwindow* window;
    };
}

#endif //ZGR_LAUNCHER_H
