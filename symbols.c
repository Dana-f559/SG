#include <math.h>
#include <raylib.h>
#include <raymath.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#include "symbols.h"

Vector2 *createSymbolsVectors(Vector2 center, float radius, size_t scount) {
    Vector2 *list = (Vector2 *)malloc(scount * sizeof(Vector2));
    if (list == NULL) return NULL;
    
    float d_theta = 2.f * PI / (float)scount;

    for (size_t i = 0; i < scount; i++) {
        // float angle = i * d_theta;
        float angle = i * d_theta - PI / 2.0f;
        list[i] = (Vector2){center.x + radius * cosf(angle), 
                            center.y + radius * sinf(angle)};

        // float angle = i * d_theta + PI / 2.0f;
        // printf("ANGLE: %f\n", angle);
        // list[i] = (Vector2){center.y + radius * sinf(angle) ,
        //                     center.x + radius * cosf(angle)};
    
        
    }
    return list;
}

Symbol *addSymbols(Vector2 center, float radius, size_t scount) {
    Symbol *slist = (Symbol *)malloc(scount * sizeof(Symbol));

    Vector2 *list = createSymbolsVectors(center, radius, scount); 
    for (int i = 0; i < scount; i ++) {
        slist[i].pos = list[i];
        slist[i].n = i;
    }

    free(list);
    return slist;
}

// TODO: NOT WORKING, RETURNING A NEGATIVE VALUE
float findAngleRadians(Vector2 v1, Vector2 v2, Vector2 center) {

    v1 = Vector2Normalize(Vector2Subtract(v1, center));
    v2 = Vector2Normalize(Vector2Subtract(v2, center));
    float angleRadians = Vector2Angle(v1, v2);

    return angleRadians;
}

void drawSquareInOrbitAndRotate( Vector2 SCREEN_CENTRE, Symbol *list, int N_SYMBOLS, Vector2 size, Color color){
    for (int i = 0; i < N_SYMBOLS; i++) {
            
        // rotate square
        Vector2 direction = Vector2Subtract(SCREEN_CENTRE, list[i].pos);
        float angleRadians = atan2f(direction.y, direction.x);
        float rotationAngle = angleRadians * (180.0f / PI);

        // rotate it per orbit
        Rectangle rec = {list[i].pos.x , list[i].pos.y , size.x, size.y };
        Vector2 origin = { size.x / 2, size.y / 2 };

        if (i == 0) {
            DrawRectanglePro(rec, origin, rotationAngle, GREEN);
        } else {
            DrawRectanglePro(rec, origin, rotationAngle, color);
        }
        // DrawRectanglePro(rec, origin, rotationAngle, color);

    }
}


// void rotateSymbol(float *groupRotationOffset, float maxRotation, Symbol* list, int N_SYMBOLS, float RADIUS_SIZE, Vector2 SCREEN_CENTRE, int turn_dir) {    
void rotateSymbol(RotationHandler *handler, bool *isRotating) {
    if (!(*isRotating)) return;

    if (handler->groupRotationOffset <= handler->maxRotation) {
        for (int i = 0; i < handler->nSymbols; i++) {
            float angle = handler->groupRotationOffset + (2 * PI * i / handler->nSymbols);
            handler->list[i].pos = (Vector2){
            handler->ScrCenter.x + handler->radius * handler->direction * cosf(angle),
            handler->ScrCenter.y + handler->radius * sinf(angle)};
            
        }
        handler->groupRotationOffset += 1.0f * GetFrameTime();
    }
}