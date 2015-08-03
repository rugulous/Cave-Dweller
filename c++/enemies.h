#ifndef GAME_ENEMIES
#define GAME_ENEMIES

#include <utility>
#include <allegro5/allegro.h>
#include <cmath>
#include <vector>

#include "object.h"
//#include "stages.h"

using namespace std;

namespace SideScroller{

class Enemy{
public:
	Enemy(int sf,double X, double Y);
	virtual void draw(int xo) = 0;
	virtual void AI(vector<vector<pair<int,int>>> map,int xo) = 0;
	int sf;
	double x;
	double y;
	int ani;
	int step;
	int maxStep;
	bool dead;
	int d;
	int max_hp;
	int current_hp;
	ALLEGRO_BITMAP *sprites;
};


class Slime : public Enemy{
public:
	Slime(int sf,double X, double Y);
	Slime(int sf,double X, double Y,int type);
	void draw(int xo);
	void AI(vector<vector<pair<int,int>>> map,int xo);
	int type;
};

class Skeleton : public Enemy{
public:
	Skeleton(int sf,double X,double Y);
	Skeleton(int sf,double X,double Y,bool player);
	void draw(int xo);
	void AI(vector<vector<pair<int,int>>> map,int xo);
};

};

namespace Roguelike{

class Character{
public:
	Character(int x, int y,ALLEGRO_COLOR c,char *name, char *symbol,int hp,int def, int pow);
	int x;
	int y;
	ALLEGRO_COLOR c;
	char *name;
	char *symbol;
	int ani;
	int d;
	int step;
	int maxStep;
	ALLEGRO_BITMAP *base;
};

};

#endif