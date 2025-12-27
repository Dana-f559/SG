#include <math.h>
#include <raylib.h>
#include <raymath.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#include "symbols.h"

const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 900;
const Vector2 SCREEN_CENTRE = { .y = (float) SCREEN_HEIGHT / 2.0f, .x = (float) SCREEN_WIDTH / 2.0f };
const int N_SYMBOLS = 4;
const float RADIUS_SIZE = 350.0f;

const int N_SELECT = 4;

static const int RIGHT_TURN = 1;
static const int LEFT_TURN = -1;

static int DIRECTION = RIGHT_TURN;

int main(void) {
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    SetTargetFPS(60);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "gate");

    
    Symbol *list = addSymbols(SCREEN_CENTRE, RADIUS_SIZE, N_SYMBOLS);
    Symbol *selectList = addShevrons(SCREEN_CENTRE, RADIUS_SIZE + 40, N_SELECT);

    // printf("%f", );
    // float dialing[7] = {3 * PI/2, };

    RotationHandler handler;
    // handler.groupRotationOffset = 3 * PI/2;
    handler.groupRotationOffset = 0;
    handler.maxRotation = 3 * PI/2;
    // handler.groupRotationOffset = 1 * PI/2;
    // handler.maxRotation = 3 * PI/2;

    // float s = -PI/2;
    handler.list = list;
    handler.nSymbols = N_SYMBOLS;
    handler.radius = RADIUS_SIZE;
    handler.ScrCenter = SCREEN_CENTRE;
    handler.direction = RIGHT_TURN;

    bool isRotating = true;

    // ignore
    // size_t d_l[7] = {1, 2, 3, 6, 7, 8, 0};
    // size_t d_s[7] = {1, 2, 3, 4, 5, 6, 7};
    while (!WindowShouldClose()) {
        rotateSymbol(&handler, &isRotating); 
        
        BeginDrawing();

        ClearBackground(WHITE);
        DrawFPS(SCREEN_WIDTH - 100, 10);

        // draw the centre circle, and a ring of the suposed path around
        DrawCircle(SCREEN_CENTRE.x, SCREEN_CENTRE.y, 20, RED);
        DrawCircleLines(450.0f, 450.0f, RADIUS_SIZE, RED);
        

        // draw the squares 
        drawSquareInOrbitAndRotate(SCREEN_CENTRE, list, N_SYMBOLS, (Vector2){.x = 40, .y = 40}, BLUE);
        drawSquareInOrbitAndRotate(SCREEN_CENTRE, selectList, N_SELECT, (Vector2){.x = 40, .y = 40}, RED);
        EndDrawing();
    }
    CloseWindow();

    free(list);
    free(selectList);

    return 0;
}