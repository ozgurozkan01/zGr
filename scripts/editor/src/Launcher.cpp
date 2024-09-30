//
// Created by ozgur on 9/15/2024.
//

#include "../include/Launcher.h"
#include "../../../3rdParty/imgui/imgui_impl_opengl3.h"
#include "../../../3rdParty/stb/stb_image.h"
#include "../../../3rdParty/fileDialog/ImGuiFileDialog.h"
#include <regex>

namespace zgr::editor
{
    Launcher::Launcher(int x_res, int y_res, const char* w_name) :
            x_resolution(x_res),
            y_resolution(y_res),
            window_name(w_name),
            file_browser("File Browser"),
            project_name("NewProject"),
            is_browsing(false),
            is_wrong_name(false),
            is_wrong_path(false),
            is_path_exist(false),
            is_project_created(false),
            is_existed_project_open(false),
            is_launcher_closed(false)
    {
        init();
    }

    Launcher::~Launcher()
    {
        destroy();
    }

    void Launcher::destroy()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    void Launcher::init()
    {
        if (!glfwInit())
        {
            std::cerr << "ERROR : GLFW LIB could not initialized!!!\n";
            exit(-1);
        }

        window = glfwCreateWindow(x_resolution, y_resolution, window_name, nullptr, nullptr);
        // this operation sets the assigned window as the window where all calls and operations will be performed at that time
        glfwMakeContextCurrent(window);

        ImGui::CreateContext();
        // Connect imgui and glfw
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        // Determien the OpenGLSL version / i.e. GLSL 3.30
        ImGui_ImplOpenGL3_Init("#version 330");

        std::string parentPath = std::filesystem::current_path().parent_path().string();
        strncpy(project_path, parentPath.c_str(), sizeof(project_path) - 1);

        templates.emplace_back(project_type::empty,        "Empty Project",        load_texture("C:/Users/ozgur/GitHub/zGr/templates/EmptyTemplate/icon.png"));
        templates.emplace_back(project_type::first_person, "First Person Project", load_texture("C:/Users/ozgur/GitHub/zGr/templates/FirstPersonTemplate/icon.png"));
        templates.emplace_back(project_type::third_person, "Third Person Project", load_texture("C:/Users/ozgur/GitHub/zGr/templates/ThirdPersonTemplate/icon.jpeg"));
    }

    void Launcher::render()
    {
        glfwPollEvents();
        // Resets and prepares the OpenGL3 related functions of ImGui.
        // This does all the background preparation necessary for ImGui to be able to draw with OpenGL3.
        ImGui_ImplOpenGL3_NewFrame();
        //  Resets and prepares the GLFW related functions of ImGui.
        //  This allows GLFW to correctly handle user inputs, window events and other related information.
        ImGui_ImplGlfw_NewFrame();
        // Allows ImGui to create a new frame.
        ImGui::NewFrame();

        // Match the imgui and window
        int framebufferWidth, framebufferHeight;
        glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);
        ImGui::SetNextWindowSize(ImVec2(static_cast<float>(framebufferWidth), static_cast<float>(framebufferHeight)));
        ImGui::SetNextWindowPos(ImVec2(0, 0));

        // ImGui::ShowDemoWindow();
        render_launcher_default_editor();

        switch (mode)
        {
            case launcher_mode::new_project:
                render_new_project_editor(); break;
            case launcher_mode::open_project:
                render_open_project_editor(); break;
        }

        ImGui::SetCursorScreenPos(ImVec2(x_resolution - 150, y_resolution - 75));
        if (ImGui::Button("Exit", ImVec2(100, 30)))
        {
            is_launcher_closed = true;
        }

        // Close the window
        ImGui::End();

        ImGui::Render();
        // It draws the GUI data generated by ImGui on the screen using OpenGL.
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        // Displays the GUI data generated by ImGui on the screen
        glfwSwapBuffers(window);
    }

    void Launcher::render_launcher_default_editor()
    {
        ImGui::Begin("Engine Launcher");

        ImGui::SetCursorScreenPos(ImVec2(x_resolution / 2 - 225, 50));
        if (ImGui::Button("Open Project", ImVec2(200, 40)))
        {
            mode = launcher_mode::open_project;
        }

        ImGui::SetCursorScreenPos(ImVec2(x_resolution / 2 + 25, 50));
        if (ImGui::Button("New Project", ImVec2(200, 40)))
        {
            mode = launcher_mode::new_project;
        }

        ImGui::Separator();

        ImGui::SetCursorScreenPos(ImVec2(x_resolution - 400, y_resolution - 75));
        if (ImGui::Button("Browse", ImVec2(100, 30)))
        {
            is_browsing = true;
        }

        if (is_browsing)
        {
            render_file_browser();
        }
    }

    void Launcher::render_new_project_editor()
    {
        ImGui::SetCursorScreenPos(ImVec2(75, 150));
        ImGui::BeginChild("ProjectTypes", ImVec2(250, 400), true);

        for (int i = 0; i < IM_ARRAYSIZE(project_types); i++)
        {
            if (ImGui::Selectable(templates[i].name().c_str(), selected_project_type == i))
            {
                selected_project_type = i;
            }
        }

        ImGui::EndChild();

        ImGui::SameLine();

        ImGui::SetCursorScreenPos(ImVec2(335, 150));
        ImGui::BeginChild("ProjectPreview", ImVec2(400, 400), true);
        ImGui::Image((void*)(intptr_t)templates[selected_project_type].image_id(), ImVec2(375, 375));
        ImGui::EndChild();

        ImGui::SetCursorScreenPos(ImVec2(100, y_resolution - 140));
        ImGui::Text("File Name:");
        ImGui::SameLine();
        ImGui::InputText("##FileName", project_name, IM_ARRAYSIZE(project_name), ImGuiInputTextFlags_CharsNoBlank);

        ImGui::SetCursorScreenPos(ImVec2(100, y_resolution - 110));
        ImGui::Text("File Path:");
        ImGui::SameLine();
        ImGui::InputText("##FilePath", project_path, IM_ARRAYSIZE(project_path), ImGuiInputTextFlags_CharsNoBlank);

        ImGui::SetCursorScreenPos(ImVec2(x_resolution - 275, y_resolution - 75));
        if (ImGui::Button("Create", ImVec2(100, 30)) && can_create_project())
        {
            std::filesystem::create_directory(full_path);
            is_project_created = true;
        }

        if (is_path_exist)
        {
            ImGui::SetCursorScreenPos(ImVec2(50, y_resolution - 25));
            ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 0, 0, 255));
            ImGui::Text("WARNING : This directory already exists!!");
            ImGui::PopStyleColor();
        }
        if (is_wrong_path)
        {
            ImGui::SetCursorScreenPos(ImVec2(50, y_resolution - 50));
            ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 0, 0, 255));
            ImGui::Text("WARNING : Directory is not valid!!");
            ImGui::PopStyleColor();
        }
        if (is_wrong_name)
        {
            ImGui::SetCursorScreenPos(ImVec2(50, y_resolution - 75));
            ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 0, 0, 255));
            ImGui::Text("WARNING : Invalid character(s) is used in project name");
            ImGui::PopStyleColor();
        }
    }

    void Launcher::render_open_project_editor()
    {
        ImGui::SetCursorScreenPos(ImVec2(75, 150));
        ImGui::BeginChild("Exist Projects", ImVec2(250, 400), true);

        if (existed_projects.empty())
        {
            ImGui::Text("No Exist Project");
        }
        else
        {
            for (int i = 0; i < existed_projects.size(); i++)
            {
                if (ImGui::Selectable(existed_projects[i].c_str(), selected_exist_project == i))
                {
                    selected_exist_project = i;
                }
            }
        }

        ImGui::EndChild();

        ImGui::SetCursorScreenPos(ImVec2(x_resolution - 275, y_resolution - 75));
        if (ImGui::Button("Open", ImVec2(100, 30)))
        {
            is_existed_project_open = true;
        }
    }

    void Launcher::render_file_browser()
    {
        IGFD::FileDialogConfig config;
        config.path = std::filesystem::current_path().parent_path().string();

        ImGuiFileDialog::Instance()->OpenDialog(file_browser, "Choose Folder", nullptr, config);

        if (ImGuiFileDialog::Instance()->Display(file_browser))
        {
            if (ImGuiFileDialog::Instance()->IsOk())
            {
                selected_folder_path = ImGuiFileDialog::Instance()->GetCurrentPath();
                strncpy(project_path, selected_folder_path.string().c_str(), sizeof(project_path) - 1);

                is_browsing = false;
            }
            ImGuiFileDialog::Instance()->Close();
        }
    }

    GLuint Launcher::load_texture(const std::string& path)
    {
        GLuint texture_id;
        glGenTextures(1, &texture_id);
        glBindTexture(GL_TEXTURE_2D, texture_id);

        int width, height, nrChannels;
        unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        }

        stbi_image_free(data);
        return texture_id;
    }

    bool Launcher::window_should_close()      { return glfwWindowShouldClose(window) || is_project_created || is_existed_project_open || is_launcher_closed; }
    bool Launcher::is_project_name_validate() { return std::regex_match(project_name, std::regex("^[a-zA-Z0-9_]+$")); }
    bool Launcher::is_project_path_validate() { return std::filesystem::is_directory(project_path); }
    bool Launcher::is_project_path_exist()    { return std::filesystem::exists(full_path = std::string(project_path) + "\\" + project_name); }
    bool Launcher::can_create_project()
    {
        if (!is_project_path_validate()) { is_wrong_path = true; }
        if (!is_project_name_validate()) { is_wrong_name = true; }
        if (is_project_path_exist())     { is_path_exist = true; }

        return !is_wrong_path && !is_wrong_name && !is_path_exist;
    }
}
