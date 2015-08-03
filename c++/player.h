#ifndef GAME_P
#define GAME_P

#include <vector>
#include <utility>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>

#include "stages.h"
#include "projectile.h"
#include "object.h"
using namespace std;

namespace SideScroller{

class Player{
public:
	Player(int hp,int def,int att,char *type);
	void draw(int sf,bool done=false);
	void move(vector<vector<pair<int,int>>> map,int sf, int width);
	void left();
	void right();
	void idle();
	void melee();
	void ranged();
	int jump;
	bool falling;
	int step;
	int maxStep;
	double X;
	int xoffset;
	double Y;
	bool canJump;
	double dy;
	int base_att;
	int base_def;
	int max_hp;
	int current_hp;
	char *type;
	int hurt;
	bool dead;
	int m;
	int d;
	bool levelComplete;
	float shrink;
	vector<pair<char*,pair<int,int>>> inventory;
	ALLEGRO_BITMAP *sprites;
	Projectile *projectile;
	bool proj;
};

};

namespace Roguelike{



};

#endif