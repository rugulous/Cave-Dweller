#include "Player.h"
#include <iostream>

SideScroller::Player::Player(int hp,int def,int att,char *type): max_hp(hp), current_hp(hp), base_def(def), base_att(att), type(type){
	this->levelComplete = false;
	char path[50] = "assets/side/sprites/c/";
	strcat(path,type);
	strcat(path,".png");
	this->sprites = al_load_bitmap(path);
	this->maxStep = 3;
	this->step = 0;
	this->jump = -1;
	this->X = 0.0;
	this->Y = 6.0;
	this->falling = false;
	this->xoffset = 0;
	this->hurt = 0;
	this->dead = false;
	this->m = 0;
	this->d = 0;
	this->proj = false;
	this->dy = 0;
	this->shrink = 0;
}

void SideScroller::Player::draw(int sf,bool done){
	if(!done){
		if(!this->falling&&this->jump<=0){
			if(this->step==this->maxStep){
				this->step = 0;
			} else {
				this->step++;
			}
		} else {
			if(this->step < 2){
				this->step++;
			} else {
				this->step = 2;
			}
		}
		if(!this->dead){
			if(this->hurt<=0){
				al_draw_scaled_bitmap(this->sprites,(this->m*41)+10,(this->step*30)+1,22,29,this->X * sf,(this->Y * sf) + (2*(sf/10)),sf,sf,this->d);
			} else {
				this->hurt-=1;
				al_draw_tinted_scaled_bitmap(this->sprites,al_map_rgba_f(1,1,1,0.5 * (this->hurt % 2)),(this->m*41)+10,(this->step*30)+1,22,29,this->X * sf,(this->Y * sf) + (2*(sf/10)),sf,sf,this->d);
			}
			if(this->proj){
				this->projectile->draw(sf);
			}
		}
	} else {
		if(this->shrink<5){
			this->shrink += 0.5;
		}
		al_draw_scaled_bitmap(this->sprites,(this->m*41)+10,(this->step*30)+1,22,29,this->X * sf + ((this->shrink * (sf/5)/2)),(this->Y * sf) + (2*(sf/10)) + ((this->shrink * (sf/5)/2)),sf - (this->shrink * (sf/5)),sf - (this->shrink * (sf/5)),this->d);
	}
}

void SideScroller::Player::left(){
	this->m = 1;
	this->d = 1;
	this->maxStep = 5;
}

void SideScroller::Player::right(){
	this->m = 1;
	this->d = 0;
	this->maxStep = 5;
}

void SideScroller::Player::idle(){
	this->m = 0;
	this->maxStep = 3;
	this->step = 0;
}

void SideScroller::Player::melee(){
	this->m = 3;
	this->maxStep = 2;
}

void SideScroller::Player::ranged(){
	if(!this->proj){
		this->projectile = new Projectile(this->type,ceil(this->X) - this->d,this->Y,this->d);
		this->proj = true;
	}
}

void SideScroller::Player::move(vector<vector<pair<int,int>>> map,int sf,int width){
	if(!this->levelComplete){
		try{
			if(map.at(floor(this->X + this->xoffset)).at(floor(this->Y)).second == 99){
				this->levelComplete = true;
			}
			if(map.at(ceil(this->X) + this->xoffset).at(floor(this->Y) + 1).second == 0){
				if(this->dy<0.45){
					this->dy+= 0.05;
				}
			} else {
				this->Y = floor(this->Y);
				this->dy = 0;
				this->canJump = true;
			}
			if(this->jump > 0&&map.at(floor(this->X) + this->xoffset).at(this->Y - 1).second == 0){
				this->dy = -0.5;
				this->jump = 0;
			} 
			this->Y += this->dy;
			if(this->m==1){
				if(this->d==0){
					if(ceil(this->X) >= (width / sf) - 3){
							this->X -= 0.5;
							this->xoffset += 1;
						}
						if(map.at(floor(this->X) + this->xoffset + 1).at(this->Y).second == 0||map.at(floor(this->X) + this->xoffset + 1).at(this->Y).second == 98||map.at(floor(this->X) + this->xoffset + 1).at(this->Y).second == 99){
							this->X += 0.25;
						}
					} else {
						if(this->X + this->xoffset > 0){
							if(floor(this->X)==3&&this->xoffset>0){
								this->X += 0.5;
								this->xoffset -= 1;
							}
							if(map.at(ceil(this->X) + this->xoffset - 1).at(this->Y).second == 0){
								this->X -= 0.25;
							}
						}
					}
				}
		} catch(exception e){
			printf("Error\n");
		}
	} 
}

