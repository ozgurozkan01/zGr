//
// Created by ozgur on 10/8/2024.
//

#ifndef ZGR_SERIALIZE_H
#define ZGR_SERIALIZE_H

#include "../../editor/include/ProjectTemplate.h"
#include <iostream>

namespace zgr
{
    using namespace editor;

    class Serialize {
    public:
        Serialize() = default;

        [[maybe_unused]] static void to_file(const ProjectTemplate& project_temp, const std::string& path);
        [[maybe_unused]] static ProjectTemplate from_file(const std::string& path);
    };
}


#endif //ZGR_SERIALIZE_H
