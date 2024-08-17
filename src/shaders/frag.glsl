#version 330 core

in vec3 fragmentColor;
in vec3 Position_worldspace;
in vec3 Normal_cameraspace;
in vec3 EyeDirection_cameraspace;
in vec3 LightDirection_cameraspace;

uniform vec3 AmbientLightIntensity;

out vec4 color;

void main() {
    vec3 MaterialDiffuseColor = fragmentColor;
    vec3 MaterialAmbientColor = AmbientLightIntensity * MaterialDiffuseColor;
    vec3 MaterialSpecularColor = vec3(0.3, 0.3, 0.3);

    vec3 n = normalize(Normal_cameraspace);
    vec3 l = normalize(LightDirection_cameraspace);
    float cosTheta = clamp(dot(n, l), 0.0, 1.0);

    vec3 E = normalize(EyeDirection_cameraspace);
    vec3 R = reflect(-l, n);
    float cosAlpha = clamp(dot(E, R), 0.0, 1.0);

    vec3 finalColor = MaterialAmbientColor + 
                      MaterialDiffuseColor * cosTheta + 
                      MaterialSpecularColor * pow(cosAlpha, 5.0);

    color = vec4(finalColor, 1.0);
}
