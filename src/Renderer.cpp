#include "headers/Renderer.h"

Renderer::Renderer(Window& window)
    : window(window),
    programID(0),
    MatrixID(0),
    ViewMatrixID(0),
    ModelMatrixID(0),
    LightID(0),
    Projection(glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f)),
    View(glm::lookAt(glm::vec3(4, 3, -3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0))),
    lightPos(4.0f, 4.0f, 4.0f) {}

Renderer::~Renderer() {
    glDeleteProgram(programID);
}

bool Renderer::init() {
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return false;
    }

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    programID = LoadShaders("src/shaders/vert.glsl", "src/shaders/frag.glsl");
    if (programID == 0) {
        fprintf(stderr, "Failed to load shaders\n");
        return false;
    }

    MatrixID = glGetUniformLocation(programID, "MVP");
    ViewMatrixID = glGetUniformLocation(programID, "V");
    ModelMatrixID = glGetUniformLocation(programID, "M");
    LightID = glGetUniformLocation(programID, "LightPosition_worldspace");

    glUseProgram(programID);
    glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &View[0][0]);
    glUniform3f(LightID, lightPos.x, lightPos.y, lightPos.z);

    return true;
}

void Renderer::render(Cube& cube) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 Model = glm::rotate(glm::mat4(1.0f), (float)SDL_GetTicks() / 1000.0f * glm::radians(50.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 MVP = Projection * View * Model;

    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
    glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &Model[0][0]);

    cube.draw();
    SDL_GL_SwapWindow(window.getWindow());
}
