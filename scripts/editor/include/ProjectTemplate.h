//
// Created by ozgur on 9/29/2024.
//

#ifndef ZGR_PROJECTTEMPLATE_H
#define ZGR_PROJECTTEMPLATE_H

#include <cstdint>
#include <iostream>
#include <GLFW/glfw3.h>
#include <vector>

namespace zgr::editor
{
    enum class project_type : uint8_t
    {
        invalid,
        empty,
        third_person,
        first_person
    };

    enum class project_creation_status : uint8_t
    {
        success,
        invalid_path,
        invalid_name,
        path_exist
    };

    class ProjectTemplate {
    public:
        explicit ProjectTemplate(std::string i_path = "Invalid Path", project_type type = project_type::invalid, std::string p_file = "NewProject");

        // GETTERS
        [[nodiscard]] std::string get_project_file_name() const { return project_file_name; }
        [[nodiscard]] std::string get_icon_path() const { return icon_path; }
        [[nodiscard]] std::string get_template_type() const;
        [[nodiscard]] GLuint get_icon_id() const { return icon_id; }
        [[nodiscard]] std::vector<std::string> get_files() const { return file_list; }

        // SETTERS
        void set_project_file_name(const std::string& ext) { project_file_name = ext; }
        void set_icon_path(const std::string& path) { icon_path = path; }
        void set_template_type(const std::string& t);
        void set_icon_id(const GLuint id) { icon_id = id; }
        void set_files(const std::vector<std::string>& files) { file_list = files; }

    private:
        // BEFORE CREATION
        std::string icon_path;
        project_type type; // exp. empty
        // AFTER CREATION
        std::string project_file_name; //
        std::vector<std::string> file_list; // extra files
        GLuint icon_id;
    };
}

#endif //ZGR_PROJECTTEMPLATE_H
