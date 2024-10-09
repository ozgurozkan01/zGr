//
// Created by ozgur on 10/8/2024.
//

#include "../include/Serialize.h"
#include <fstream>
#include <iostream>
#include <exception>

namespace zgr
{
    [[maybe_unused]] void Serialize::to_file(const ProjectTemplate &project_temp, const std::string &path)
    {
        try
        {
            std::string serialized_file_path = path + "\\templates\\" + project_temp.get_template_type() + "\\.bin";
            std::ofstream ofile(serialized_file_path, std::ios::binary);
            if (!ofile.is_open())
            {
                throw std::ios_base::failure("Error occurred while serializing the file.");
            }

            size_t length = project_temp.get_template_type().size();
            ofile.write(reinterpret_cast<const char*>(&length), sizeof(length));
            ofile.write(project_temp.get_template_type().c_str(), length);

            length = project_temp.get_project_file_name().size();
            ofile.write(reinterpret_cast<const char*>(&length), sizeof(length));
            ofile.write(project_temp.get_project_file_name().c_str(), length);

            length = project_temp.get_icon_path().size();
            ofile.write(reinterpret_cast<const char*>(&length), sizeof(length));
            ofile.write(project_temp.get_icon_path().c_str(), length);

            size_t folderCount = project_temp.get_files().size();
            ofile.write(reinterpret_cast<const char*>(&folderCount), sizeof(folderCount));

            for (const auto& folder : project_temp.get_files())
            {
                length = folder.size();
                ofile.write(reinterpret_cast<const char*>(&length), sizeof(length));
                ofile.write(folder.c_str(), length);
            }

            ofile.close();
            std::cerr << "Serialized completed!!\n";

        }
        catch (const std::exception& ex)
        {
            std::cerr << "Exception caught while serializing: " << ex.what() << std::endl;
            exit(-1);
        }
    }

    ProjectTemplate Serialize::from_file(const std::string &path)
    {
        ProjectTemplate temp;

        try
        {
            std::ifstream ifile(path, std::ios::binary);
            if (!ifile.is_open())
            {
                throw std::ios_base::failure("Error occurred while serializing the file.");
            }

            size_t length;
            ifile.read(reinterpret_cast<char*>(&length), sizeof(length));
            std::string template_type(length, '\0');
            ifile.read(&template_type[0], length);
            temp.set_template_type(template_type);

            ifile.read(reinterpret_cast<char*>(&length), sizeof(length));
            std::string file_name(length, '\0');
            ifile.read(&file_name[0], length);
            temp.set_project_file_name(file_name);

            ifile.read(reinterpret_cast<char*>(&length), sizeof(length));
            std::string icon_path(length, '\0');
            ifile.read(&icon_path[0], length);
            temp.set_icon_path(icon_path);

            size_t folderCount;
            ifile.read(reinterpret_cast<char*>(&folderCount), sizeof(folderCount));
            std::vector<std::string> folders(folderCount);

            for (size_t i = 0; i < folderCount; ++i) {
                ifile.read(reinterpret_cast<char*>(&length), sizeof(length));
                folders[i].resize(length);
                ifile.read(&folders[i][0], length);
            }
            temp.set_files(folders);


            std::cout << temp.get_template_type() << std::endl;
            std::cout << temp.get_project_file_name() << std::endl;
            std::cout << temp.get_icon_path() << std::endl;

            for (const auto& file : temp.get_files())
            {
                std::cout << file << std::endl;
            }

            ifile.close();
            std::cerr << "Deserialized completed!!\n";

        }
        catch (const std::exception& ex)
        {
            std::cerr << "Exception caught while deserializing : " << ex.what() << std::endl;
            exit(-1);
        }

        return temp;
    }
}