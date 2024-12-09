#include "raylib.h"

typedef struct Bullet {
    Vector2 position;
    Vector2 speed;
    Vector2 size;
    bool active;

} Bullet;

#define MAX_BULLETS 10

 Bullet player1Bullets[MAX_BULLETS];
 Bullet player2Bullets[MAX_BULLETS];

void shootBullet_1(Vector2 position) {
    for (int i = 0; i < MAX_BULLETS; i++) {
        if(!player1Bullets[i].active) {
            player1Bullets[i].position = position;
            player1Bullets[i].speed = (Vector2){10.0f, 0.0f};
            player1Bullets[i].size = (Vector2){5.0f, 5.0f};
            player1Bullets[i].active = true;
            break;
        }
    }
}

void shootBullet_2(Vector2 position) {
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (!player2Bullets[i].active) {
            player2Bullets[i].position = position;
            player2Bullets[i].speed = (Vector2){-10.0f, 0.0f}; // Moving to the left
            player2Bullets[i].size = (Vector2){5.0f, 5.0f};
            player2Bullets[i].active = true;
            break;
        }
    }
}

// Function to update and draw bullets
void updateBullets(Vector2 squarePosition_1, Vector2 squarePosition_2, float squareSize, int* player1Health, int* player2Health) {
    // Update player 1 bullets
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (player1Bullets[i].active) {
            player1Bullets[i].position.x += player1Bullets[i].speed.x;
            if (CheckCollisionRecs(
                (Rectangle){player1Bullets[i].position.x, player1Bullets[i].position.y, player1Bullets[i].size.x, player1Bullets[i].size.y},
                (Rectangle){squarePosition_2.x, squarePosition_2.y, squareSize, squareSize}))
            {
                if (*player2Health > 0) {
                    (*player2Health) -= 1;
                }
                player1Bullets[i].active = false;
            }
            if (player1Bullets[i].position.x > GetScreenWidth()) {
                player1Bullets[i].active = false; // Deactivate the bullet when it goes off-screen
            }
        }
    }

    // Update player 2 bullets
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (player2Bullets[i].active) {
            player2Bullets[i].position.x += player2Bullets[i].speed.x;
           if (CheckCollisionRecs(
                (Rectangle){player2Bullets[i].position.x, player2Bullets[i].position.y, player2Bullets[i].size.x, player2Bullets[i].size.y},
                (Rectangle){squarePosition_1.x, squarePosition_1.y, squareSize, squareSize}))
            {
                if (*player1Health > 0) {
                    (*player1Health) -= 1;
                }
                player1Bullets[i].active = false;
            }
            if (player2Bullets[i].position.x < 0) {
                player2Bullets[i].active = false; // Deactivate the bullet when it goes off-screen
            }
        }
    }
}

// Function to draw bullets
void drawBullets() {
    // Draw player 1 bullets
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (player1Bullets[i].active) {
            DrawRectangleV(player1Bullets[i].position, player1Bullets[i].size, BLUE);
        }
    }

    // Draw player 2 bullets
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (player2Bullets[i].active) {
            DrawRectangleV(player2Bullets[i].position, player2Bullets[i].size, RED);
        }
    }
}

int main(void) {
    InitWindow(800, 600, "Shoot");

    // Square properties
    Vector2 squarePosition_1 = {100.0f, 100.0f};
    Vector2 squarePosition_2 = {700.0f, 100.0f};
    float squareSize = 25.0f;
    float speed = 5.0f;

    int player1Health = 5;
    int player2Health = 5;

    // Initialize bullets to inactive
    for (int i = 0; i < MAX_BULLETS; i++) {
        player1Bullets[i].active = false;
        player2Bullets[i].active = false;
    }

    SetTargetFPS(60);

    // Main game looop
    while (!WindowShouldClose()) { 

        // Update
        if (IsKeyDown(KEY_D) && squarePosition_1.x < 775) squarePosition_1.x += speed;
        if (IsKeyDown(KEY_A) && squarePosition_1.x > 0) squarePosition_1.x -= speed;
        if (IsKeyDown(KEY_W) && squarePosition_1.y > 0) squarePosition_1.y -= speed; 
        if (IsKeyDown(KEY_S) && squarePosition_1.y < 575) squarePosition_1.y += speed;       

        if (IsKeyPressed(KEY_SPACE)) {    
            shootBullet_1(squarePosition_1);
        }

        if (IsKeyDown(KEY_RIGHT) && squarePosition_2.x < 775) squarePosition_2.x += speed;
        if (IsKeyDown(KEY_LEFT) && squarePosition_2.x > 0) squarePosition_2.x -= speed;
        if (IsKeyDown(KEY_UP) && squarePosition_2.y > 0) squarePosition_2.y -= speed;
        if (IsKeyDown(KEY_DOWN) && squarePosition_2.y < 575) squarePosition_2.y += speed;   

        if (IsKeyPressed(KEY_RIGHT_CONTROL)) shootBullet_2(squarePosition_2); 

        // Update Bullets
        updateBullets(squarePosition_1, squarePosition_2, squareSize, &player1Health, &player2Health);

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText(TextFormat("P1  %i/5", player1Health), 10, 0, 30, BLACK);
        DrawText(TextFormat("P2  %i/5", player2Health), 675, 0, 30, BLACK);
        DrawRectangle(squarePosition_1.x, squarePosition_1.y, squareSize, squareSize, BLUE);
        DrawRectangle(squarePosition_2.x, squarePosition_2.y, squareSize, squareSize, RED);

        // Draw bullets
        drawBullets();


        EndDrawing();
    }

    CloseWindow();
    return 0;
}
