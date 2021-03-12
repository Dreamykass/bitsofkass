// shader.frag
#version 450

layout(location=0) in vec3 v_color; // from the vertex shader
layout(location=0) out vec4 f_color; // to the buffer 0 - current texture from the swapchain, the screen

void main() {
//    f_color = vec4(0.3, 0.2, 0.1, 1.0);
    f_color = vec4(v_color, 1.0);
}
