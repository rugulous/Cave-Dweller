#include "projectile.h"

SideScroller::Projectile::Projectile(char *type,int x,int y,int d):x(x),y(y),d(d){
	char path[50] = "assets/side/sprites/r/";
	strcat(path,type);
	strcat(path,".png");
	this->sprites = al_load_bitmap(path);
	this->step = 0;
	this->maxStep = 13;
}

void SideScroller::Projectile::draw(int sf){
	if(this->d==0){
		this->x += 0.4;
	} else {
		this->x -= 0.4;
	}
	if(this->step==this->maxStep){
		this->step = 0;
	} else {
		this->step++;
	}
	al_draw_scaled_bitmap(this->sprites,(this->step * 30) + 2,1,28,29,(sf*this->x),(sf*this->y)+ (sf/3),sf,sf,this->d);
}