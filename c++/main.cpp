#include "game.h"
#include <allegro5/allegro_native_dialog.h>
/*
VALUES FOR TILES
0 - EMPTY
1 - SOLID
98 - START OF LEVEL
99 - END OF LEVEL

VALUES FOR TILE IMAGES
0 - EMPTY
1 - FLOOR
2 - CEILING
3 - WALL
99 - DOOR
*/

int main(){
	srand(time(NULL));
	al_init();
	al_init_image_addon();
	al_init_acodec_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_primitives_addon();
	al_install_keyboard();
	al_install_audio();
	al_reserve_samples(2);
	al_set_app_name("Cave Dweller");
	//SteamAPI_Init();
	//if( SteamUser() ){
	//ALLEGRO_DISPLAY *screen = al_create_display(500,500);
		ALLEGRO_DISPLAY_MODE disp;
		al_get_display_mode(al_get_num_display_modes() - 1, &disp);
		al_set_new_display_flags(ALLEGRO_FULLSCREEN);
		ALLEGRO_DISPLAY *screen = al_create_display(disp.width,disp.height);
		al_hide_mouse_cursor(screen); 
	/*int sf = (disp.height / 10) + 1;
	bool exit = false;
	bool show = false;
	ALLEGRO_FONT *f = al_load_font("assets/font/main.ttf",64,0);
	ALLEGRO_FONT *f2 = al_load_font("assets/font/main.ttf",32,0);
	ALLEGRO_COLOR white = al_map_rgb(255,255,255);
	ALLEGRO_TIMER *t = al_create_timer(0.5);
	ALLEGRO_EVENT e;
	ALLEGRO_EVENT_QUEUE *eq;
	eq = al_create_event_queue();
	al_register_event_source(eq, al_get_keyboard_event_source());
	al_register_event_source(eq, al_get_timer_event_source(t));
	al_clear_to_color(al_map_rgb(0,0,0));
	al_draw_text(f,white,(disp.width/2) - (al_get_text_width(f,"GMAE") / 2),100,0,"GMAE");
	al_draw_text(f2,white,(disp.width/2) - (al_get_text_width(f2,"Press any button to begin!") / 2),disp.height - 100, 0,"Press any button to begin!");
	al_flip_display();
	al_start_timer(t);
	while(!exit){
		al_wait_for_event(eq,&e);
		if(e.type == ALLEGRO_EVENT_TIMER){
			al_clear_to_color(al_map_rgb(0,0,0));
			al_draw_text(f,white,(disp.width/2) - (al_get_text_width(f,"GMAE") / 2),100,0,"GMAE");
			if(show){
				al_draw_text(f2,white,(disp.width/2) - (al_get_text_width(f2,"Press any button to begin!") / 2),disp.height - 100, 0,"Press any button to begin!");
			}
			show=!show;
			al_flip_display();
		} else if(e.type==ALLEGRO_EVENT_KEY_DOWN){
			exit = true;
		}
	}
	al_destroy_timer(t);
	al_destroy_font(f);
	al_destroy_font(f2);
	ALLEGRO_BITMAP *heart = al_load_bitmap("assets/sprites/i/Heart.png");
	ALLEGRO_BITMAP *nheart = al_load_bitmap("assets/sprites/i/No Heart.png");
	f = al_load_font("assets/font/main.ttf",sf,0);
	t = al_create_timer(0.1);
	Grass_Stage test(30,sf,disp.width);
	test.draw();
	al_flip_display();
	//Character c = {"Samurai",10,10,10,2,8};
	Player *player = new Player(5,2,2,"Ninja");
	vector<Enemy*> enemies;
	enemies.push_back(new Slime(sf,9,8,0));
	enemies.push_back(new Slime(sf,10,8,1));
	enemies.push_back(new Slime(sf,11,8,2));
	enemies.push_back(new Slime(sf,12,8,3));
	enemies.push_back(new Skeleton(sf,13,8));
	ALLEGRO_SAMPLE *sample = NULL;
	ALLEGRO_SAMPLE_ID *musik = NULL;
	sample = al_load_sample( "assets/music/Battle.wav" );
	ALLEGRO_BITMAP *bg = al_load_bitmap("assets/images/cave.png");
	al_play_sample(sample,1.0,0.0,1.0,ALLEGRO_PLAYMODE_LOOP,musik);
	al_register_event_source(eq, al_get_keyboard_event_source());
	al_register_event_source(eq, al_get_timer_event_source(t));
	al_start_timer(t);
	int d = 0;
	int m = 0;
	bool keydown;
	while(true){
		al_wait_for_event(eq,&e);
		if(e.keyboard.keycode == ALLEGRO_KEY_ESCAPE){
				break;
			}
		if(e.type == ALLEGRO_EVENT_KEY_DOWN&&(player->jump<=0&&!player->falling&&!player->dead)){
			keydown = true;
			if(e.keyboard.keycode == ALLEGRO_KEY_RIGHT){
				m = 1;
				d = 0;
				player->maxStep = 5;
			} else if(e.keyboard.keycode == ALLEGRO_KEY_LEFT){
				m = 1;
				d = 1;
				player->maxStep = 5;
			} else if(e.keyboard.keycode == ALLEGRO_KEY_UP){
				player->jump = 10;
				player->maxStep = 3;
			} else if(e.keyboard.keycode == ALLEGRO_KEY_SPACE){
				m = 3;
				player->maxStep = 2;
			}
			player->step = 0;
		} else if(e.type == ALLEGRO_EVENT_KEY_UP){
			keydown = false;
			if(player->jump<=0&&!player->falling){
				m = 0;
				player->maxStep = 3;
				player->step = 0;
			}
		}else if(e.type == ALLEGRO_EVENT_TIMER){
			int tempm = m;
			if(player->jump>0&&!player->falling){
				if(test.map[player->X][ceil(player->Y) - 1].second != 0){
						player->jump = 0;
				} else {
					player->Y -= 0.15;
					player->jump -= 1;
					tempm = 2;
				}
			} else if(player->jump==0){
				player->falling = true;
			}
			if(player->falling){
				if(test.map[player->X][floor(player->Y) + 1].second != 0){
					player->falling = false;
					if(!keydown){
						m = 0;
						player->maxStep = 3;
					}
					player->step = 0;
					player->jump = -1;
				} else {
					player->Y += 0.15;
				}
			}
			if(m==1){
				if(d==0){
					if(ceil(player->X) == (disp.width / sf)){
						printf("XOFFSET +");
						player->X -= 0.5;
						player->xoffset += 1;
					}
					if(test.map[floor(player->X) + player->xoffset + 1][player->Y].second == 0){
						player->X += 0.25;
					}
				} else {
					if(floor(player->X)==0&&player->xoffset>0){
						player->X += 0.5;
						player->xoffset -= 1;
					}
					if(test.map[ceil(player->X) + player->xoffset - 1][player->Y].second == 0){
						player->X -= 0.25;
					}
				}
			}
			al_clear_to_color(al_map_rgb(0,0,0));
			al_draw_scaled_bitmap(bg,0,0,1000,500,0,0,disp.width,disp.height,0);
			test.draw(player->xoffset);
			al_draw_text(f,white,1,1,0,"Room: 0");
			for(int i =player->max_hp;i>0;i--){
				al_draw_scaled_bitmap(nheart,0,0,32,32,disp.width - (i*sf) + 10,1,sf,sf,0);
				if(player->current_hp>=i){
					al_draw_scaled_bitmap(heart,0,0,32,32,disp.width - (i*sf) + 10,1,sf,sf,0);
				}
			}
			if(!player->dead){
				for(int i=0;i<enemies.size();i++){
					if((((floor(enemies[i]->x) - player->xoffset  == floor(player->X) - 1)&&d==1)||((floor(enemies[i]->x) - player->xoffset == ceil(player->X))&&d==0))&&m==3){
						enemies[i]->current_hp--;
						if(enemies[i]->current_hp==0){
							enemies[i]->ani = 4;
						}
					}
					if(floor(enemies[i]->x) - player->xoffset  == floor(player->X)&&(floor(enemies[i]->y)==floor(player->Y))&&!enemies[i]->dead){
						if(player->hurt<=0){
							player->current_hp -= 1;
							player->hurt = 15;
							if(player->current_hp == 0){
								player->dead = true;
								al_stop_samples();
								Skeleton *dead = new Skeleton(sf,player->X,player->Y);
								dead->ani = 4;
								dead->step = 0;
								dead->maxStep = 9;
								enemies.push_back(dead);
							}
						}
					}
					enemies[i]->AI(test.map,player->xoffset);
				}
				player->draw(tempm,sf,d);
			} else {
				enemies[enemies.size() -1]->draw(player->xoffset);
				if(enemies[enemies.size() -1]->dead){
					al_stop_timer(t);
					al_clear_to_color(al_map_rgb(0,0,0));
					al_draw_text(f,white,((disp.width / 2)-(al_get_text_width(f,"GAME OVER") / 2)),(disp.height / 2) - 32,0,"GAME OVER");
				}
			}
			al_flip_display();
			al_rest(0.01);
		}
	}
	*/
		//SteamUserStats()->SetAchievement("Starting Up");
		//SteamUserStats()->StoreStats();
		//SteamFriends()->ActivateGameOverlay("settings");
		//SideScroller::Game *game = new SideScroller::Game(disp.width,disp.height);
		Roguelike::Game *game = new Roguelike::Game(disp.width,disp.height);
		//Roguelike::Game *game = new Roguelike::Game(500,500);
		al_destroy_display(screen);
	//} else {
	//	al_show_native_message_box(NULL,"Error","","Steam must be running!","Close",0);
	//}
	return 0;
}

