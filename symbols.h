#include <raylib.h>
#include <stddef.h>

typedef struct {
    Vector2 pos;
    size_t n;
} Symbol;

typedef struct {
    float groupRotationOffset;
    float maxRotation;
    Symbol *list;
    int nSymbols;
    float radius;
    Vector2 ScrCenter;
    int direction;

} RotationHandler;

/**
  * Create a list of Vector2 that points to each symbol, with the first symbol being in the centre at the top.
  * @param center The center of the circle.
  * @param radius The radius of the circle.
  * @param scount The number of symbols.
 */

Vector2 *createSymbolsVectors(Vector2 center, float radius, size_t scount);

Vector2 *createShevronsVectors(Vector2 center, float radius, size_t scount);

Symbol *addShevrons(Vector2 center, float radius, size_t scount);
/**
  * Creates a list of symbols, using the createSymbolsVectors
  * @param center The center of the circle.
  * @param radius The radius of the circle.
  * @param scount The number of symbols.
 */
Symbol *addSymbols(Vector2 center, float radius, size_t scount);

/**
  * Find the angle distance between two vectors, that have the same origin point
  * @param v1 First vector.
  * @param v2 Second vector.
 */

float findAngleRadians(Vector2 v1, Vector2 v2, Vector2 center);

/**
  * Draw the square while keeping its angle looking at the centre.
  * @param SCREEN_CENTRE Vector2 to the centre of the screen.
  * @param list List of all of the symbols
  * @param N_SYMBOLS The number of total symbols.
  * @param size Size of the square in a Vector2.
*/
void drawSquareInOrbitAndRotate( Vector2 SCREEN_CENTRE, Symbol *list, int N_SYMBOLS, Vector2 size, Color color);
void drawSquareInOrbit(Symbol *list, int N_SYMBOLS, Vector2 size, Color color);
/**
  * Rotates all of the symbols, based on an orbit, at n degrees.
*/
void rotateSymbol(RotationHandler *h, bool *isRotating);
// void rotateSymbol(float *groupRotationOffset, float maxRotation, Symbol* list, int N_SYMBOLS, float RADIUS_SIZE, Vector2 SCREEN_CENTRE, int turn_dir);