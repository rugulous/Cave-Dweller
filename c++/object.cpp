#include "object.h"
#include "enemies.h"

Roguelike::Object::Object(int x, int y, char *symbol, char *name, ALLEGRO_COLOR c, bool blocks): x(x),y(y),symbol(symbol), name(name),c(c),blocks(blocks){
}