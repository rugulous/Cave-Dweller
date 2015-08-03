#include "enemies.h"


SideScroller::Enemy::Enemy(int sf,double X,double Y):sf(sf),x(X),y(Y){
	this->d = 0; //0 = left, 1 = right//
	this->step = 0;
	this->ani = 1;
	this->dead = false;
}

SideScroller::Slime::Slime(int sf,double X, double Y):Enemy(sf,X,Y){
	this->sprites = al_load_bitmap("assets/side/sprites/e/slime.png");
	this->maxStep = 9;
	this->type = rand() % 4;
	this->max_hp = 1;
	this->current_hp = 1;
}

SideScroller::Slime::Slime(int sf,double X, double Y, int type):Enemy(sf,X,Y){
	this->sprites = al_load_bitmap("assets/side/sprites/e/slime.png");
	this->maxStep = 9;
	this->type = type;
	this->max_hp = 1;
	this->current_hp = 1;
}

void SideScroller::Slime::draw(int xo){
	al_draw_scaled_bitmap(this->sprites,(this->step * 32),(this->type * 160)+(this->ani*32),32,32,(this->x - xo) * sf,(this->y * sf) ,sf,sf,this->d);
	if(this->step == this->maxStep){
		if(!this->dead){
			if(this->ani == 4){
				this->dead = true;
			} else {
				this->step = 0;
			}
		}
	} else {
		this->step++;
	}
}

void SideScroller::Slime::AI(vector<vector<pair<int,int>>> map,int xo){
	if(this->ani == 1){
		if(this->d == 0){
			if(map[ceil(this->x) - 1][this->y].second == 0){
				this->x -= 0.1;
			} else {
				this->d = 1;
			}
		} else {
			if(map[floor(this->x) + 1][this->y].second == 0){
				this->x += 0.1;
			} else {
				this->d = 0;
			}
		}
	}
	this->draw(xo);
}

SideScroller::Skeleton::Skeleton(int sf,double X,double Y) : Enemy(sf,X,Y){
	this->sprites = al_load_bitmap("assets/side/sprites/e/Skeleton.png");
	this->max_hp = 2;
	this->current_hp = 2;
	this->ani = 2;
	this->maxStep = 9;
	this->d = 1;
}

void SideScroller::Skeleton::draw(int xo){
al_draw_scaled_bitmap(this->sprites,(this->step * 32),(this->ani*32),32,32,(this->x - xo) * sf,(this->y * sf) ,sf,sf,this->d);
	if(this->step == this->maxStep){
		if(!this->dead){
			if(this->ani == 4){
				this->dead = true;
			} else {
				this->step = 0;
			}
		}
	} else {
		this->step++;
	}
}

void SideScroller::Skeleton::AI(vector<vector<pair<int,int>>> map,int xo){
if(this->ani == 2){
		if(this->d == 1){
			if(map[ceil(this->x) - 1][this->y].second == 0){
				this->x -= 0.1;
			} else {
				this->d = 0;
			}
		} else {
			if(map[floor(this->x) + 1][this->y].second == 0){
				this->x += 0.1;
			} else {
				this->d = 1;
			}
		}
	}
	this->draw(xo);
}

Roguelike::Character::Character(int x, int y,ALLEGRO_COLOR c,char *name, char *symbol,int hp,int def, int pow) : x(x),y(y),c(c),name(name),symbol(symbol){
	char path[100];
	strcpy(path,"assets/rogue/sprites/base/");
	strcat(path,name);
	strcat(path,".png");
	this->base = al_load_bitmap(path);
	this->step = 0;
	this->maxStep = 8;
	this->ani = 1;
	this->d = 2;
}
