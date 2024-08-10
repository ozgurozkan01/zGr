//
// Created by ozgur on 8/10/2024.
//

#include "../include/graphic_pipeline.h"
#include <fstream>
#include <iostream>

namespace zgr
{
    graphic_pipeline::graphic_pipeline(const std::string &vertex_file_path, const std::string &fragment_file_path)
    {
        create_graphics_pipeline(vertex_file_path, fragment_file_path);
    }

    std::vector<char> graphic_pipeline::read_file(const std::string& file_name)
    {
        // ate: Start reading at the end of the file
        // binary: Read the file as binary file (avoid text transformations)
        // The advantage of starting to read at the end of the file is that
        // we can use the read position to determine the size of the file and allocate a buffer:
        std::ifstream file(file_name, std::ios::ate | std::ios::binary);

        if (!file.is_open())
        {
            std::cerr << "Failed to open file : " << file_name;
        }

        // tellg retunrs the file current read position - end of the file.
        size_t file_size = static_cast<size_t>(file.tellg());
        std::vector<char> file_content_buffer(file_size);

        // change the current read position as 0 "zero" - beginning of the file
        file.seekg(0);
        file.read(file_content_buffer.data(), file_size);

        file.close();

        return file_content_buffer;
    }

    [[maybe_unused]] void graphic_pipeline::create_graphics_pipeline(const std::string& vertex_file_path, const std::string& fragment_file_path)
    {
        std::vector<char> vertex_shader_code = read_file(vertex_file_path);
        std::vector<char> fragment_shader_code = read_file(fragment_file_path);

        std::cout << "Vertex   : " << vertex_shader_code.size() << "\n";
        std::cout << "Fragment : " << fragment_shader_code.size() << "\n";
    }
}