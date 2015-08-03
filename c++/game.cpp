#include "game.h"

#include <iostream>

SideScroller::Game::Game(int width,int height):width(width),height(height){
	this->paused = false;
	this->level = 1;
	this->sf = (this->height / 10) + 1;
	this->heart = al_load_bitmap("assets/side/sprites/i/Heart.png");
	this->nheart = al_load_bitmap("assets/side/sprites/i/No Heart.png");
	this->title = al_load_font("assets/side/font/main.ttf",sf,0);
	this->subtitle = al_load_font("assets/side/font/main.ttf",sf/2,0);
	this->kills = 0;
	this->Menu_Main();
}

void SideScroller::Game::Menu_Main(){
	this->stage = new Grass_Stage((width/sf) + 1,sf,width);
	int index = 0;
	this->white = al_map_rgb(255,255,255);
	int d = 0;
	this->t = al_create_timer(0.1);
	this->eq = al_create_event_queue();
	al_register_event_source(this->eq, al_get_keyboard_event_source());
	al_register_event_source(this->eq, al_get_timer_event_source(this->t));
	//al_draw_scaled_bitmap(this->bg,0,0,al_get_bitmap_width(this->bg),al_get_bitmap_height(this->bg),0,0,this->width,this->height,0);
	this->stage->draw();
	al_draw_text(this->title,white,(this->width/2) - (al_get_text_width(this->title,GAME) / 2),sf,0,GAME);
	al_draw_text(this->subtitle,white,(this->width/2) - (al_get_text_width(this->subtitle,"Play") / 2),sf * 4,0,"Play");
	al_draw_text(this->subtitle,white,(this->width/2) - (al_get_text_width(this->subtitle,"About") / 2),sf * 6,0,"About");
	al_draw_text(this->subtitle,white,(this->width/2) - (al_get_text_width(this->subtitle,"Quit") / 2),sf * 8,0,"Quit");
	al_draw_filled_triangle((this->width/2) - (al_get_text_width(this->subtitle,"Play") / 2) - sf,sf * 4,(this->width/2) - (al_get_text_width(this->subtitle,"Play") / 2) - (sf / 2),sf * 4.25,(this->width/2) - (al_get_text_width(this->subtitle,"Play") / 2) - sf,sf * 4.5,white);
	al_flip_display();
	al_start_timer(t);
	while(true){
		al_wait_for_event(this->eq,&this->e);
		if(e.type == ALLEGRO_EVENT_TIMER){
			if(d<10){
				d++;
			} else {
				d = 0;
			}
//			al_draw_scaled_bitmap(this->bg,0,0,al_get_bitmap_width(this->bg),al_get_bitmap_height(this->bg),0,0,this->width,this->height,0);
			this->stage->draw();
			al_draw_text(this->title,white,(this->width/2) - (al_get_text_width(this->title,GAME) / 2),sf,0,GAME);
			al_draw_text(this->subtitle,white,(this->width/2) - (al_get_text_width(this->subtitle,"Play") / 2),sf * 4,0,"Play");
			al_draw_text(this->subtitle,white,(this->width/2) - (al_get_text_width(this->subtitle,"About") / 2),sf * 6,0,"About");
			al_draw_text(this->subtitle,white,(this->width/2) - (al_get_text_width(this->subtitle,"Quit") / 2),sf * 8,0,"Quit");
			al_draw_filled_triangle((this->width/2) - (al_get_text_width(this->subtitle,"Play") / 2) - sf,sf * 4 + (sf * 2 * index),(this->width/2) - (al_get_text_width(this->subtitle,"Play") / 2) - (sf / 2),sf * 4.25 + (sf * 2 * index),(this->width/2) - (al_get_text_width(this->subtitle,"Play") / 2) - sf,sf * 4.5 + (sf * 2 * index),white);
			al_flip_display();
		} else if(e.type == ALLEGRO_EVENT_KEY_DOWN){
			if(this->e.keyboard.keycode == ALLEGRO_KEY_ENTER){
				if(index==0){
					this->Main();
					this->stage = new Grass_Stage((width/sf) + 1,sf,width);
				} else if(index==1) {
					this->About(0,index);
				} else {
					exit(0);
				}
			} else if(this->e.keyboard.keycode == ALLEGRO_KEY_UP){
				if(index>0){
					index--;
				} else {
					index = 2;
				}
			} else if(this->e.keyboard.keycode == ALLEGRO_KEY_DOWN){
				if(index<2){
					index++;
				} else {
					index = 0;
				}
			}
		}
	}
	al_stop_timer(this->t);
}

void SideScroller::Game::About(int page,int index){
	int d = 0;
	char *text;
	char *title;
	char *left;
	char *right;
	ALLEGRO_BITMAP *l = al_load_bitmap("assets/side/sprites/k/l.png");
	ALLEGRO_BITMAP *r = al_load_bitmap("assets/side/sprites/k/r.png");
	ALLEGRO_BITMAP *esc = al_load_bitmap("assets/side/sprites/k/esc.png");
	switch(page){
	case 1:
		title = "PLAYER ART";
		text = "ALL PLAYER ART WAS DRAWN BY DAVID [DEZRASDRAGONS] AND ISRELEASED UNDER PUBLIC DOMAIN[CREATIVE COMMONS 0]";
		left = " About";
		right = "Enemy Art ";
		break;
	case 2:
		title = "ENEMY ART";
		text = "ALL ENEMY ART WAS DRAWN BY  CALLUM [CALCIUMTRICE] AND ISRELEASED UNDER PUBLICDOMAIN [CREATIVE COMMONS 3.0]";
		left = " Player Art";
		right = "Stage Art ";
		break;
	case 3:
		title = "STAGE ART";
		text = "GRASS AND STONE STAGE ART BYHANNES [SOGOMN] UNDER PUBLIC DOMAIN[CREATIVE COMMONS 0]";
		left = " Enemy Art";
		right = "Misc Art ";
		break;
	case 4:
		title = "MISC ART";
		text = "HEARTS BY ... [CC], KEYS BY		";
		left = " Stage Art";
		right = "Sources ";
		break;
	case 5:
		title = "SOURCES";
		text = "ALL ART CAN BE FOUND IN ITS ORIGINAL FORM AT            [HTTP://OPENGAMEART.ORG].   CREATIVE COMMONS:           [HTTP://CREATIVECOMMONS.ORG]";
		left = " Misc Art";
		right = NULL;
		break;
	default:
		title = "ABOUT";
		text = "CAVE DWELLER COPYRIGHT LUKE TAYLOR 2015. ASSETS FROM    VARIOUS ARTISTS UNDER       CREATIVE COMMONS.";
		left = NULL;
		right = "Player Art ";
	}
	while(true){
		al_wait_for_event(this->eq,&this->e);
		if(this->e.type == ALLEGRO_EVENT_TIMER){
			if(d<10){
				d++;
			} else {
				d = 0;
			}
//			al_draw_scaled_bitmap(this->bg,0,0,al_get_bitmap_width(this->bg),al_get_bitmap_height(this->bg),0,0,this->width,this->height,0);
			this->stage->draw();
			al_draw_text(this->title,white,(this->width/2) - (al_get_text_width(this->title,GAME) / 2),sf,0,GAME);
			al_draw_text(this->subtitle,white,(this->width/2) - (al_get_text_width(this->subtitle,"Play") / 2),sf * 4,0,"Play");
			al_draw_text(this->subtitle,white,(this->width/2) - (al_get_text_width(this->subtitle,"About") / 2),sf * 6,0,"About");
			al_draw_text(this->subtitle,white,(this->width/2) - (al_get_text_width(this->subtitle,"Quit") / 2),sf * 8,0,"Quit");
			al_draw_filled_triangle((this->width/2) - (al_get_text_width(this->subtitle,"Play") / 2) - sf,sf * 4 + (sf * 2 * index),(this->width/2) - (al_get_text_width(this->subtitle,"Play") / 2) - (sf / 2),sf * 4.25 + (sf * 2 * index),(this->width/2) - (al_get_text_width(this->subtitle,"Play") / 2) - sf,sf * 4.5 + (sf * 2 * index),white);
			al_draw_filled_rectangle(this->sf * 2,this->sf * 2,this->width - (this->sf * 2),this->height - (this->sf * 0.8),al_map_rgb(255,255,255));
			al_draw_text(this->subtitle,al_map_rgb(0,0,0),this->width - (this->sf * 2) - al_get_text_width(this->subtitle,title),this->sf * 2.5f,0,title);
			al_draw_scaled_bitmap(esc,0,0,50,50,this->sf * 2,this->sf * 2,sf,sf,0);
			al_draw_text(this->subtitle,al_map_rgb(192,192,192),this->sf * 3,this->sf * 2.25,0," Close");
			al_draw_line(this->sf * 2,this->sf * 3,this->width - (this->sf * 2),this->sf * 3,al_map_rgb(192,192,192),10);
			int xcoord = this->sf * 2;
			int ycoord = this->sf * 2.5;
			int index = 0;
			char temp;
			for(int i = 0;i<=strlen(text)/20;i++){
				ycoord+=this->sf;
				xcoord = this->sf * 2;
				while(xcoord<this->width - (this->sf * 2)){
					if(index<strlen(text)){
						temp = text[index];
						temp = text[index];
						al_draw_text(this->subtitle,al_map_rgb(0,0,0),xcoord, ycoord,0,&temp);
						xcoord+= al_get_text_width(this->subtitle,&temp);
						index++;
					} else {
						xcoord = 500000;
					}
				}
			}
			if(left!=NULL){
				al_draw_scaled_bitmap(l,0,0,50,50,this->sf * 2,this->sf * 8.2,sf,sf,0);
				al_draw_text(this->subtitle,al_map_rgb(192,192,192),this->sf * 3,this->sf * 8.45,0,left);
			}
			if(right!=NULL){
				al_draw_scaled_bitmap(r,0,0,50,50,this->width - (this->sf * 3),this->sf * 8.2,this->sf,this->sf,0);
				al_draw_text(this->subtitle,al_map_rgb(192,192,192),this->width - (this->sf * 3) - al_get_text_width(this->subtitle,right),this->sf * 8.45,0,right);
			}
		//al_draw_text(this->subtitle,al_map_rgb(0,0,0),this->sf * 2, this->sf * 3.5,0,text);
			al_flip_display();
		} else if(this->e.type == ALLEGRO_EVENT_KEY_DOWN){
			if(this->e.keyboard.keycode == ALLEGRO_KEY_LEFT){
				l = al_load_bitmap("assets/side/sprites/k/lp.png");
			} else if(this->e.keyboard.keycode == ALLEGRO_KEY_RIGHT){
				r = al_load_bitmap("assets/side/sprites/k/rp.png");
			} else if(this->e.keyboard.keycode == ALLEGRO_KEY_ESCAPE){
				esc = al_load_bitmap("assets/side/sprites/k/escp.png");
			}
		} else if(this->e.type == ALLEGRO_EVENT_KEY_UP){
			if(this->e.keyboard.keycode == ALLEGRO_KEY_LEFT&&left!=NULL){
				this->About(page - 1);
				break;
			} else if(this->e.keyboard.keycode == ALLEGRO_KEY_RIGHT&&right!=NULL){
				this->About(page + 1);
				break;
			} else if(this->e.keyboard.keycode == ALLEGRO_KEY_ESCAPE){
				break;
			}
		}
	}
}

void SideScroller::Game::Main(){
	this->player = new Player(3,3,3,"Ninja");
	this->stage = this->New_Stage();
	al_start_timer(t);
//	al_draw_scaled_bitmap(this->bg,0,0,1000,500,0,0,this->width,this->height,0);
	this->stage->draw(this->player->xoffset);
	this->Main_draw_panel();
	this->player->draw(this->sf);
	al_flip_display();
	while(true){
		al_wait_for_event(this->eq,&this->e);
		if(this->e.type == ALLEGRO_EVENT_KEY_DOWN){
			if(this->e.keyboard.keycode == ALLEGRO_KEY_ESCAPE){
				this->Main_pause();
			}
			if(!this->player->levelComplete){
				if(this->e.keyboard.keycode == ALLEGRO_KEY_LEFT){
					this->player->left();
				} 
				if(this->e.keyboard.keycode == ALLEGRO_KEY_RIGHT){
					this->player->right();
				} 
				if(this->e.keyboard.keycode == ALLEGRO_KEY_UP){
					if(this->player->canJump){
						this->player->jump = 3;
					}
				}
				if(this->e.keyboard.keycode == ALLEGRO_KEY_X){
					this->player->melee();
				} 
				if(this->e.keyboard.keycode == ALLEGRO_KEY_Z){
					this->player->ranged();
				}
				if(this->e.keyboard.keycode == ALLEGRO_KEY_SPACE){
					cout << "Saving screenshot... " << endl;
					this->screenshot(NULL,NULL);
				}
			}
				this->player->step = 0;
		} else if(this->e.type == ALLEGRO_EVENT_KEY_UP){
			this->player->idle();
		} else if(this->e.type == ALLEGRO_EVENT_TIMER){
			if(this->player->shrink>=4){
				this->stage = this->New_Stage();
				this->player->xoffset = 0;
				this->player->X = 0.0;
				this->player->Y = 6.0;
				this->level++;
				this->player->shrink = 0;
				this->player->levelComplete = false;
			}
			//al_draw_scaled_bitmap(this->bg,0,0,1000,500,0,0,this->width,this->height,0);
			this->stage->draw(this->player->xoffset,this->player->dead,this->player->levelComplete);
			if(!player->dead){
				this->Main_draw_panel();
				this->player->move(this->stage->map,this->sf,this->width);
				this->player->draw(this->sf,this->stage->levelComplete);
				this->Hit_detect();
			} else {
				this->stage->enemies[this->stage->enemies.size() -1]->draw(this->player->xoffset);
				if(this->stage->enemies[this->stage->enemies.size() -1]->dead){
					//al_stop_timer(this->t);
					al_clear_to_color(al_map_rgb(0,0,0));
					al_draw_text(this->title,this->white,((this->width / 2)-(al_get_text_width(this->title,"GAME OVER") / 2)),(this->height / 2) - this->sf,0,"GAME OVER");
					al_flip_display();
					al_rest(3);
					return;
				}
			}
			al_flip_display();
		}
	}
}

void SideScroller::Game::Main_draw_panel(){
	char room[8] = "Room ";
	char roomno[3];
	_itoa(this->level,roomno,10);
	strcat(room,roomno);
	al_draw_text(this->title,this->white,1,1,0,room);
	for(int i =this->player->max_hp;i>0;i--){
			al_draw_scaled_bitmap(this->nheart,0,0,32,32,this->width - (i*this->sf) + 10,1,this->sf,this->sf,0);
			if(this->player->current_hp>=i){
				al_draw_scaled_bitmap(this->heart,0,0,32,32,this->width - (i*this->sf) + 10,1,this->sf,this->sf,0);
			}
		}
}

void SideScroller::Game::Main_pause(){
	this->paused = !this->paused;
		if(this->paused){
			al_stop_timer(this->t);
			al_draw_text(this->title,this->white,((this->width / 2) - (al_get_text_width(this->title,"PAUSED") / 2)),this->sf,0,"PAUSED");
			al_flip_display();
		} else {
			al_start_timer(this->t);
		}
}

void SideScroller::Game::Hit_detect(){
	if(this->player->proj&&(((this->player->projectile->x>=(this->width /sf)+1)||this->player->projectile->x<=0)||(this->stage->WallAt(this->player->projectile->x,this->player->projectile->y)))){
		this->player->proj = false;
		this->player->projectile = NULL;
	}
	for(int i=0;i<this->stage->enemies.size();i++){
		if(!this->stage->enemies[i]->dead){
			if(this->player->proj&&(floor(this->player->projectile->x) == (floor(this->stage->enemies[i]->x)-this->player->xoffset) && floor(this->player->projectile->y) == floor(this->stage->enemies[i]->y))){
				this->player->proj = false;
				this->player->projectile = NULL;
				this->stage->enemies[i]->current_hp-=1;
				if(this->stage->enemies[i]->current_hp <= 0){
					this->stage->enemies[i]->ani = 4;
					this->kills++;
				}
			} else if((floor(this->stage->enemies[i]->x) - this->player->xoffset ==floor(this->player->X))&&(floor(this->stage->enemies[i]->y)==floor(this->player->Y))){
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
						this->stage->enemies.push_back(dead);
					}
				}
			}
		}
	}
}

SideScroller::Stage* SideScroller::Game::New_Stage(int type){
	if(type==NULL){
		type = (rand()%2);
	}
	if(type == 0){
		return new Grass_Stage(30,this->sf,this->width);
	} else {
		return new Stone_Stage(30,this->sf,this->width);
	}
}

int SideScroller::Game::screenshot(const char *destination_path, const char *gamename){
		ALLEGRO_PATH *path;
	char *filename, *filename_wp;
	struct tm *tmp;
	time_t t;
	unsigned int i;
	const char *path_cstr;
 
	if(!destination_path)
		path = al_get_standard_path(ALLEGRO_USER_DOCUMENTS_PATH);
	else
		path = al_create_path_for_directory(destination_path);
 
	if(!path)
		return -1;
 
	if(!gamename) {
		if( !(gamename = al_get_app_name()) ) {
			al_destroy_path(path);
			return -2;
		}
	}
 
	t = time(0);
	tmp = localtime(&t);
	if(!tmp) {
		al_destroy_path(path);
		return -3;
	}
 
	// Length of gamename + length of "-YYYYMMDD" + length of maximum [a-z] + NULL terminator
	if ( !(filename_wp = filename = (char *)malloc(strlen(gamename) + 9 + 2 + 1)) ) {
		al_destroy_path(path);
		return -4;
	}
 
	strcpy(filename, gamename);
	// Skip to the '.' in the filename, or the end.
	for(; *filename_wp != '.' && *filename_wp != 0; ++filename_wp);
 
	*filename_wp++ = '-';
	if(strftime(filename_wp, 9, "%Y%m%d", tmp) != 8) {
		free(filename);
		al_destroy_path(path);
		return -5;
	}
	filename_wp += 8;
 
	for(i = 0; i < 26*26; ++i) {
		if(i > 25) {
			filename_wp[0] = (i / 26) + 'a';
			filename_wp[1] = (i % 26) + 'a';
			filename_wp[2] = 0;
		}
		else {
			filename_wp[0] = (i % 26) + 'a';
			filename_wp[1] = 0;
		}
 
		al_set_path_filename(path, filename);
		al_set_path_extension(path, ".png");
		path_cstr = al_path_cstr(path, ALLEGRO_NATIVE_PATH_SEP);
 
		if (al_filename_exists(path_cstr))
			continue;
 
		al_save_bitmap(path_cstr, al_get_target_bitmap());
		free(filename);
		al_destroy_path(path);
		return 0;
	}
 
	free(filename);
	al_destroy_path(path);
 
	return -6;
}

Roguelike::Game::Game(int width,int height) : width(width),height(height){
	this->panel_sfx = this->width / 160;
	this->panel_sfy = this->height / 90;
	this->panel_x = (this->width / 160) * 80;
	this->sf = this->height / 10;
	this->f = al_load_font("assets/side/font/main.ttf",this->panel_sfx,0);
	this->sprites = al_load_bitmap("assets/rogue/sprites/ground.png");
	this->dark_wall = al_map_rgb(0,0,100);
	this->light_wall = al_map_rgb(130,110,50);
	this->dark_ground = al_map_rgb(50,50,150);
	this->light_ground = al_map_rgb(200,180,50);
	this->show_panel = false;
	this->player = new Character(0,0,al_map_rgb(255,255,255),"Player","@",1,2,3);
	this->t = al_create_timer(0.1);
	this->eq = al_create_event_queue();
	al_register_event_source(this->eq,al_get_timer_event_source(this->t));
	this->make_map();
	this->gameloop();
};

void Roguelike::Game::gameloop(){
	al_register_event_source(this->eq,al_get_keyboard_event_source());
	while(true){
		this->calculate_FOV();
		al_clear_to_color(al_map_rgb(50,33,37));
		this->draw_main();
		if(this->show_panel){
			this->draw_panel();
		}
		this->draw_enemies();
		al_flip_display();
		al_wait_for_event(this->eq,&this->e);
		if(this->e.type == ALLEGRO_EVENT_KEY_DOWN){
			handle_keys(this->e.keyboard.keycode);
		}
	}
}

void Roguelike::Game::handle_keys(int key){
	if(key == ALLEGRO_KEY_UP){
		this->player->d = 0;
		this->move(this->player,0,-1);
	} else if(key == ALLEGRO_KEY_DOWN){
		this->player->d = 2;
		this->move(this->player,0,1);
	} else if(key == ALLEGRO_KEY_LEFT){
		this->player->d = 1;
		this->move(this->player,-1,0);
	} else if(key == ALLEGRO_KEY_RIGHT){
		this->player->d = 3;
		this->move(this->player,1,0);
	} else if(key == ALLEGRO_KEY_M){
		this->show_panel = !this->show_panel;
	}
}

void Roguelike::Game::draw_main(){
	for(int y = 0; y < 10; y++){
		if(this->player->y - 5 + y<0){
			continue;
		}
		for(int x = 0; x < (this->width / sf) + 1; x++){
			if(this->player->x - ((this->width / sf)/2) + x<0||this->player->x - ((this->width / sf)/2) + x>80){
				continue;
			}
			try{
				if(this->map.at(this->player->x - ((this->width / sf)/2) + x).at(this->player->y - 5 + y)->visible){
					if(this->map.at(this->player->x - ((this->width / sf)/2) + x).at(this->player->y - 5 + y)->blocked){
						if(!this->map.at(this->player->x - ((this->width / sf)/2) + x).at(this->player->y - 5 + y - 1)->blocked){ //if bottom of cell
							if(!this->map.at(this->player->x - ((this->width / sf)/2) + x - 1).at(this->player->y - 5 + y)->blocked){
								al_draw_scaled_bitmap(this->sprites,40,80,40,40,x * sf,y  * sf,this->sf,this->sf,0); //wall ne_out
							} else if(!this->map.at(this->player->x - ((this->width / sf)/2) + x + 1).at(this->player->y - 5 + y)->blocked){
								al_draw_scaled_bitmap(this->sprites,80,80,40,40,x * sf,y  * sf,this->sf,this->sf,0); //wall nw_out
							} else {
								al_draw_scaled_bitmap(this->sprites,120,0,40,40,x * sf,y  * sf,this->sf,this->sf,0); //wall s
							}
						} else if(!this->map.at(this->player->x - ((this->width / sf)/2) + x).at(this->player->y - 5 + y + 1)->blocked){ //if top of cell
							if(!this->map.at(this->player->x - ((this->width / sf)/2) + x - 1).at(this->player->y - 5 + y)->blocked){
								al_draw_scaled_bitmap(this->sprites,160,0,40,40,x * sf,y  * sf,this->sf,this->sf,0); //wall se_out
							} else if(!this->map.at(this->player->x - ((this->width / sf)/2) + x + 1).at(this->player->y - 5 + y)->blocked){
								al_draw_scaled_bitmap(this->sprites,160,40,40,40,x * sf,y  * sf,this->sf,this->sf,0); //wall sw_out
							} else {
								al_draw_scaled_bitmap(this->sprites,40,40,40,40,x * sf,y  * sf,this->sf,this->sf,0); //wall n
							}
						} else if(!this->map.at(this->player->x - ((this->width / sf)/2) + x + 1).at(this->player->y - 5 + y)->blocked){
							al_draw_scaled_bitmap(this->sprites,200,0,40,40,x * sf,y  * sf,this->sf,this->sf,0); //wall w
						} else if(!this->map.at(this->player->x - ((this->width / sf)/2) + x - 1).at(this->player->y - 5 + y)->blocked){
							al_draw_scaled_bitmap(this->sprites,0,40,40,40,x * sf,y  * sf,this->sf,this->sf,0); //wall e
						} else if(!this->map.at(this->player->x - ((this->width / sf)/2) + x - 1).at(this->player->y - 5 + y - 1)->blocked){
							al_draw_scaled_bitmap(this->sprites,120,40,40,40,x * sf,y  * sf,this->sf,this->sf,0); //wall se
						} else if(!this->map.at(this->player->x - ((this->width / sf)/2) + x + 1).at(this->player->y - 5 + y - 1)->blocked){
							al_draw_scaled_bitmap(this->sprites,120,80,40,40,x * sf,y  * sf,this->sf,this->sf,0); //wall sw
						} else if(!this->map.at(this->player->x - ((this->width / sf)/2) + x - 1).at(this->player->y - 5 + y + 1)->blocked){
							al_draw_scaled_bitmap(this->sprites,0,80,40,40,x * sf,y  * sf,this->sf,this->sf,0); //wall ne
						} else if(!this->map.at(this->player->x - ((this->width / sf)/2) + x + 1).at(this->player->y - 5 + y + 1)->blocked){
							al_draw_scaled_bitmap(this->sprites,80,40,40,40,x * sf,y  * sf,this->sf,this->sf,0); //wall nw
						}
					} else {
						if(this->map.at(this->player->x - ((this->width / sf)/2) + x).at(this->player->y - 5 + y)->lit){
							al_draw_scaled_bitmap(this->sprites,40,0,40,40,x * sf,y  * sf,this->sf,this->sf,0);
						} else {
							al_draw_scaled_bitmap(this->sprites,0,0,40,40,x * sf,y  * sf,this->sf,this->sf,0);
						}
					}
				}
			} catch(...){}
		}
	}
	al_draw_scaled_bitmap(this->player->base,this->player->step * 64,(this->player->d * 64) + (this->player->ani * 256),64,64,(this->width / 2) - this->sf,(this->height / 2),this->sf,this->sf,0);
}

void Roguelike::Game::draw_panel(){
	for(int x = 0; x <= 80; x++){
		for(int y = 0; y <= 45; y ++){
			if(this->map[x][y]->lit){
				if(this->map[x][y]->block_sight){
					al_draw_filled_rectangle((x * this->panel_sfx) + this->panel_x,y * this->panel_sfy,((x + 1) * this->panel_sfx) + this->panel_x,(y+1) * this->panel_sfy,this->light_wall);
				} else {
					al_draw_filled_rectangle((x * this->panel_sfx) + this->panel_x,y * this->panel_sfy,((x + 1) * this->panel_sfx) + this->panel_x,(y+1) * this->panel_sfy,this->light_ground);
				}
			}  else {
				if(this->map[x][y]->visible){
					if(this->map[x][y]->block_sight){
						al_draw_filled_rectangle((x * this->panel_sfx) + this->panel_x,y * this->panel_sfy,((x + 1) * this->panel_sfx) + this->panel_x,(y+1) * this->panel_sfy,this->dark_wall);
					} else {
						al_draw_filled_rectangle((x * this->panel_sfx) + this->panel_x,y * this->panel_sfy,((x + 1) * this->panel_sfx) + this->panel_x,(y+1) * this->panel_sfy,this->dark_ground);
					}
				}
			}
		}
	}
	al_draw_text(this->f,this->player->c,(this->player->x * this->panel_sfx) + this->panel_x,this->player->y * this->panel_sfy,0,this->player->symbol);
}

void Roguelike::Game::draw_enemies(){
	for(int y = 0; y < 10; y++){
		if(this->player->y - 5 + y<0){
			continue;
		}
		for(int x = 0; x < (this->width / sf) + 1; x++){
			if(this->player->x - ((this->width / sf)/2) + x<0||this->player->x - ((this->width / sf)/2) + x>80){
				continue;
			}
			for(int i = 0; i < enemies.size(); i++){
				if(this->is_visible(this->player->x - ((this->width / sf)/2) + x,this->player->y - 5 + y)&&this->enemies[i]->x == this->player->x - ((this->width / sf)/2) + x && this->enemies[i]->y == this->player->y - 5 + y){
					al_draw_scaled_bitmap(this->enemies[i]->base,this->enemies[i]->step * 64,(this->enemies[i]->d * 64) + (this->enemies[i]->ani * 256),64,64,x * this->sf,y * this->sf,this->sf,this->sf,0);
					if(this->show_panel){
						al_draw_text(this->f,this->enemies[i]->c,(this->enemies[i]->x * this->panel_sfx) + this->panel_x,this->enemies[i]->y * this->panel_sfy,0,this->enemies[i]->symbol);
					}
				}
			}
		}
	}
}


void Roguelike::Game::calculate_FOV(){
	for(int x = 0; x < 80; x++){
		for(int y = 0; y < 45; y++){
			this->map[x][y]->lit = false;
		}
	}
	for(int i = 0; i < 360; i++){
		float ax = sin(i);
		float ay = cos(i);
		float y = this->player->y;
		float x = this->player->x;
		for(int j = 0; j<10;j++){
			x += ax;
			y += ay;
			if(x<0 || y<0 || x>80 || y>45){
				break;
			}
			this->map[x][y]->lit = true;
			this->map[x][y]->visible = true;
			if(this->map[x][y]->block_sight){
				break;
			}
		}
	}
}

bool Roguelike::Game::create_room(Rect *room){
	for(int x = room->x1 + 1; x < room->x2; x++){
		for(int y = room->y1 + 1; y < room ->y2; y++){
			try{
				this->map.at(x).at(y)->blocked = false;
				this->map.at(x).at(y)->block_sight = false;
			} catch(...){
				return false;
			}
		}
	}
	return true;
}

void Roguelike::Game::create_h_tunnel(int x1, int x2, int y){
	for(int x = min(x1,x2); x <= max(x1,x2); x++){
		this->map[x][y]->blocked = false;
		this->map[x][y]->block_sight = false;
	}
}

void Roguelike::Game::create_v_tunnel(int y1, int y2, int x){
	for(int y = min(y1,y2); y <= max(y1,y2); y++){
		this->map[x][y]->blocked = false;
		this->map[x][y]->block_sight = false;
	}
}

void Roguelike::Game::make_map(){
	this->map.resize(81);
	for(int x = 0; x<81;x++){
		this->map[x].resize(46);
		for(int y=0;y<46;y++){
			this->map[x][y] = new Tile(true);
		}
	}
	vector<Rect*> rooms;
	int num_rooms = 0;
	for(int r = 0; r < 30; r++){
		int w = (rand() % (10 - 6)) + 6;
		int h = (rand() % (10 - 6)) + 6;
		int x = (rand() % (79 - w - 1)) + w - 5;
		while(x <= 0 || x + w >=79){
			x = (rand() % (79 - w - 1)) + w - 5;
		}
		int y = (rand() % (44- h - 1)) + h - 5;
		while(y <= 0||y + w >= 44){
			y = (rand() % (44 - h - 1)) + h - 5;
		}
		Rect *new_room = new Rect(x,y,w,h);
		bool failed = false;
		for(int i = 0; i < num_rooms; i++){
			if(new_room->intersect(rooms[i])){
				failed = true;
				break;
			}
		}
		if(!failed){
			if(this->create_room(new_room)){
				this->place_objects(new_room);
				pair<int,int> newpos = new_room->center();
				if(num_rooms == 0){
					this->player->x = newpos.first;
					this->player->y = newpos.second;
				} else {
					pair<int,int> prevpos = rooms[num_rooms - 1]->center();
					if(rand() % 2 == 1){
						this->create_h_tunnel(prevpos.first,newpos.first,prevpos.second);
						this->create_v_tunnel(prevpos.second,newpos.second,newpos.first);
					} else {
						this->create_v_tunnel(prevpos.second,newpos.second,prevpos.first);
						this->create_h_tunnel(prevpos.first,newpos.first,newpos.second);
					}
				}
				rooms.push_back(new_room);
				num_rooms++;
			}
		}
	}
}

void Roguelike::Game::place_objects(Rect *room){
	int num_monsters = (rand() % 4) + 1;
	for(int i = 0; i <= num_monsters; i++){
		int x = room->x1 + 1 + (rand() % (room->x2 - room->x1));
		int y = room->y1 + 1 + (rand() % (room->y2 - room->y1));
		if(!is_blocked(x,y)){
			if(rand() % 100 < 80){
				this->enemies.push_back(new Character(x,y,al_map_rgb(255,255,255),"Skeleton","s",0,0,0));
			//} else {
			//	this->enemies.push_back(new Character(x,y,al_map_rgb(0,63,0),"Troll","T",0,0,0));
			}
		}
	}
}

void Roguelike::Game::move(Character *c, int dx, int dy){
	if(c->step < c->maxStep){
		c->step++;
	} else {
		c->step = 0;
	}
	if(!this->is_blocked(c->x + dx,c->y + dy)){
		c->x += dx;
		c->y += dy;
	}
}

bool Roguelike::Game::is_blocked(int x, int y){
	if(this->map[x][y]->blocked){
		return true;
	}
	for(int i = 0; i < enemies.size(); i++){
		if(enemies[i]->x == x && enemies[i]->y == y){
			return true;
		}
	}
	return false;
}

bool Roguelike::Game::is_visible(int x, int y){
	return this->map[x][y]->lit;
}
