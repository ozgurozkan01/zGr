//
// Created by ozgur on 9/15/2024.
//

#ifndef ZGR_LAUNCHER_H
#define ZGR_LAUNCHER_H

#include <filesystem>
#include <iostream>
#include <cstdint>
#include <utility>
#include <vector>
#include <map>
// THIRD PARTY
#include "../../../3rdParty/imgui/imgui_impl_glfw.h"
// CUSTOM LIBS
#include "NewProjectGenerator.h"

namespace zgr::editor
{
    enum class launcher_mode : uint8_t
    {
        new_project,
        open_project
    };

    class Launcher {
    public:
        explicit Launcher(int x_res = 0, int y_res = 0, const char* w_name = "");
        ~Launcher();

        void init();
        void destroy();
        void render();
        bool window_should_close();

        // Launcher Editor Base
        void render_launcher_default_editor();
        GLuint load_texture(const std::string& path);
        // Create New Project
        void render_new_project_editor();
        bool is_project_path_validate();
        bool is_project_path_exist();
        bool is_project_name_validate();
        bool can_create_project();
        // Open Exist Project
        void render_open_project_editor();
        void render_file_browser();

        void close();
    private:
        launcher_mode mode = launcher_mode::new_project;

        std::filesystem::path selected_folder_path;

        const int x_resolution;
        const int y_resolution;
        const char* window_name;

        const std::string file_browser;
        char project_name[25];
        char project_path[50];
        std::string full_path; // project_path + project_name
        project_type project_types[3] = {project_type::empty, project_type::first_person, project_type::third_person};
        std::vector<std::string> existed_projects;
        std::vector<ProjectTemplate> templates;

        int selected_exist_project = 0;
        int selected_project_type = 0;

        bool is_browsing;
        bool is_wrong_path;
        bool is_wrong_name;
        bool is_path_exist;
        // LAUNCHER EDITOR LIFE CONTROL
        bool is_project_created;
        bool is_existed_project_open;
        bool is_launcher_closed;

        GLFWwindow* window;
    };
}

#endif //ZGR_LAUNCHER_H
