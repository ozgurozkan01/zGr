//
// Created by ozgur on 8/8/2024.
//

#define GLFW_INCLUDE_VULKAN

#include "../include/screen.h"
#include <iostream>

namespace zgr
{
    screen::screen()
    {
        if (!init_window()) { exit(-1); }
    }

    screen::~screen()
    {
        glfwDestroyWindow(window);
        /* Deactive the initialized glfw lib */
        glfwTerminate();
    }

    [[maybe_unused]] bool screen::init_window()
    {
        if (!glfwInit())
        {
            std::cerr << "GLFW lib could not be initialized!\n";
            return false;
        }

        /*
         Vulkan does not have a context and the Vulkan instance is created via the Vulkan API itself.
         If you will be using Vulkan to render to a window, disable context creation by setting the GLFW_CLIENT_API hint to GLFW_NO_API
         */
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        /* Disable the resizability of window */
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        window = glfwCreateWindow(window_width, window_height, window_title.c_str(), nullptr, nullptr);

        return true;
    }

    bool screen::should_close() const { return glfwWindowShouldClose(window); }

}