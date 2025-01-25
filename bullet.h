#ifndef BULLET_H
#define BULLET_H

#include "raylib.h"

#define MAX_NILLETS 100

void shootBullet_1(Vector2 position, int *Player1Upgrades);
void shootBullet_2(Vector2 position, int *Player2Upgrades);

void updateBullets(Vector2 squarePosition_1, Vector2 squarePosition_2, float squareSize, int* player1Health, int* player2Health, int *player1Xp, int *player2Xp, int *Player1Upgrades, int *Player2Upgrades);

void drawBullets();

#define MAX_BULLETS 100

typedef struct Bullet {
    Vector2 position;
    Vector2 speed;
    Vector2 size;
    bool active;

} Bullet;

 extern Bullet player1Bullets[MAX_BULLETS];
 extern Bullet player2Bullets[MAX_BULLETS];

#endif