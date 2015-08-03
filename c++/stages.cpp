#include "stages.h"
#include <iostream>

SideScroller::Stage::Stage(int width, int sf, int ds): width(width),sf(sf),dispSize(ds){
	this->dStepS = 0;
	this->dStepE = 0;
	this->bg = al_load_bitmap("assets/side/cant use/images/cave.png");
	this->doors = al_load_bitmap("assets/side/sprites/d/doors.png");
	this->levelComplete = false;
	this->map.resize(this->width);
	for(int i=0;i<this->width;i++){
		this->map[i].resize(10);
	}
}

void SideScroller::Stage::draw(int xoffset,bool dead,bool done){
	al_draw_scaled_bitmap(this->bg,0,0,1000,500,0,0,this->dispSize,this->sf * 10,0);
	for(int x=0;x<(this->dispSize/this->sf) + 1;x++){
		try{
			for(int y=0;y<this->map.at(x + xoffset).size();y++){
				if(this->map.at(x + xoffset).at(y).first==1){
					al_draw_scaled_bitmap(this->spritesheet,26,0,28,26,x * sf,(y * sf),sf,sf,0);
				} else if(this->map.at(x + xoffset).at(y).first==2){
					al_draw_scaled_bitmap(this->spritesheet,26,52,28,26,x * sf,(y * sf),sf,sf,0);	
				} else if(this->map.at(x + xoffset).at(y).first==3){
					al_draw_scaled_bitmap(this->spritesheet,26,25,28,26,x * sf,(y * sf),sf,sf,0);	
				} else if(this->map.at(x + xoffset).at(y).first == 99){
					al_draw_scaled_bitmap(this->spritesheet,26,25,28,26,x * sf,(y * sf),sf,sf,0);
					al_draw_scaled_bitmap(this->doors,320,0,64,96,x * sf, y * sf,sf,sf,0);
					al_draw_scaled_bitmap(this->doors,0,0,64,96,x * sf,(y * sf),sf,sf,0);
					if(this->map.at(x + xoffset).at(y).second == 99){
						al_draw_scaled_bitmap(this->doors,(floor(this->dStepE) + 1) * 64,0,64,96,x * sf,(y * sf),sf,sf,0);
					} else {
						al_draw_scaled_bitmap(this->doors,(floor(this->dStepS) + 1) * 64,0,64,96,x * sf,(y * sf),sf,sf,0);
					}
				}
			}
		} catch(exception e){
				al_draw_filled_rectangle(x*sf,0,(x + 1) * sf,sf * 10,al_map_rgb(0,0,0));
		}
	}
	if(!dead&&!done){
		for(int i=0;i<this->enemies.size();i++){
			this->enemies[i]->AI(this->map,xoffset);
		}
	}
	if(done){
		if(this->dStepE<4){
			this->dStepE+=0.5;
		} else {
			this->levelComplete = true;
		}
	}
}

void SideScroller::Stage::GenerateMap(){
	for(int x=0;x<this->width;x++){
		for(int y=0;y<10;y++){
			this->map[x][y] = make_pair(0,0); //blank map
		}
	}
	for(int x=1;x<this->width;x++){
		this->map[x][0] = make_pair(2,1); //ceiling
		this->map[x][9] = make_pair(1,1); //floor
		for(int y=9;y>=0;y--){
			if(y==9){
				int r = (rand() % 5) + 1;
				if(r<3){
					this->map[x][9] = make_pair(3,1);
				} else {
					this->map[x][9] = make_pair(1,1);
				}
			} else if(y>3){
				if(((y<6&&this->map[x][y+1].first == 3)||(this->map[x][y+1].first == 3 && (this->map[x-1][y+1].first == 3||this->map[x-1][y+1].first == 1)))&&(x>4&&x<width-4)){
					int r = (rand() % 5) + 1;
					if(r<3){
						this->map[x][y] = make_pair(1,1);
					} else {
						this->map[x][y] = make_pair(3,1);
					}
				} else if(y>=6&&this->map[x][y+1].first == 3){
					this->map[x][y] = make_pair(1,1);
				}
			} else if(y==3){
				if(this->map[x][y+1].first == 3){
					this->map[x][y] = make_pair(1,1);
				}
			}
			this->map[0][y] = make_pair(3,1); //left wall
			this->map[this->width-1][y] = make_pair(3,1); //right wall
		}
	}
	this->map[2][9] = make_pair(3,1);
	this->map[1][9] = make_pair(3,1);
	this->map[this->width - 2][9] = make_pair(3,1);
	this->map[this->width - 3][9] = make_pair(3,1);
	this->map[1][8] = make_pair(3,1);
	this->map[2][8] = make_pair(1,1);
	this->map[this->width - 2][8] = make_pair(3,1);
	this->map[this->width - 3][8] = make_pair(1,1);
	this->map[1][7] = make_pair(1,1);
	this->map[this->width - 2][7] = make_pair(1,1);
	this->map[0][6] = make_pair(99,98);
	this->map[this->width - 1][6] = make_pair(99,99);
}

void SideScroller::Stage::GenerateEnemies(int type){
	for(int i = 0;i<(rand() % (this->width / 2))+2;i++){
		Enemy* _enemy;
		int enemy = (rand() % 2) + type;
		bool location = false;
		int x;
		x = (rand() % (this->width - 6)) + 5;
		while(this->EnemyAt(x,8)||this->WallAt(x,8)){
			x = (rand() % (this->width - 6)) + 5;
		}
		if(enemy == 1){
			_enemy = new Slime(this->sf,x,8);
		} else {//if(enemy == 2){
			_enemy = new Skeleton(this->sf,x,8);
		}
		_enemy->d = rand() % 2;
		this->enemies.push_back(_enemy);
	}
}

bool SideScroller::Stage::EnemyAt(int x,int y){
	for(int a=0;a<this->enemies.size();a++){
		if(floor(this->enemies[a]->x) == x && floor(this->enemies[a]->y) == y){
			return true;
		}
	}
	return false;
}

bool SideScroller::Stage::WallAt(int x,int y){
	if(this->map[x][y].second == 1){
		return true;
	} else {
		return false;
	}
}

SideScroller::Grass_Stage::Grass_Stage(int width, int sf,int ds) : Stage(width,sf,ds){
	this->spritesheet = al_load_bitmap("assets/side/sprites/bg/grass.png");
	this->GenerateMap();
	this->GenerateEnemies();
}

SideScroller::Stone_Stage::Stone_Stage(int width, int sf,int ds) : Stage(width,sf,ds){
	this->spritesheet = al_load_bitmap("assets/side/sprites/bg/stone.png");
	this->GenerateMap();
	this->GenerateEnemies();
}

Roguelike::Tile::Tile(bool blocked,bool block_sight):blocked(blocked),block_sight(block_sight){
	this->visible = false;
	if(this->block_sight == NULL){
		this->block_sight = this->blocked;
	}
	this->lit = false;
}

Roguelike::Rect::Rect(int x, int y, int w, int h) : x1(x), y1(y), x2(x + w), y2(y + h){}

pair<int,int> Roguelike::Rect::center(){
	return make_pair(ceil((this->x1 + this->x2)/2),ceil((this->y1 + this->y2)/2));
}

bool Roguelike::Rect::intersect(Rect *other){
	return (this->x1 <= other->x2 && this->x2 >= other->x1 && this->y1 <= other->y2 && this->y2 >= this->y1);
}