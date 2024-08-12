//
// Created by ozgur on 8/12/2024.
//

#include <iostream>
#include <vector>
#include "../include/renderer.h"
#include "../../thirdParty/include/glfw/glfw3.h"

namespace zgr
{

    renderer::renderer() { init(); }
    renderer::~renderer() { terminate();}

    void renderer::init()
    {
        create_instance();
    }
    void renderer::terminate()
    {
        vkDestroyInstance(instance, nullptr);

    }

    void renderer::create_instance()
    {
        create_app_info();
        create_instance_info();

        enumerate_instance_extension();

        bool isCreationValid = vkCreateInstance(&instance_info, nullptr, &instance);

        if (isCreationValid != VK_SUCCESS)
        {
            std::cerr << "failed to create instance!\n";
            exit(-1);
        }
    }

    void renderer::create_app_info()
    {
        app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        app_info.pApplicationName = "First Triangle";
        app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        app_info.pEngineName = "ZGR ENGINE";
        app_info.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        app_info.apiVersion = VK_API_VERSION_1_0;
    }

    void renderer::create_instance_info()
    {
        instance_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        instance_info.pNext = nullptr;
        instance_info.flags = 0;
        instance_info.pApplicationInfo = &app_info;

        /*
         Vulkan is a platform agnostic API, which means that you need an extension to interface with the window system.
         GLFW has a handy built-in function that returns the extension(s) it needs to do
         */
        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        /* enumerate the glfw extensions */
        std::vector<std::string> requiredExtensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

        for (const auto& extension : requiredExtensions)
        {
            std::cout << extension.c_str() << '\n';
        }

        instance_info.enabledExtensionCount = glfwExtensionCount;
        instance_info.ppEnabledExtensionNames = glfwExtensions;
        instance_info.enabledLayerCount = 0;
    }

    void renderer::enumerate_instance_extension()
    {
        uint32_t extensionCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
        std::vector<VkExtensionProperties> extensions(extensionCount);
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

        std::cout << "available extensions count : " << extensionCount << std::endl;

        for (const auto& extension : extensions)
        {
            std::cout << '\t' << extension.extensionName << '\n';
        }
    }
}