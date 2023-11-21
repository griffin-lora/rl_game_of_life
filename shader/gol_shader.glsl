#version 420 core
layout (location = 0) out float out_alive;

uniform sampler2D texture0;

in vec2 fragTexCoord;

void main() {
    vec2 tex_coord = vec2(fragTexCoord.x, 1.0 - fragTexCoord.y);

    float alive = texture(texture0, tex_coord).r;
    float sum = 
        textureOffset(texture0, tex_coord, ivec2(-1, 0)).r +
        textureOffset(texture0, tex_coord, ivec2(1, 0)).r +
        textureOffset(texture0, tex_coord, ivec2(0, 1)).r +
        textureOffset(texture0, tex_coord, ivec2(0, -1)).r +
        textureOffset(texture0, tex_coord, ivec2(-1, -1)).r +
        textureOffset(texture0, tex_coord, ivec2(1, -1)).r +
        textureOffset(texture0, tex_coord, ivec2(-1, 1)).r +
        textureOffset(texture0, tex_coord, ivec2(1, 1)).r;

    if (sum < 2.0 || sum > 3.0) {
        out_alive = 0.0;
        return;
    }
    if (sum == 3.0) {
        out_alive = 1.0;
        return;
    }
    if (sum == 2.0 || sum == 3.0) {
        out_alive = alive;
        return;
    }
}