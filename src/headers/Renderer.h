#ifndef RENDERER_H
#define RENDERER_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "shader.hpp"
#include "Window.h"
#include "Cube.h"

class Renderer {
public:
    Renderer(Window& window);
    ~Renderer();
    bool init();
    void render(Cube& cube);
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
};

#endif
