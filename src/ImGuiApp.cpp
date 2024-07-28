#include "headers/ImGuiApp.h"

ImGuiApp::~ImGuiApp()
{
    Cleanup();
}

bool ImGuiApp::Init(Window* window)
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    // io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; // Enable Multi-Viewport / Platform Windows if needed

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer bindings
    ImGui_ImplSDL2_InitForOpenGL(window->getWindow(), window->getContext());
    ImGui_ImplOpenGL3_Init("#version 330");

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

        // Render ImGui
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Check for OpenGL errors
        GLenum err;
        while ((err = glGetError()) != GL_NO_ERROR) {
            std::cerr << "OpenGL error: " << err << std::endl;
        }

        SDL_GL_SwapWindow(renderer->getWindow().getWindow());
    }
}

void ImGuiApp::Cleanup()
{
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}
