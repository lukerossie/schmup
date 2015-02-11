#pragma once
#include "SDLW/SDLW.hpp"
#include "sprites.hpp"
#include "drawable.hpp"

class Player;
class Enemy;
class EnemyList;

class Bullet : public DrawableObject
{
	private:
	Player* p;
	Enemy* e;
	EnemyList* el;
	public:
	bool friendly;
	bool alive;
	Bullet(ImageInfo, bool _friendly, Enemy*, Player*, EnemyList*);
	Bullet(ImageInfo, int _XVel, int _YVel, bool _friendly, Enemy, Player*, EnemyList*);
	Bullet(ImageInfo, bool _friendly, Player* _p, EnemyList* _el);
	void checkHit();
	void update();
	void kill();
	
	public:
	
};
extern vector<Bullet> bullet;
