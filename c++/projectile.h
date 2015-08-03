#ifndef GAME_PROJECTILE
#define GAME_PROJECTILE

#include <allegro5/allegro.h>

namespace SideScroller{

class Projectile{
public:
	Projectile(char *type, int x, int y,int d);
	void draw(int sf);
	int step;
	int maxStep;
	double x;
	double y;
	int d;
	ALLEGRO_BITMAP *sprites;
};

};

#endif