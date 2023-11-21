#version 420 core
layout (location = 0) out vec4 color;

uniform sampler2D texture0;

in vec2 fragTexCoord;

void main() {
    vec4 alive = texture(texture0, fragTexCoord);
    color = vec4(alive.r, alive.r, alive.r, 1.0);
}