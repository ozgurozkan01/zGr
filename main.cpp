#include "scripts/editor/include/Launcher.h"

int main()
{
    zgr::editor::Launcher launcher(840, 720, "zGr Game Engine");

    while (!launcher.window_should_close())
    {
        launcher.render();
    }

    return 0;
}
