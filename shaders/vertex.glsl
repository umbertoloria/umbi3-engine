#version 330 core

in vec3 aPosition;
in vec3 aColor;
in vec3 aNormal;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 transformationMatrix;
uniform vec3 viewPosition;

out vec3 oColor;
out vec3 oNormal;
out vec3 oViewPosition;
out vec3 oFragPosition;

void main () {
    oColor = aColor;
    oNormal = mat3(transpose(inverse(transformationMatrix))) * aNormal;
    oViewPosition = viewPosition;
    oFragPosition = vec3(transformationMatrix * vec4(aPosition, 1.0));
    gl_Position = projectionMatrix * viewMatrix * vec4(oFragPosition, 1.0);
}