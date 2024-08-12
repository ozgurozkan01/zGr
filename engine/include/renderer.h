//
// Created by ozgur on 8/12/2024.
//

#ifndef ZGR_RENDERER_H
#define ZGR_RENDERER_H

#include "../../thirdParty/include/vulkan/vulkan.h"

namespace zgr
{
    class renderer {
    public:
        renderer();
        ~renderer();
    private:
        void init();
        void terminate();

        void create_instance();
        void create_app_info();
        void create_instance_info();

        void enumerate_instance_extension();

        VkInstance instance;
        VkApplicationInfo app_info;
        VkInstanceCreateInfo instance_info;
    };
}

#endif //ZGR_RENDERER_H
