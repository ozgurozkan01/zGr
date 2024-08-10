// (version 4.5)
#version 120

vec2 positions[3] = vec2[](
vec2(0.0, -0.5),
vec2(0.5, 0.5),
vec2(-0.5, 0.5)
);

// To be executed once for each vertex
void main() {
    gl_Position = vec4(positions[gl_VertexIndex], 0.0, 1.0);
}