#version 330 core

in vec3 aPosition;
in vec3 aColor;
in vec3 aNormal;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 transformationMatrix;

out vec3 oColor;
out vec3 oNormal;

void main () {
    gl_Position = projectionMatrix * viewMatrix * transformationMatrix * vec4(aPosition, 1.0);
//    gl_Position = transformationMatrix * vec4(aPosition, 1.0);
    oColor = aColor;
    oNormal = aNormal;
}