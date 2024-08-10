//
// Created by ozgur on 8/8/2024.
//

#ifndef ZGR_SCREEN_H
#define ZGR_SCREEN_H

#include "../../thirdParty/include/glfw/glfw3.h"
#include <string>

namespace zgr
{
    class screen {
    public:
        /* Prevent copying the screen and posibility of dangling pointer */
        screen(const screen&) = delete;
        screen &operator=(const screen&) = delete;

        screen();
        ~screen();

        [[maybe_unused]] [[nodiscard]] bool should_close() const;

    private:
        // Window Variables
        static constexpr uint16_t window_width = 480;
        static constexpr uint16_t window_height = 360;
        static constexpr std::string window_title = "ZGR ENGINE";

        [[maybe_unused]] bool init_window();


        GLFWwindow* window; // main screen window
    };
}

#endif //ZGR_SCREEN_H
