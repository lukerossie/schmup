#include "SDLW/SDLW.hpp"
#include "sprites.hpp"
#include "bullets.hpp"

vector<Bullet> bullet;

Bullet::Bullet(ImageInfo i, bool _friendly, Enemy* _e, Player* _p, EnemyList* _el) : DrawableObject(i) 
{
	alive = true;
	p = _p;
	e = _e;
	el = _el;
	friendly=_friendly;
	if(friendly)
	{
		YVel = -5;
		x = p->x + 10;
		y = p->y;
	}
	else
	{
		YVel = 5;
		x = e->x + 10;//needs to be tilesize (maybe need to make tilesize struct with .w and .h)
		y = e->y;
	}
}
Bullet::Bullet(ImageInfo i, bool _friendly, Player* _p, EnemyList* _el) : DrawableObject(i) 
{
	alive = true;
	p = _p;
	el = _el;
	friendly = _friendly;
	if(friendly)
	{
		YVel = -5;
		x = p->x + 10;
		y = p->y;
	}
}
Bullet::Bullet(ImageInfo i, int _XVel, int _YVel, bool _friendly, Enemy _e, Player* _p, EnemyList* _el) : DrawableObject(i,_XVel,_YVel) 
{	
	alive = true;
	p = _p;
	e = &_e;
	el = _el;
	friendly = _friendly;
	if(friendly)
	{
		YVel = -5;
		x = p->x + 10;
		y = p->y;
	}
	else
	{
		YVel = 5;
		x = e->x + 10;
		y = e->y;
	}
}
void Bullet::update()
{
	if(y < 0 || y > SCREEN_HEIGHT) kill();
	checkHit();
	move();	
}
void Bullet::checkHit()
{
	if(!friendly) 
		if(intersects(p->image,image)) 
		{
			p->kill();
			kill();
		}
	int counter = 0;
	if(friendly) 
		for(auto &x : el->grid)
		{
			bool animating = false;
			for(auto &y : x)
			{
				if(y.anim.trigger) animating = true;
				image.dest.x = this->x;
				image.dest.y = this->y;
				if(intersects(y.image,image)) 
				{
					if(!animating) el->knockBack(counter);
					kill();
				}
			}
			counter++;
		}	
}
void Bullet::kill()
{
	alive = false;
}
