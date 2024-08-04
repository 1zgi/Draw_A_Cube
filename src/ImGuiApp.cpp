#include "headers/ImGuiApp.h"

ImGuiApp::ImGuiApp() : window(nullptr) {}

ImGuiApp::~ImGuiApp()
{
    Cleanup();
}

bool ImGuiApp::Init(Window* window)
{
    this->window = window;

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    // io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; // Enable Multi-Viewport / Platform Windows if needed

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer bindings
    if (!ImGui_ImplSDL2_InitForOpenGL(window->getWindow(), window->getContext()))
    {
        std::cerr << "Failed to initialize ImGui SDL2 backend!" << std::endl;
        return false;
    }
    if (!ImGui_ImplOpenGL3_Init("#version 330"))
    {
        std::cerr << "Failed to initialize ImGui OpenGL3 backend!" << std::endl;
        return false;
    }

    return true;
}

void ImGuiApp::Run(Renderer* renderer, Cube* cube)
{
    while (!done)
    {
        // Poll and handle events
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT)
                done = true;
            if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(renderer->getWindow().getWindow()))
                done = true;
        }

        // Start the ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        // ImGui code goes here
        ImGui::Begin("Light Control");
        ImGui::SliderFloat3("Light Position", &lightPosition[0], -10.0f, 10.0f);
        ImGui::End();

        // Update the light position in the renderer
        renderer->setLightPosition(lightPosition);

        // Render your scene
        renderer->render(*cube);

        // Rendering ImGui
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Swap buffers
        SDL_GL_SwapWindow(renderer->getWindow().getWindow());

        // Check for OpenGL errors
        GLenum err;
        while ((err = glGetError()) != GL_NO_ERROR) {
            std::cerr << "OpenGL error: " << err << std::endl;
        }
    }
}

void ImGuiApp::Cleanup()
{
    // Cleanup ImGui
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    // Cleanup SDL
    if (window) {
        SDL_GL_DeleteContext(window->getContext());
        SDL_DestroyWindow(window->getWindow());
        window = nullptr;
    }
    SDL_Quit();
}
