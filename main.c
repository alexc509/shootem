#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include "bullet.h"
#include "player.h"

int main(void) {

    typedef enum GameScreen { GAMEPLAY, UPGRADESHOP, ENDING } GameScreen;

    InitWindow(800, 600, "Shootem");

    srand(time(NULL)); 
    GameScreen currentScreen = GAMEPLAY;

    for (int i = 0; i < MAX_BULLETS; i++) {
        player1Bullets[i].active = false;
        player2Bullets[i].active = false;
    }

    int player1SelectedUpgrade = 1;
    int player2SelectedUpgrade = 1;

    int totalUpgrades = 4;

    // Player 1 Upgrades

    // Speed Upgrade
    Rectangle player1BulletSpeedUpgrade = { 30, 100, 175, 50 };
    Color player1BulletSpeedUpgradeColor = GRAY;
    Color player1BulletSpeedUpgradeTextColor = BLACK;
    const char *player1BulletSpeedUpgradeText = "bSpeed Upgrade\nCost: 5xp";
    bool player1BulletSpeedUpgradeBought = 0;

    // Size Upgrade
    Rectangle player1BulletSizeUpgrade = { 30, 170, 175, 50 };
    Color player1BulletSizeUpgradeColor = GRAY;
    Color player1BulletSizeUpgradeTextColor = BLACK;
    const char *player1BulletSizeUpgradeText = "bSize Upgrade\nCost: 5xp";
    bool player1BulletSizeUpgradeBought = 0;

    // Bullet Bounce
    Rectangle player1BulletBounceUpgrade = { 30, 240, 175, 50 };
    Color player1BulletBounceUpgradeColor = GRAY;
    Color player1BulletBounceUpgradeTextColor = BLACK;
    const char *player1BulletBounceUpgradeText = "bBounce Upgrade\nCost: 10xp";
    bool player1BulletBounceUpgradeBought = 0;    

    // Dash
    Rectangle player1DashUpgrade = { 30, 310, 175, 50 };
    Color player1DashUpgradeColor = GRAY;
    Color player1DashUpgradeTextColor = BLACK;
    const char *player1DashUpgradeText = "pDash Upgrade\nCost: 10xp";
    bool player1DashUpgradeBought = 0;    
    // Player 2 Upgrades

    // Speed Upgrade
    Rectangle player2BulletSpeedUpgrade = { 530, 100, 175, 50 };
    Color player2BulletSpeedUpgradeColor = GRAY;
    Color player2BulletSpeedUpgradeTextColor = BLACK;
    const char *player2BulletSpeedUpgradeText = "bSpeed Upgrade\nCost: 5xp";
    bool player2BulletSpeedUpgradeBought = 0;

    // Size Upgrade
    Rectangle player2BulletSizeUpgrade = { 530, 170, 175, 50 };
    Color player2BulletSizeUpgradeColor = GRAY;
    Color player2BulletSizeUpgradeTextColor = BLACK;
    const char *player2BulletSizeUpgradeText = "bSize Upgrade\nCost: 5xp";
    bool player2BulletSizeUpgradeBought = 0;

    // Bullet Bounce
    Rectangle player2BulletBounceUpgrade = { 530, 240, 175, 50 };
    Color player2BulletBounceUpgradeColor = GRAY;
    Color player2BulletBounceUpgradeTextColor = BLACK;
    const char *player2BulletBounceUpgradeText = "bBounce Upgrade\nCost: 10xp";
    bool player2BulletBounceUpgradeBought = 0;  

    // Dash 
    Rectangle player2DashUpgrade = { 530, 310, 175, 50 };
    Color player2DashUpgradeColor = GRAY;
    Color player2DashUpgradeTextColor = BLACK;
    const char *player2DashUpgradeText = "pDash Upgrade\nCost: 10xp";
    bool player2DashUpgradeBought = 0; 

    float timeG;
    float lastShopTime = 0.0f;
    float dashCooldown_1;
    float dashCooldown_2;
    

    int framesCounter = 0; 
    int shopDelay = 30;

    int DashDelay = 5;
    float lastDashTime_1 = 0.0f;
    float lastDashTime_2 = 0.0f;

    bool spawnedHealthKit1 = false;
    bool spawnedHealthKit2 = false;

    bool healthKit1Collected = false;
    bool healthKit2Collected = false;

    Vector2 healthKit1Position;
    Vector2 healthKit2Position; 

    SetTargetFPS(60);

    // Main game looop
    while (!WindowShouldClose()) { 

        switch (currentScreen) {
            case GAMEPLAY:
                {
                    timeG = shopDelay - (GetTime() - lastShopTime);
                    char timeString[50];
                    gcvt(timeG,3 ,timeString);
                    if (timeG < 0) {
                        currentScreen = UPGRADESHOP;
                        lastShopTime = GetTime();
                    };

                    char dashCooldown_1String[50];
                    dashCooldown_1 = DashDelay - (GetTime() - lastDashTime_1);
                    gcvt(dashCooldown_1,3 ,dashCooldown_1String);
                    if (dashCooldown_1 < 0) {
                        strcpy(dashCooldown_1String, "Dash Ready [E]");
                    }

                    char dashCooldown_2String[50];
                    dashCooldown_2 = DashDelay - (GetTime() - lastDashTime_2);
                    gcvt(dashCooldown_2,3 ,dashCooldown_2String);
                    if (dashCooldown_2 < 0) {
                        strcpy(dashCooldown_2String, "Dash Ready\n [RSHIFT]");
                    }


                    char lastPressedMoveKeyPlayer1 = '\0';
                    char lastPressedMoveKeyPlayer2[50];

                    if (player1BulletSpeedUpgradeBought) Player1Upgrades[0] = 1;
                    if (player1BulletSizeUpgradeBought) Player1Upgrades[1] = 1;
                    if (player1BulletBounceUpgradeBought) Player1Upgrades[2] = 1;
                    if (player1DashUpgradeBought) Player1Upgrades[3] = 1;
                    

                    if (player2BulletSpeedUpgradeBought) Player2Upgrades[0] = 1;
                    if (player2BulletSizeUpgradeBought) Player2Upgrades[1] = 1; 
                    if (player2BulletBounceUpgradeBought) Player2Upgrades[2] = 1;  
                    if (player2DashUpgradeBought) Player2Upgrades[3] = 1;
                    
                    if (IsKeyDown(KEY_D) && squarePosition_1.x < 775) {
                        squarePosition_1.x += speed; 
                        lastPressedMoveKeyPlayer1 = 'D';
                    } 
                    if (IsKeyDown(KEY_A) && squarePosition_1.x > 0)  {
                        squarePosition_1.x -= speed;
                        lastPressedMoveKeyPlayer1 = 'A';
                    }
                    if (IsKeyDown(KEY_W) && squarePosition_1.y > 0) {
                        squarePosition_1.y -= speed; 
                        lastPressedMoveKeyPlayer1 = 'W'; 
                    }
                    if (IsKeyDown(KEY_S) && squarePosition_1.y < 575) {
                        squarePosition_1.y += speed; 
                        lastPressedMoveKeyPlayer1 = 'S';    
                    }   

                    if (IsKeyPressed(KEY_SPACE)) shootBullet_1(squarePosition_1, Player1Upgrades);
                    if (IsKeyPressed(KEY_E) && Player1Upgrades[3] == 1 && dashCooldown_1 < 0) {
                        lastDashTime_1 = GetTime();
                        switch (lastPressedMoveKeyPlayer1) {
                            case 'D':
                                squarePosition_1.x += 150;
                                break;
                            case 'A':
                                squarePosition_1.x -= 150;
                                break;
                            case 'W':
                                squarePosition_1.y -= 150;
                                break;
                            case 'S':
                                squarePosition_1.y += 150;
                                break;
                        }
                        if (squarePosition_1.x < 0) squarePosition_1.x = 0;
                        if (squarePosition_1.x > 775) squarePosition_1.x = 775;
                        if (squarePosition_1.y < 0) squarePosition_1.y = 0;
                        if (squarePosition_1.y > 575) squarePosition_1.y = 575;
                    }


                    if (IsKeyDown(KEY_RIGHT) && squarePosition_2.x < 775) {
                        squarePosition_2.x += speed;
                        strcpy(lastPressedMoveKeyPlayer2, "KEY_RIGHT");
                    }
                    if (IsKeyDown(KEY_LEFT) && squarePosition_2.x > 0) {
                        squarePosition_2.x -= speed;
                        strcpy(lastPressedMoveKeyPlayer2, "KEY_LEFT");
                    }
                    if (IsKeyDown(KEY_UP) && squarePosition_2.y > 0) {
                        squarePosition_2.y -= speed;
                        strcpy(lastPressedMoveKeyPlayer2, "KEY_UP");
                    }
                    if (IsKeyDown(KEY_DOWN) && squarePosition_2.y < 575) {
                        squarePosition_2.y += speed;   
                        strcpy(lastPressedMoveKeyPlayer2, "KEY_DOWN");
                    }

                    if (IsKeyPressed(KEY_RIGHT_CONTROL)) shootBullet_2(squarePosition_2, Player2Upgrades); 
                    if (IsKeyPressed(KEY_RIGHT_SHIFT) && Player2Upgrades[3] == 1  && dashCooldown_2 < 0) {
                        lastDashTime_2 = GetTime();
                        if (strcmp(lastPressedMoveKeyPlayer2, "KEY_RIGHT") == 0) {
                            squarePosition_2.x += 150;
                        } 
                        else if (strcmp(lastPressedMoveKeyPlayer2, "KEY_LEFT") == 0) {
                            squarePosition_2.x -= 150;
                        } 
                        else if (strcmp(lastPressedMoveKeyPlayer2, "KEY_UP") == 0) {
                            squarePosition_2.y -= 150;
                        } 
                        else if (strcmp(lastPressedMoveKeyPlayer2, "KEY_DOWN") == 0) {
                            squarePosition_2.y += 150;
                        }
                    }
                        if (squarePosition_2.x < 0) squarePosition_2.x = 0;
                        if (squarePosition_2.x > 775) squarePosition_2.x = 775;
                        if (squarePosition_2.y < 0) squarePosition_2.y = 0;
                        if (squarePosition_2.y > 575) squarePosition_2.y = 575;

                    updateBullets(squarePosition_1, squarePosition_2, squareSize, &player1Health, &player2Health, &player1Xp, &player2Xp, Player1Upgrades, Player2Upgrades);

                    if (player1Health == 0) {
                        currentScreen = ENDING;
                    }
                    else if (player2Health == 0) {
                        currentScreen = ENDING;
                    }

                    if (timeG < 0) {
                        currentScreen = UPGRADESHOP;
                    }

                    BeginDrawing();
                    ClearBackground(RAYWHITE);

                    DrawText(TextFormat("P1  %i/100", player1Health), 10, 0, 30, BLACK);
                    DrawText(TextFormat("P2  %i/100", player2Health), 625, 0, 30, BLACK);

                    DrawText((timeString), 350, 30, 30, BLACK);

                    DrawText(TextFormat("XP: %i", player1Xp), 10, 30, 30, BLACK);
                    DrawText(TextFormat("XP: %i", player2Xp), 625, 30, 30, BLACK);
                    
                    if (Player1Upgrades[3] == 1){
                        DrawText((dashCooldown_1String), 10, 500, 30, BLACK);
                    }
                    if (Player2Upgrades[3] == 1){
                        DrawText((dashCooldown_2String), 600, 500, 30, BLACK);
                    }


                    DrawRectangle(squarePosition_1.x, squarePosition_1.y, squareSize, squareSize, BLUE);
                    DrawRectangle(squarePosition_2.x, squarePosition_2.y, squareSize, squareSize, RED);

                    drawBullets();

                    if (timeG < 20 && !spawnedHealthKit1 && !healthKit1Collected) {
                        healthKit1Position.x = 100 + rand() % (701 - 100);
                        healthKit1Position.y = 100 + rand() % (501 - 100);
                        DrawRectangle(healthKit1Position.x, healthKit1Position.y, 20, 20, GREEN);
                        spawnedHealthKit1 = true;
                    }
                    if (timeG < 10 && !spawnedHealthKit2 && !healthKit2Collected) {
                        healthKit2Position.x = 100 + rand() % (701 - 100);
                        healthKit2Position.y = 100 + rand() % (501 - 100);
                        DrawRectangle(healthKit2Position.x, healthKit2Position.y, 20, 20, GREEN);
                        spawnedHealthKit2 = true;
                    }

                    // Drawing existing health kits
                    if (spawnedHealthKit1 && !healthKit1Collected) {
                        DrawRectangle(healthKit1Position.x, healthKit1Position.y, 20, 20, GREEN);
                    }
                    if (spawnedHealthKit2 && !healthKit2Collected) {
                        DrawRectangle(healthKit2Position.x, healthKit2Position.y, 20, 20, GREEN);
                    }

                    // Collision detection and health kit pickup
                    if (!healthKit1Collected && CheckCollisionRecs(
                        (Rectangle){healthKit1Position.x, healthKit1Position.y, 20, 20},
                        (Rectangle){squarePosition_1.x, squarePosition_1.y, squareSize, squareSize})) {
                        spawnedHealthKit1 = false;
                        healthKit1Collected = true;
                        if (player1Health + 10 > 100) {
                            player1Health = 100;
                        } else {
                            player1Health += 10;
                        }
                    }

                    if (!healthKit2Collected && CheckCollisionRecs(
                        (Rectangle){healthKit2Position.x, healthKit2Position.y, 20, 20},
                        (Rectangle){squarePosition_1.x, squarePosition_1.y, squareSize, squareSize})) {
                        spawnedHealthKit2 = false;
                        healthKit2Collected = true;
                        if (player1Health + 10 > 100) {
                            player1Health = 100;
                        } else {
                            player1Health += 10;
                        }
                    }

                    if (!healthKit1Collected && CheckCollisionRecs(
                        (Rectangle){healthKit1Position.x, healthKit1Position.y, 20, 20},
                        (Rectangle){squarePosition_2.x, squarePosition_2.y, squareSize, squareSize})) {
                        spawnedHealthKit1 = false;
                        healthKit1Collected = true;
                        if (player2Health + 10 > 100) {
                            player2Health = 100;
                        } else {
                            player2Health += 10;
                        }
                    }

                    if (!healthKit2Collected && CheckCollisionRecs(
                        (Rectangle){healthKit2Position.x, healthKit2Position.y, 20, 20},
                        (Rectangle){squarePosition_2.x, squarePosition_2.y, squareSize, squareSize})) {
                        spawnedHealthKit2 = false;
                        healthKit2Collected = true;
                        if (player2Health + 10 > 100) {
                            player2Health = 100;
                        } else {
                            player2Health += 10;
                        }
                    }

                    EndDrawing();
                    
            } break;

            case UPGRADESHOP: {
                
                framesCounter++;
                BeginDrawing();
                ClearBackground(GOLD);


                if (IsKeyPressed(KEY_W) && player1SelectedUpgrade > 1) {
                    player1SelectedUpgrade -= 1;
                }
                else if (IsKeyPressed(KEY_S) && player1SelectedUpgrade  < totalUpgrades) {
                    player1SelectedUpgrade += 1;
                }

                if (IsKeyPressed(KEY_UP) && player2SelectedUpgrade > 1) {
                    player2SelectedUpgrade -= 1;
                }
                else if (IsKeyPressed(KEY_DOWN) && player2SelectedUpgrade  < totalUpgrades) {
                    player2SelectedUpgrade += 1;
                }

                // Player 1 Upgrades

                //speed upgrade
                if (player1SelectedUpgrade == 1) {
                    if (!player1BulletSpeedUpgradeBought) player1BulletSpeedUpgradeTextColor = RAYWHITE;
                    else player1BulletSpeedUpgradeTextColor = GREEN; 
                    if (!player1BulletSizeUpgradeBought) player1BulletSizeUpgradeTextColor = BLACK;
                    else player1BulletSizeUpgradeTextColor = DARKGREEN;
                    if (!player1BulletBounceUpgradeBought) player1BulletBounceUpgradeTextColor = BLACK;
                    else player1BulletBounceUpgradeTextColor = DARKGREEN;
                    if (!player1DashUpgradeBought) player1DashUpgradeTextColor = BLACK;
                    else player1DashUpgradeTextColor = DARKGREEN;
                    if (player1BulletSpeedUpgradeBought == false) {
                        if (IsKeyPressed(KEY_F) && player1Xp >= 5) {
                            player1BulletSpeedUpgradeBought = 1;
                            player1Xp -= 5;
                            player1BulletSpeedUpgradeTextColor = DARKGREEN;
                        }
                            
                    }
                } 
                //size upgrade
                else if (player1SelectedUpgrade == 2) {
                    if (!player1BulletSizeUpgradeBought) player1BulletSizeUpgradeTextColor = RAYWHITE;
                    else player1BulletSizeUpgradeTextColor = GREEN; 
                    if (!player1BulletSpeedUpgradeBought) player1BulletSpeedUpgradeTextColor = BLACK;
                    else player1BulletSpeedUpgradeTextColor = DARKGREEN;
                    if (!player1BulletBounceUpgradeBought) player1BulletBounceUpgradeTextColor = BLACK;
                    else player1BulletBounceUpgradeTextColor = DARKGREEN;
                    if (!player1DashUpgradeBought) player1DashUpgradeTextColor = BLACK;
                    else player1DashUpgradeTextColor = DARKGREEN;
                    if (player1BulletSizeUpgradeBought == false) {
                        
                        if (IsKeyPressed(KEY_F) && player1Xp >= 5 && !player1BulletSizeUpgradeBought) {
                            player1BulletSizeUpgradeBought = 1;
                            player1Xp -= 5;
                            player1BulletSizeUpgradeTextColor = DARKGREEN;
                        }
                    }
                }
                //bounce upgrade
                else if (player1SelectedUpgrade == 3) {
                    if (!player1BulletBounceUpgradeBought) player1BulletBounceUpgradeTextColor = RAYWHITE;
                    else player1BulletBounceUpgradeTextColor = GREEN; 
                    if (!player1BulletSpeedUpgradeBought) player1BulletSpeedUpgradeTextColor = BLACK;
                    else player1BulletSpeedUpgradeTextColor = DARKGREEN;
                    if (!player1BulletSizeUpgradeBought) player1BulletSizeUpgradeTextColor = BLACK;
                    else player1BulletSizeUpgradeTextColor = DARKGREEN;
                    if (!player1DashUpgradeBought) player1DashUpgradeTextColor = BLACK;
                    else player1DashUpgradeTextColor = DARKGREEN;
                    if (player1BulletBounceUpgradeBought == false) {
                        
                        if (IsKeyPressed(KEY_F) && player1Xp >= 10 && !player1BulletBounceUpgradeBought) {
                            player1BulletBounceUpgradeBought = 1;
                            player1Xp -= 10;
                            player1BulletBounceUpgradeTextColor = DARKGREEN;
                        }
                    }
                }

                //dash
                else if (player1SelectedUpgrade == 4) {
                    if (!player1DashUpgradeBought) player1DashUpgradeTextColor = RAYWHITE;
                    else player1DashUpgradeTextColor = GREEN;      
                    if (!player1BulletSpeedUpgradeBought) player1BulletSpeedUpgradeTextColor = BLACK;
                    else player1BulletSpeedUpgradeTextColor = DARKGREEN;
                    if (!player1BulletSizeUpgradeBought) player1BulletSizeUpgradeTextColor = BLACK;
                    else player1BulletSizeUpgradeTextColor = DARKGREEN; 
                    if (!player1BulletBounceUpgradeBought) player1BulletBounceUpgradeTextColor = BLACK;
                    else player1BulletBounceUpgradeTextColor = DARKGREEN;  
                    if (player1DashUpgradeBought == false) {   
                        if (IsKeyPressed(KEY_F) && player1Xp >= 10) {
                            player1DashUpgradeBought = 1;
                            player1Xp -= 10;
                            player1DashUpgradeTextColor = DARKGREEN;
                        }  
                    }                          

                }

                // Player 2 Upgrades

                //speed upgrade
                if (player2SelectedUpgrade == 1) {
                    if (!player2BulletSpeedUpgradeBought) player2BulletSpeedUpgradeTextColor = RAYWHITE;
                    else player2BulletSpeedUpgradeTextColor = GREEN; 
                    if (!player2BulletSizeUpgradeBought) player2BulletSizeUpgradeTextColor = BLACK;
                    else player2BulletSizeUpgradeTextColor = DARKGREEN;
                    if (!player2BulletBounceUpgradeBought) player2BulletBounceUpgradeTextColor = BLACK;
                    else player2BulletBounceUpgradeTextColor = DARKGREEN;
                    if (!player2DashUpgradeBought) player2DashUpgradeTextColor = BLACK;
                    else player2DashUpgradeTextColor = DARKGREEN;


                    if (player2BulletSpeedUpgradeBought == false) {
                        if (IsKeyPressed(KEY_ENTER) && player2Xp >= 5) {
                            player2BulletSpeedUpgradeBought = 1;
                            player2Xp -= 5;
                            player2BulletSpeedUpgradeTextColor = DARKGREEN;
                        }
                            
                    }
                } 
                //size upgrade
                else if (player2SelectedUpgrade == 2) {
                    if (!player2BulletSizeUpgradeBought) player2BulletSizeUpgradeTextColor = RAYWHITE;
                    else player2BulletSizeUpgradeTextColor = GREEN; 
                    if (!player2BulletSpeedUpgradeBought) player2BulletSpeedUpgradeTextColor = BLACK;
                    else player2BulletSpeedUpgradeTextColor = DARKGREEN;
                    if (!player2BulletBounceUpgradeBought) player2BulletBounceUpgradeTextColor = BLACK;
                    else player2BulletBounceUpgradeTextColor = DARKGREEN;
                    if (!player2DashUpgradeBought) player2DashUpgradeTextColor = BLACK;
                    else player2DashUpgradeTextColor = DARKGREEN;

                    if (player2BulletSizeUpgradeBought == false) {
                        
                        if (IsKeyPressed(KEY_ENTER) && player2Xp >= 5 && !player2BulletSizeUpgradeBought) {
                            player2BulletSizeUpgradeBought = 1;
                            player2Xp -= 5;
                            player2BulletSizeUpgradeTextColor = DARKGREEN;
                        }
                    }
                }
                //bounce upgrade
                else if (player2SelectedUpgrade == 3) {
                    if (!player2BulletBounceUpgradeBought) player2BulletBounceUpgradeTextColor = RAYWHITE;
                    else player2BulletBounceUpgradeTextColor = GREEN; 
                    if (!player2BulletSpeedUpgradeBought) player2BulletSpeedUpgradeTextColor = BLACK;
                    else player2BulletSpeedUpgradeTextColor = DARKGREEN;
                    if (!player2BulletSizeUpgradeBought) player2BulletSizeUpgradeTextColor = BLACK;
                    else player2BulletSizeUpgradeTextColor = DARKGREEN;
                    if (!player2DashUpgradeBought) player2DashUpgradeTextColor = BLACK;
                    else player2DashUpgradeTextColor = DARKGREEN;
                    if (player2BulletBounceUpgradeBought == false) {
                        
                        if (IsKeyPressed(KEY_ENTER) && player2Xp >= 10 && !player2BulletBounceUpgradeBought) {
                            player2BulletBounceUpgradeBought = 1;
                            player2Xp -= 5;
                            player2BulletBounceUpgradeTextColor = DARKGREEN;
                        }
                    }
                }

                else if (player2SelectedUpgrade == 4) {
                    if (!player2DashUpgradeBought) player2DashUpgradeTextColor = RAYWHITE;
                    else player2DashUpgradeTextColor = GREEN;      
                    if (!player2BulletSpeedUpgradeBought) player2BulletSpeedUpgradeTextColor = BLACK;
                    else player2BulletSpeedUpgradeTextColor = DARKGREEN;
                    if (!player2BulletSizeUpgradeBought) player2BulletSizeUpgradeTextColor = BLACK;
                    else player2BulletSizeUpgradeTextColor = DARKGREEN; 
                    if (!player2BulletBounceUpgradeBought) player2BulletBounceUpgradeTextColor = BLACK;
                    else player2BulletBounceUpgradeTextColor = DARKGREEN;

                    if (player2DashUpgradeBought == false) {
                        
                        if (IsKeyPressed(KEY_ENTER) && player2Xp >= 10 && !player2DashUpgradeBought) {
                            player2DashUpgradeBought = 1;
                            player2Xp -= 10;
                            player2DashUpgradeTextColor = DARKGREEN;
                        }
                    }
                }

                DrawRectangleRec(player1BulletSpeedUpgrade, player1BulletSpeedUpgradeColor);
                DrawText(player1BulletSpeedUpgradeText, 35, 105, 20, player1BulletSpeedUpgradeTextColor);
                DrawRectangleRec(player1BulletSizeUpgrade, player1BulletSizeUpgradeColor);
                DrawText(player1BulletSizeUpgradeText, 35, 175, 20, player1BulletSizeUpgradeTextColor);
                DrawRectangleRec(player1BulletBounceUpgrade, player1BulletBounceUpgradeColor);
                DrawText(player1BulletBounceUpgradeText, 35, 245, 20, player1BulletBounceUpgradeTextColor);
                DrawRectangleRec(player1DashUpgrade, player1DashUpgradeColor);
                DrawText(player1DashUpgradeText, 35, 315, 20, player1DashUpgradeTextColor);

                DrawRectangleRec(player2BulletSpeedUpgrade, player2BulletSpeedUpgradeColor);
                DrawText(player2BulletSpeedUpgradeText, 535, 105, 20, player2BulletSpeedUpgradeTextColor);
                DrawRectangleRec(player2BulletSizeUpgrade, player2BulletSizeUpgradeColor);
                DrawText(player2BulletSizeUpgradeText, 535, 175, 20, player2BulletSizeUpgradeTextColor);
                DrawRectangleRec(player2BulletBounceUpgrade, player2BulletBounceUpgradeColor);
                DrawText(player2BulletBounceUpgradeText, 535, 245, 20, player2BulletBounceUpgradeTextColor);
                DrawRectangleRec(player2DashUpgrade, player2DashUpgradeColor);
                DrawText(player2DashUpgradeText, 535, 315, 20, player2DashUpgradeTextColor);

                DrawText(("Upgrade Shop!\n10 Seconds"), 250, 30, 32, BLACK);
                DrawText(TextFormat("XP: %i", player1Xp), 10, 30, 30, BLACK);
                DrawText(TextFormat("XP: %i", player2Xp), 625, 30, 30, BLACK);
                EndDrawing();


                if (framesCounter > 600) {  // 10s
                    currentScreen = GAMEPLAY;
                    framesCounter = 0;
                    lastShopTime = GetTime();

                    spawnedHealthKit1 = false;
                    spawnedHealthKit2 = false;
                    healthKit1Collected = false;
                    healthKit2Collected = false;
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