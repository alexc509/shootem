#include "raylib.h"

int main(void) {
    InitWindow(800, 600, "Shoot");
    

    // Square properties
    Vector2 squarePosition_1 = {100.0f, 100.0f};
    Vector2 squarePosition_2 = {700.0f, 100.0f};
    float squareSize = 25.0f;
    float speed = 5.0f;

    SetTargetFPS(60);

    // Main game looop
    while (!WindowShouldClose()) { 

        // Update
        if (IsKeyDown(KEY_D)) squarePosition_1.x += speed;
        if (IsKeyDown(KEY_A)) squarePosition_1.x -= speed;
        if (IsKeyDown(KEY_W)) squarePosition_1.y -= speed; 
        if (IsKeyDown(KEY_S)) squarePosition_1.y += speed;       

        if (IsKeyDown(KEY_RIGHT)) squarePosition_2.x += speed;
        if (IsKeyDown(KEY_LEFT)) squarePosition_2.x -= speed;
        if (IsKeyDown(KEY_UP)) squarePosition_2.y -= speed;
        if (IsKeyDown(KEY_DOWN)) squarePosition_2.y += speed;   

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawRectangle(squarePosition_1.x, squarePosition_1.y, squareSize, squareSize, BLUE);
        DrawRectangle(squarePosition_2.x, squarePosition_2.y, squareSize, squareSize, RED);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
