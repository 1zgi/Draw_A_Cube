#include "headers/Window.h"
#include "headers/Renderer.h"
#include "headers/Cube.h"
#include "headers/ImGuiApp.h"

const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;

int main(int argc, char* args[]) {
    Window window(SCREEN_WIDTH, SCREEN_HEIGHT);
    ImGuiApp app;

    if (!window.init()) {
        return -1;
    }

    Renderer renderer(window);
    if (!renderer.init()) {
        return -1;
    }

    Cube cube;
    cube.init();

    bool running = true;
    SDL_Event event;
    ImGuiApp imguiApp;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        if (!imguiApp.Init(&window))
        {
            std::cerr << "Failed to initialize ImGui!" << std::endl;
            return -1;
        }

        imguiApp.Run(&renderer, &cube);
        
    }

    //imguiApp.Cleanup();
    
    

    return 0;
}
