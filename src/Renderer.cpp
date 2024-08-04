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
    lightPos(4.0f, 4.0f, 4.0f),
    vao(0),
    vbo(0)
{}

Renderer::~Renderer() {
    cleanup();
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

    // Initialize VAO and VBO
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // Assuming some vertex data setup here...

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return true;
}

void Renderer::render(Cube& cube) {
    // Clear the buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Set the viewport
    int width, height;
    SDL_GetWindowSize(window.getWindow(), &width, &height);
    glViewport(0, 0, width, height);

    // Compute the MVP matrix
    glm::mat4 Model = glm::rotate(glm::mat4(1.0f), (float)SDL_GetTicks() / 1000.0f * glm::radians(50.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 MVP = Projection * View * Model;

    // Pass the MVP matrix to the shader
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
    glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &Model[0][0]);

    // Update the light position in the shader
    glUniform3f(LightID, lightPos.x, lightPos.y, lightPos.z);

    // Render the cube
    cube.draw();

    // Check for OpenGL errors
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        std::cerr << "OpenGL error: " << err << std::endl;
    }
}

void Renderer::cleanup() {
    // Cleanup shaders
    if (programID) {
        glDeleteProgram(programID);
        programID = 0;
    }

    // Cleanup VAO and VBO
    if (vbo) {
        glDeleteBuffers(1, &vbo);
        vbo = 0;
    }

    if (vao) {
        glDeleteVertexArrays(1, &vao);
        vao = 0;
    }

    // Any additional cleanup for OpenGL resources
}

void Renderer::setLightPosition(const glm::vec3& position) {
    lightPos = position;
}

Window& Renderer::getWindow() {
    return window;
}
