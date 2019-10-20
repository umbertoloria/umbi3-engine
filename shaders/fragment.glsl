#version 330 core

out vec4 fragColor;

in vec3 oColor;
in vec3 oNormal;

void main () {
    vec3 norm = normalize(oNormal);
    fragColor = vec4(oColor, 1.0);
}