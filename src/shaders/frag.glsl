#version 330 core

in vec3 fragmentColor;
in vec3 fragmentPosition_worldspace;
in vec3 fragmentNormal_cameraspace;

out vec3 color;

uniform vec3 LightPosition_worldspace;
uniform mat4 V;

void main(){
    vec3 LightColor = vec3(1, 1, 1);
    float LightPower = 50.0f;

    vec3 MaterialDiffuseColor = fragmentColor;
    vec3 MaterialAmbientColor = vec3(0.1) * MaterialDiffuseColor;
    vec3 MaterialSpecularColor = vec3(0.3, 0.3, 0.3);

    vec3 LightPosition_cameraspace = (V * vec4(LightPosition_worldspace, 1)).xyz;
    vec3 EyeDirection_cameraspace = vec3(0, 0, -1);
    vec3 LightDirection_cameraspace = LightPosition_cameraspace - fragmentPosition_worldspace;

    float distance = length(LightDirection_cameraspace);

    vec3 n = normalize(fragmentNormal_cameraspace);
    vec3 l = normalize(LightDirection_cameraspace);

    float cosTheta = clamp(dot(n, l), 0, 1);

    vec3 E = normalize(EyeDirection_cameraspace);
    vec3 R = reflect(-l, n);
    float cosAlpha = clamp(dot(E, R), 0, 1);

    color = MaterialAmbientColor +
            MaterialDiffuseColor * LightColor * LightPower * cosTheta / (distance * distance) +
            MaterialSpecularColor * LightColor * LightPower * pow(cosAlpha, 5) / (distance * distance);
}
