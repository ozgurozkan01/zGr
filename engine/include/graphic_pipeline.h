//
// Created by ozgur on 8/10/2024.
//

#ifndef ZGR_GRAPHIC_PIPELINE_H
#define ZGR_GRAPHIC_PIPELINE_H

#include <string>
#include <vector>

namespace zgr
{
    class graphic_pipeline {
    public:
        graphic_pipeline(const std::string& vertex_file_path, const std::string& fragment_file_path);
    private:
        static std::vector<char> read_file(const std::string& file_name);
        [[maybe_unused]] void create_graphics_pipeline(const std::string& vertex_file_path, const std::string& fragment_file_path);
    };
}

#endif //ZGR_GRAPHIC_PIPELINE_H
