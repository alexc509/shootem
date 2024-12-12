#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>

typedef enum GameScreen { GAMEPLAY, UPGRADESHOP, ENDING } GameScreen;

typedef struct Bullet {
    Vector2 position;
    Vector2 speed;
    Vector2 size;
    bool active;

} Bullet;

#define MAX_BULLETS 10

 Bullet player1Bullets[MAX_BULLETS];
 Bullet player2Bullets[MAX_BULLETS];

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
/*  1. 2x Bullet speed
    2. 2x Bullet Size
    3. Side Shoot
    4. Up and down shoot
  */
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

void updateBullets(Vector2 squarePosition_1, Vector2 squarePosition_2, float squareSize, int* player1Health, int* player2Health, int *player1Xp, int *player2Xp) {

    for (int i = 0; i < MAX_BULLETS; i++) {
        if (player1Bullets[i].active) {
            player1Bullets[i].position.x += player1Bullets[i].speed.x;
            if (CheckCollisionRecs(
                (Rectangle){player1Bullets[i].position.x, player1Bullets[i].position.y, player1Bullets[i].size.x, player1Bullets[i].size.y},
                (Rectangle){squarePosition_2.x, squarePosition_2.y, squareSize, squareSize}))
            {
                if (*player2Health > 0) {
                    (*player2Health) -= 1;
                    *player1Xp += 1;
                }
                player1Bullets[i].active = false;
            }
            if (player1Bullets[i].position.x > GetScreenWidth()) {
                player1Bullets[i].active = false;
            }
        }
    }

    for (int i = 0; i < MAX_BULLETS; i++) {
        if (player2Bullets[i].active) {
            player2Bullets[i].position.x += player2Bullets[i].speed.x;
           if (CheckCollisionRecs(
                (Rectangle){player2Bullets[i].position.x, player2Bullets[i].position.y, player2Bullets[i].size.x, player2Bullets[i].size.y},
                (Rectangle){squarePosition_1.x, squarePosition_1.y, squareSize, squareSize}))
            {
                if (*player1Health > 0) {
                    (*player1Health) -= 1;
                    *player2Xp += 1;
                }
                player2Bullets[i].active = false;
            }
            if (player2Bullets[i].position.x < 0) {
                player2Bullets[i].active = false;
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

int main(void) {
    InitWindow(800, 600, "Shoot");

    GameScreen currentScreen = GAMEPLAY;

    // Square properties
    Vector2 squarePosition_1 = {100.0f, 100.0f};
    Vector2 squarePosition_2 = {700.0f, 100.0f};
    float squareSize = 25.0f;
    float speed = 5.0f;

    int player1Health = 100;
    int player2Health = 100;

    int player1Xp = 0;
    int player2Xp = 0;

    for (int i = 0; i < MAX_BULLETS; i++) {
        player1Bullets[i].active = false;
        player2Bullets[i].active = false;
    }

    int Player1Upgrades[4] = {0,0,0,0};
    int Player2Upgrades[4] = {0,0,0,0};

    int player1SelectedUpgrade = 1;
    int player2SelectedUpgrade = 1;


    // Speed Upgrade
    Rectangle player1BulletSpeedUpgrade = { 30, 100, 175, 50 };
    Color player1BulletSpeedUpgradeColor = GRAY;
    Color player1BulletSpeedUpgradeTextColor = BLACK;
    const char *player1BulletSpeedUpgradeText = "Speed Upgrade\nCost: 5xp";
    bool player1BulletSpeedUpgradeBought = 0;

    // Size Upgrade
    Rectangle player1BulletSizeUpgrade = { 30, 170, 175, 50 };
    Color player1BulletSizeUpgradeColor = GRAY;
    Color player1BulletSizeUpgradeTextColor = BLACK;
    const char *player1BulletSizeUpgradeText = "Size Upgrade\nCost: 5xp";
    bool player1BulletSizeUpgradeBought = 0;

    float time;
    float lastShopTime = 0.0f;

    int framesCounter = 0; 
    SetTargetFPS(60);

    // Main game looop
    while (!WindowShouldClose()) { 

        switch (currentScreen) {
            case GAMEPLAY:
                {
                time = 30 - (GetTime() - lastShopTime);

                char timeString[50];
                gcvt(time,3 ,timeString);
                if (time < 0) {
                    currentScreen = UPGRADESHOP;
                    lastShopTime = GetTime();
                };

                if (player1BulletSpeedUpgradeBought) Player1Upgrades[0] = 1;
                if (player1BulletSizeUpgradeBought) Player1Upgrades[1] = 1;
                
                if (IsKeyDown(KEY_D) && squarePosition_1.x < 775) squarePosition_1.x += speed;
                if (IsKeyDown(KEY_A) && squarePosition_1.x > 0) squarePosition_1.x -= speed;
                if (IsKeyDown(KEY_W) && squarePosition_1.y > 0) squarePosition_1.y -= speed; 
                if (IsKeyDown(KEY_S) && squarePosition_1.y < 575) squarePosition_1.y += speed;       

                if (IsKeyPressed(KEY_SPACE)) shootBullet_1(squarePosition_1, Player1Upgrades);


                if (IsKeyDown(KEY_RIGHT) && squarePosition_2.x < 775) squarePosition_2.x += speed;
                if (IsKeyDown(KEY_LEFT) && squarePosition_2.x > 0) squarePosition_2.x -= speed;
                if (IsKeyDown(KEY_UP) && squarePosition_2.y > 0) squarePosition_2.y -= speed;
                if (IsKeyDown(KEY_DOWN) && squarePosition_2.y < 575) squarePosition_2.y += speed;   

                if (IsKeyPressed(KEY_RIGHT_CONTROL)) shootBullet_2(squarePosition_2, Player2Upgrades); 

                updateBullets(squarePosition_1, squarePosition_2, squareSize, &player1Health, &player2Health, &player1Xp, &player2Xp);

                if (player1Health == 0) {
                    currentScreen = ENDING;
                }
                else if (player2Health == 0) {
                    currentScreen = ENDING;
                }

                if (time < 0) {
                    currentScreen = UPGRADESHOP;
                }

                BeginDrawing();
                ClearBackground(RAYWHITE);

                DrawText(TextFormat("P1  %i/100", player1Health), 10, 0, 30, BLACK);
                DrawText(TextFormat("P2  %i/100", player2Health), 625, 0, 30, BLACK);

                DrawText((timeString), 350, 30, 30, BLACK);

                DrawText(TextFormat("XP: %i", player1Xp), 10, 30, 30, BLACK);
                DrawText(TextFormat("XP: %i", player2Xp), 625, 30, 30, BLACK);
                DrawRectangle(squarePosition_1.x, squarePosition_1.y, squareSize, squareSize, BLUE);
                DrawRectangle(squarePosition_2.x, squarePosition_2.y, squareSize, squareSize, RED);

                drawBullets();

                EndDrawing();
            } break;

            case UPGRADESHOP: {
                
                framesCounter++;
                BeginDrawing();
                ClearBackground(GOLD);


                if (IsKeyPressed(KEY_W) && player1SelectedUpgrade > 1) {
                    player1SelectedUpgrade -= 1;
                }
                else if (IsKeyPressed(KEY_S) && player1SelectedUpgrade  < 2) {
                    player1SelectedUpgrade += 1;
                }

                // Player 1 Upgrades
                if (player1SelectedUpgrade == 1) {
                    if (!player1BulletSizeUpgradeBought) player1BulletSizeUpgradeTextColor = BLACK;
                    else player1BulletSizeUpgradeTextColor = GREEN;
                    player1BulletSpeedUpgradeTextColor = RAYWHITE;
                    if (player1BulletSpeedUpgradeBought == false) {
                        if (IsKeyPressed(KEY_F) && player1Xp >= 5) {
                            player1BulletSpeedUpgradeBought = 1;
                            player1Xp -= 5;
                            player1BulletSpeedUpgradeTextColor = GREEN;
                        }
                            
                    }
                } 
                else if (player1SelectedUpgrade == 2) {
                    if (!player1BulletSpeedUpgradeBought) player1BulletSpeedUpgradeTextColor = BLACK;
                    else player1BulletSpeedUpgradeTextColor = GREEN;
                    player1BulletSizeUpgradeTextColor = RAYWHITE;
                    if (player1BulletSizeUpgradeBought == false) {
                        
                        if (IsKeyPressed(KEY_F) && player1Xp >= 5 && !player1BulletSizeUpgradeBought) {
                            player1BulletSizeUpgradeBought = 1;
                            player1Xp -= 5;
                            player1BulletSizeUpgradeTextColor = GREEN;
                        }
                    }
                }

                DrawRectangleRec(player1BulletSpeedUpgrade, player1BulletSpeedUpgradeColor);
                DrawText(player1BulletSpeedUpgradeText, 35, 105, 20, player1BulletSpeedUpgradeTextColor);
                DrawRectangleRec(player1BulletSizeUpgrade, player1BulletSizeUpgradeColor);
                DrawText(player1BulletSizeUpgradeText, 35, 175, 20, player1BulletSizeUpgradeTextColor);

                DrawText(("Upgrade Shop!\n10 Seconds"), 250, 30, 32, BLACK);
                DrawText(TextFormat("XP: %i", player1Xp), 10, 30, 30, BLACK);
                DrawText(TextFormat("XP: %i", player2Xp), 625, 30, 30, BLACK);
                EndDrawing();


                if (framesCounter > 600) {  // 10s
                    currentScreen = GAMEPLAY;
                    framesCounter = 0;
                    lastShopTime = GetTime();
                }
                
            } break;

            case ENDING: {
                BeginDrawing();
                ClearBackground(BLACK);
                if (player1Health == 0) DrawText("Player 2 Wins", 275, 20, 40, RED);
                else if (player2Health == 0) DrawText("Player 1 Wins", 275, 20, 40, RED);
                EndDrawing();
            } break;
        }

    }
    
    CloseWindow();
    return 0;
}