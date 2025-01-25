#include "raylib.h"
#include "bullet.h"

// Define the actual arrays here
Bullet player1Bullets[MAX_BULLETS] = { 0 };
Bullet player2Bullets[MAX_BULLETS] = { 0 };

void shootBullet_1(Vector2 position, int *Player1Upgrades) {
    for (int i = 0; i < MAX_BULLETS; i++) {
        if(!player1Bullets[i].active) {
            player1Bullets[i].position = position;
            if (Player1Upgrades[0] == 1) {
                player1Bullets[i].speed = (Vector2){20.0f, 0.0f};
            }
            else player1Bullets[i].speed = (Vector2){10.0f, 0.0f};

            if (Player1Upgrades[1] == 1) {
                player1Bullets[i].size = (Vector2){20.0f, 20.0f};
            }           
            else player1Bullets[i].size = (Vector2){5.0f, 5.0f};
            player1Bullets[i].active = true;
            break; 
        }
    }
}

void shootBullet_2(Vector2 position, int *Player2Upgrades) {
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (!player2Bullets[i].active) {
            player2Bullets[i].position = position;
            if (Player2Upgrades[0] == 1) {
                player2Bullets[i].speed = (Vector2){-20.0f, 0.0f};
            }
            else player2Bullets[i].speed = (Vector2){-10.0f, 0.0f};

            if (Player2Upgrades[1] == 1) {
                player2Bullets[i].size = (Vector2){20.0f, 20.0f};
            }           
            else player2Bullets[i].size = (Vector2){5.0f, 5.0f};
            player2Bullets[i].active = true;
            break;
        }
    }
}

void updateBullets(Vector2 squarePosition_1, Vector2 squarePosition_2, float squareSize, int* player1Health, int* player2Health, int *player1Xp, int *player2Xp, int *Player1Upgrades, int *Player2Upgrades) {
    // Update player 1 bullets

    for (int i = 0; i < MAX_BULLETS; i++) {
        if (player1Bullets[i].active) {
            bool hitWall = false;

            if (player1Bullets[i].position.x > 800 && Player1Upgrades[2] == 1) {
                player1Bullets[i].speed.x = -player1Bullets[i].speed.x; 
                player1Bullets[i].position.x = 800;
                hitWall = true;
            }
            else if (CheckCollisionRecs(
                (Rectangle){player1Bullets[i].position.x, player1Bullets[i].position.y, player1Bullets[i].size.x, player1Bullets[i].size.y},
                (Rectangle){squarePosition_2.x, squarePosition_2.y, squareSize, squareSize})) {
                
                if (*player2Health > 0) {
                    (*player2Health) -= 1;
                    *player1Xp += 1;
                }
                player1Bullets[i].active = false;
            }
            else if (player1Bullets[i].position.x > 800 && Player1Upgrades[2] == 0) {
                player1Bullets[i].active = false;
            }
            else if (!hitWall){
                player1Bullets[i].position.x += player1Bullets[i].speed.x;
                if (player1Bullets[i].position.x < 0) {
                    player1Bullets[i].active = false;
                }
            }
        }
    }
    // Update player 2 bullets

    for (int i = 0; i < MAX_BULLETS; i++) {
        if (player2Bullets[i].active) {
            bool hitWall = false;

            if (player2Bullets[i].position.x < 0 && Player2Upgrades[2] == 1) {
                player2Bullets[i].speed.x = -player2Bullets[i].speed.x; 
                player2Bullets[i].position.x = 0;
                hitWall = true;
            }
            else if (CheckCollisionRecs(
                (Rectangle){player2Bullets[i].position.x, player2Bullets[i].position.y, player2Bullets[i].size.x, player2Bullets[i].size.y},
                (Rectangle){squarePosition_1.x, squarePosition_1.y, squareSize, squareSize})) {
                
                if (*player1Health > 0) {
                    (*player1Health) -= 1;
                    *player2Xp += 1;
                }
                player2Bullets[i].active = false;
            }
            else if (player2Bullets[i].position.x < 0 && Player2Upgrades[2] == 0) {
                player2Bullets[i].active = false;
            }
            else if (!hitWall){
                player2Bullets[i].position.x += player2Bullets[i].speed.x;
                if (player2Bullets[i].position.x > 800) {
                    player2Bullets[i].active = false;
                }
            }
        }
    }
}

void drawBullets() {

    for (int i = 0; i < MAX_BULLETS; i++) {
        if (player1Bullets[i].active) {
            DrawRectangleV(player1Bullets[i].position, player1Bullets[i].size, BLUE);
        }
    }

    for (int i = 0; i < MAX_BULLETS; i++) {
        if (player2Bullets[i].active) {
            DrawRectangleV(player2Bullets[i].position, player2Bullets[i].size, RED);
        }
    }
}