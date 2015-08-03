#ifndef GAME
#define GAME "Cave Dweller"

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <steam/steam_api.h>
#include <cmath>

#include "Player.h"
#include "stages.h"
#include "enemies.h"

namespace SideScroller{

class Game{
public:
	Game(int width,int height);
	void Menu_Main();
	void About(int page=0,int index=0);
	void Main();
	void Main_draw_panel();
	void Main_pause();
	void Hit_detect();
	Stage* New_Stage(int type=NULL);
	int screenshot(const char *destination_path, const char *gamename);
	bool paused;
	int width;
	int height;
	int level;
	int kills;
	int sf;
	Player *player;
	Stage *stage;
	ALLEGRO_COLOR white;
	ALLEGRO_BITMAP *heart;
	ALLEGRO_BITMAP *nheart;
	ALLEGRO_FONT *title;
	ALLEGRO_FONT *subtitle;
	ALLEGRO_TIMER *t;
	ALLEGRO_EVENT e;
	ALLEGRO_EVENT_QUEUE *eq;
};

};

namespace Roguelike{

class Game{
public:
	Game(int width,int height);
	void gameloop();
	void handle_keys(int key);
	void draw_main();
	void draw_panel();
	void draw_enemies();
	void calculate_FOV();
	bool create_room(Rect *room);
	void create_h_tunnel(int x1, int x2, int y);
	void create_v_tunnel(int y1, int y2, int x);
	void make_map();
	void place_objects(Rect *room);
	void move(Character *c,int dx, int dy);
	bool is_blocked(int x, int y);
	bool is_visible(int x, int y);
	bool show_panel;
	int width;
	int height;
	int sf;
	int panel_x;
	int panel_sfx;
	int panel_sfy;
	Character *player;
	vector<vector<Tile*>> map;
	vector<Object*> objects;
	vector<Character*> enemies;
	ALLEGRO_FONT *f;
	ALLEGRO_COLOR dark_wall;
	ALLEGRO_COLOR light_wall;
	ALLEGRO_COLOR dark_ground;
	ALLEGRO_COLOR light_ground;
	ALLEGRO_EVENT e;
	ALLEGRO_EVENT_QUEUE *eq;
	ALLEGRO_BITMAP *sprites;
	ALLEGRO_TIMER *t;
};

};

#endif