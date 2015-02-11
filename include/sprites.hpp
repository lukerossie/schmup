#pragma once
#include "SDLW/SDLW.hpp"
#include "bullets.hpp"
#include "drawable.hpp"
#include "clock.hpp"

class Enemy : public DrawableObject
{
	private:
	
	public:
	int color;
	bool alive;
	Enemy();
	Enemy(ImageInfo i);
	Enemy(ImageInfo i, int _color);
	Enemy(ImageInfo i, int _XVel, int _YVel);
	void kill();
	void update();
};

class Mothership : public Enemy
{
	private:
	
	public:
	int hp;
	Mothership();
	Mothership(ImageInfo i);
	void kill();
	void update();
};

class EnemyList
{
	private:
	
	public:
	Mothership m;
	int x;
	int y;
	int space;
	vector< vector<Enemy> > grid;
	EnemyList();
	EnemyList(int _x, int _y, int xDest, int yDest, int _space);
	void knockBack(int);
	void update();
	void check3();
	bool check3(int x, int y);
	string randImage(int);
};

class Player : public DrawableObject
{
	private:
	Clock bulletCD;
	EnemyList* theList;
	int milli;
	
	public:
	Player(ImageInfo i, EnemyList*);
	Player(ImageInfo i, int _XVel, int _YVel, EnemyList*);
	void update();
	void kill();
};

