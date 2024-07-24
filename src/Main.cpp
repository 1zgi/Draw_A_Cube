#include "headers/Window.h"
#include "headers/Renderer.h"
#include "headers/Cube.h"

const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;

int main(int argc, char* args[]) {
    Window window(SCREEN_WIDTH, SCREEN_HEIGHT);
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
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }
        renderer.render(cube);
    }

    return 0;
}
