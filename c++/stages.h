#ifndef GAME_STAGES
#define GAME_STAGES

#include <vector>
#include <utility>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include "enemies.h"
using namespace std;

namespace SideScroller{

class Stage{
public:
	Stage(int width, int sf,int ds);
	void draw(int xoffset=0,bool dead=false,bool levelComplete=false);
	void GenerateMap();
	void GenerateEnemies(int type=1);
	bool EnemyAt(int x,int y);
	bool WallAt(int x,int y);
	vector<vector<pair<int,int>>> map;
	vector<Enemy*> enemies;
	int width;
	int sf;
	int dispSize;
	float dStepS;
	float dStepE;
	char *size;
	bool levelComplete;
	ALLEGRO_BITMAP *spritesheet;
	ALLEGRO_BITMAP *doors;
	ALLEGRO_BITMAP *bg;
};

class Grass_Stage: public Stage{
public:
	Grass_Stage(int width,int sf,int ds);
};

class Stone_Stage: public Stage{
public:
	Stone_Stage(int width,int sf,int ds);
};

};

namespace Roguelike{

class Tile{
public:
	Tile(bool blocked,bool block_sight=NULL);
	bool blocked;
	bool block_sight;
	bool lit;
	bool visible;
};

class Rect{
public:
	Rect(int x, int y, int w, int h);
	pair<int,int> center();
	bool intersect(Rect *other);
	int x1;
	int x2;
	int y1;
	int y2;
};

};

#endif