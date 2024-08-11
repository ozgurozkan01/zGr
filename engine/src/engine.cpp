//
// Created by ozgur on 8/8/2024.
//

#include "../include/engine.h"
#include "../include/screen.h"
#include "../include/graphic_pipeline.h"

namespace zgr
{

    engine::engine()
    {
        init();
    }

    engine::~engine()
    {
        delete engine_screen;
        delete engine_pipeline;
    }

    void engine::run()
    {
        while (!engine_screen->should_close())
        {
            glfwPollEvents();
        }
    }

    void engine::init()
    {
        engine_screen = new screen();
        engine_pipeline = new graphic_pipeline(
                "../shaders/vertex_shader.vert.spv",
                "../shaders/fragment_shader.frag.spv");
    }
}