#ifndef GAME_OBJ
#define GAME_OBJ

#include <allegro5/allegro.h>

namespace Roguelike{

class Object{
public:
	Object(int x, int y, char *symbol, char *name, ALLEGRO_COLOR c, bool blocks = false);
	float x;
	float y;
	char *name;
	char *symbol;
	ALLEGRO_COLOR c;
	bool blocks;
};

};

#endif