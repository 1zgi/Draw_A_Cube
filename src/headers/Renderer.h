#ifndef RENDERER_H
#define RENDERER_H


#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Window.h"
#include "Cube.h"
#include <SDL.h>
#include <SDL_opengl.h>
#include "shader.hpp"
class Renderer
{
public:
    Renderer(Window& window);
    ~Renderer();
    bool init();
    void render(Cube& cube);
    void cleanup();
    Window& getWindow(); // Ensure this method is declared
    void setLightPosition(const glm::vec3& position); // Add this method

private:
    Window& window;
    GLuint programID;
    GLuint MatrixID;
    GLuint ViewMatrixID;
    GLuint ModelMatrixID;
    GLuint LightID;
    glm::mat4 Projection;
    glm::mat4 View;
    glm::vec3 lightPos;
    bool compileShaders();
};

#endif // RENDERER_H
