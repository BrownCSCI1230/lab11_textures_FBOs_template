#version 330 core

layout (location = 0) in vec3 pos;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projMatrix;

out vec4 world_pos;
out vec4 world_normal;
out vec4 camera_pos;

void main() {
   gl_Position = projMatrix * viewMatrix * modelMatrix * vec4(pos,1);
   world_pos = modelMatrix * vec4(pos,1);
   world_normal = transpose(inverse(modelMatrix)) * normalize(vec4(pos,0));
   camera_pos = inverse(viewMatrix) * vec4(0,0,0,1);
}
