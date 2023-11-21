#include <raylib.h>
#include <rlgl.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    InitWindow(1280, 720, "Game of Life");

    SetTargetFPS(10);

    Shader gol_shader = LoadShader(0, "shader/gol_shader.glsl");
    Shader view_shader = LoadShader(0, "shader/view_shader.glsl");
    
    Image gol_init_image = LoadImage("image/gol_init.png");
    int gol_size = gol_init_image.width;
    
    // // Params are unused here for some reason
    uint32_t framebuffer = rlLoadFramebuffer(gol_size, gol_size);

    Texture2D gol_textures[2];

    for (size_t i = 0; i < 2; i++) {
        gol_textures[i] = (Texture2D) {
            .id = rlLoadTexture(gol_init_image.data, gol_size, gol_size, RL_PIXELFORMAT_UNCOMPRESSED_GRAYSCALE, 1),
            .width = gol_size,
            .height = gol_size,
            .mipmaps = 1,
            .format = RL_PIXELFORMAT_UNCOMPRESSED_GRAYSCALE
        };
        rlTextureParameters(gol_textures[i].id, RL_TEXTURE_MIN_FILTER, RL_TEXTURE_FILTER_NEAREST);
        rlTextureParameters(gol_textures[i].id, RL_TEXTURE_MAG_FILTER, RL_TEXTURE_FILTER_NEAREST);
    }

    size_t gol_index = 0;

    while (!WindowShouldClose()) {
        rlFramebufferAttach(framebuffer, gol_textures[gol_index].id, RL_ATTACHMENT_COLOR_CHANNEL0, RL_ATTACHMENT_TEXTURE2D, 0);

        rlEnableFramebuffer(framebuffer);

        rlClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        rlClearScreenBuffers();

        rlActiveDrawBuffers(1);

        rlDisableColorBlend();
        BeginTextureMode((RenderTexture2D) { .texture = { .width = gol_size, .height = gol_size } });
        BeginShaderMode(gol_shader);
        rlEnableFramebuffer(framebuffer);
        rlClearColor(0.0, 0.0, 0.0, 1.0); // keep it black so it doesn't leak into g-buffer
        rlClearScreenBuffers();
        DrawTexture(gol_textures[gol_index ^ 1], 0, 0, WHITE);
        EndShaderMode();
        EndTextureMode();
        rlDisableFramebuffer();
        rlEnableColorBlend();

        rlActiveDrawBuffers(1);

        BeginDrawing();
        BeginShaderMode(view_shader);

        DrawTexturePro(gol_textures[gol_index], (Rectangle) {
            .x = 0,
            .y = 0,
            .width = (float)gol_textures[gol_index].width,
            .height = (float)gol_textures[gol_index].height
        }, (Rectangle) {
            .x = 0,
            .y = 0,
            .width = 720,
            .height = 720
        }, (Vector2) { 0, 0 }, 0.0f, WHITE);

        EndShaderMode();
        EndDrawing();

        gol_index ^= 1;
    }

    CloseWindow();

    return 0;

}