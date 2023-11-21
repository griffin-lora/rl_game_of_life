#include <raylib.h>

int main() {
    InitWindow(1280, 720, "Game of Life");

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        EndDrawing();
    }

    CloseWindow();

    return 0;

}