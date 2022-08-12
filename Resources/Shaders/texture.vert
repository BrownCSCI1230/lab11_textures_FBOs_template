#version 330 core

// TASK 15: add a second layout variable representing a UV coordinate
layout (location = 0) in vec3 position;

// TASK 16: create an "out" variable representing a UV coordinate

void main() {
    // TASK 16: assign the UV layout variable to the UV "out" variable

    gl_Position = vec4(position, 1.0);
}
