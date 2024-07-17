#version 330 core

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 vertexColor;
layout(location = 2) in vec3 vertexNormal_modelspace;

out vec3 fragmentColor;
out vec3 fragmentPosition_worldspace;
out vec3 fragmentNormal_cameraspace;

uniform mat4 MVP;
uniform mat4 V;
uniform mat4 M;

void main(){
    gl_Position = MVP * vec4(vertexPosition_modelspace, 1);

    fragmentPosition_worldspace = (M * vec4(vertexPosition_modelspace, 1)).xyz;
    fragmentColor = vertexColor;
    fragmentNormal_cameraspace = (V * M * vec4(vertexNormal_modelspace, 0)).xyz;
}
