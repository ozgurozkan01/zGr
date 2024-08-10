//
// Created by ozgur on 8/8/2024.
//

#ifndef ZGR_ENGINE_H
#define ZGR_ENGINE_H

namespace zgr
{
    class screen;
    class graphic_pipeline;

    class engine {
    public:
        engine();
        ~engine();

        void run();

    private:

        void init();

        screen* engine_screen{};
        graphic_pipeline* engine_pipeline{};
    };
}

#endif //ZGR_ENGINE_H
