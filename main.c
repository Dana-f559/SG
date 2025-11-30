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

const int N_SELECT = 9;

static const int RIGHT_TURN = 1;
static const int LEFT_TURN = -1;

static int DIRECTION = RIGHT_TURN;

int main(void) {
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    SetTargetFPS(60);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "gate");

    
    Symbol *list = addSymbols(SCREEN_CENTRE, RADIUS_SIZE, N_SYMBOLS);
    Symbol *selectList = addSymbols(SCREEN_CENTRE, RADIUS_SIZE + 40, N_SELECT);


    printf("X: %f Y: %f\n", list[0].pos.x, list[0].pos.y);
    
    float angle = findAngleRadians(list[0].pos, list[1].pos, SCREEN_CENTRE);
    printf("ANGLE: %f, R:%f\n", angle, PI/2);
    RotationHandler handler;
    // handler.groupRotationOffset = 1.0;
    // handler.maxRotation = 1.57079633;
    handler.groupRotationOffset = -PI/2;
    

    // handler.maxRotation = PI/2;
    handler.maxRotation = angle;
    // handler.maxRotation = 0.0f;

    handler.list = list;
    handler.nSymbols = N_SYMBOLS;
    handler.radius = RADIUS_SIZE;
    handler.ScrCenter = SCREEN_CENTRE;
    handler.direction = RIGHT_TURN;

    bool isRotating = true;
    // float nextRotationTarget = some_initial_value;

    // ignore
    // size_t d_l[7] = {1, 2, 3, 6, 7, 8, 0};
    // size_t d_s[7] = {1, 2, 3, 4, 5, 6, 7};
    while (!WindowShouldClose()) {
        if (!isRotating) {
            float gr = handler.groupRotationOffset;
            handler.groupRotationOffset = handler.maxRotation;
            handler.maxRotation = gr;

            isRotating = true;

        }
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