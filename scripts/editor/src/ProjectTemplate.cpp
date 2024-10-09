//
// Created by ozgur on 9/29/2024.
//

#include <utility>

#include "../include/ProjectTemplate.h"
#include "../../serialize/include/Serialize.h"

namespace zgr::editor
{
    ProjectTemplate::ProjectTemplate(std::string i_path, project_type type, std::string p_file)  :
            icon_path(std::move(i_path)),
            type(type),
            project_file_name(std::move(p_file))
    {
        file_list.emplace_back(".zgr");
        file_list.emplace_back("Content");
        file_list.emplace_back("GameCode");
    }

    std::string ProjectTemplate::get_template_type() const
    {
        switch (type)
        {
            case project_type::empty: return "Empty";
            case project_type::third_person: return "Third Person";
            case project_type::first_person: return "First Person";
        }

        return "Invalid Type";
    }

    void ProjectTemplate::set_template_type(const std::string &t)
    {
        if      (t == "Empty")        { this->type = project_type::empty; }
        else if (t == "Third Person") { this->type = project_type::third_person; }
        else if (t == "First Person") { this->type = project_type::first_person; }
        else                          { this->type = project_type::invalid; }
    }
}