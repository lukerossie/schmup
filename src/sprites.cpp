#include "SDLW/SDLW.hpp"
#include "bullets.hpp"
#include "sprites.hpp"

Enemy::Enemy() : DrawableObject()
{
	
}
Enemy::Enemy(ImageInfo i) : DrawableObject(i), alive(true) {}
Enemy::Enemy(ImageInfo i, int _color) : DrawableObject(i), color(_color)
{
	alive = true;
}
Enemy::Enemy(ImageInfo i, int _XVel, int _YVel) : DrawableObject(i,_XVel,_YVel) 
{
	alive = true;
}
void Enemy::kill()
{
	alive = false;
}
void Enemy::update()
{
	anim.yDest = &y;
	anim.update();
}

Mothership::Mothership() {}
Mothership::Mothership(ImageInfo i) : Enemy(i), hp(10) {}
void Mothership::kill()
{
	alive = false;
}
void Mothership::update()
{
	if(hp == 0) kill();
}

EnemyList::EnemyList()
{			
}
EnemyList::EnemyList(int _x, int _y, int xDest, int yDest, int _space) : m(ImageInfo("res/images/Mothership.bmp"))
{
	m.x = xDest;
	m.y = yDest;
	x = _x;
	y = _y;
	space = _space;
	int colora[x][y];
	for(int i = 0; i < x; i++)
		for(int a = 0; a < y; a++)
			colora[i][a] = (a+i)%3;
	for(int i = 0; i < x; i++)
	{
		vector<Enemy> v;
		
		for(int a = 0; a < y; a++)
		{
			int color = colora[i][a];//rand()%3;
			Enemy e(ImageInfo(randImage(color).c_str()), color);
			e.x = (e.image.w*i+(i*space))+xDest-(m.image.w/2);
			e.y = (e.image.h*a+(a*space))+yDest+m.image.h;
			v.push_back(e);
		}
		grid.push_back(v);
	}
}
string EnemyList::randImage(int num)
{
	switch(num)
	{
	case 0:
		{
			string r("res/images/r.bmp");
			return r;
		}
	break;
	case 1:
		{
			string g("res/images/g.bmp");
			return g;
		}	
	break;
	case 2:
		{
			string b("res/images/b.bmp");
			return b;
		}
	break;
	}
}
void EnemyList::knockBack(int x)
{
    int temp;
    for(int i = grid[x].size()-1; i >= 0; i--)
    {
        if(i != 0)
        {
            if(i == grid[x].size()-1) temp = grid[x][i].y;
            int temp2 = grid[x][i-1].y;
            grid[x][i-1].anim.moveTo(temp);
            temp = temp2;
        }
        else
        {
            grid[x][grid[x].size()-1].anim.moveTo(temp);
        }
    }
}
void EnemyList::update()
{
	check3();
}
bool EnemyList::check3(int _x, int _y)
{
	auto diffCo = [this](Enemy e, bool hor) -> int//hor true if checking horizontally false if checking vertically, return the space in between the coordinates
	{
		return hor ? e.image.w+space : e.image.h+space;
	};
	auto enemyPos = [this](int xco, int yco) -> Enemy*
	{
		for(auto &_x : grid)
			for(auto &_y : _x)
				if(_y.x == xco && _y.y == yco && _y.alive)
				{
					return &_y;
				}
		return NULL;
	};
	if(grid[_x][_y].alive)
	{
		{//verticle 3 matched
			Enemy* a = enemyPos(grid[_x][_y].x, grid[_x][_y].y+diffCo(grid[_x][_y],false));
			Enemy* b = enemyPos(grid[_x][_y].x, grid[_x][_y].y-diffCo(grid[_x][_y],false));
			if(a && b && (a->color == grid[_x][_y].color && b->color == grid[_x][_y].color))
			{
				return true;
			}
		}
		{//horizontal
			Enemy* a = enemyPos(grid[_x][_y].x+diffCo(grid[_x][_y],true), grid[_x][_y].y);
			Enemy* b = enemyPos(grid[_x][_y].x-diffCo(grid[_x][_y],true), grid[_x][_y].y);
			if(a && b && (a->color == grid[_x][_y].color && b->color == grid[_x][_y].color))
			{
				return true;
			}
		}
	}
	return false;
}
void EnemyList::check3()
{
	auto diffCo = [this](Enemy e, bool hor) -> int//hor true if checking horizontally false if checking vertically, return the space in between the coordinates
	{
		return hor ? e.image.w+space : e.image.h+space;
	};
	auto enemyPos = [this](int xco, int yco) -> Enemy*
	{
		for(auto &_x : grid)
			for(auto &_y : _x)
				if(_y.x == xco && _y.y == yco && _y.alive)
				{
					return &_y;
				}
		return NULL;
	};
	for(auto &_x : grid)
		for(auto &_y : _x)
		{
			if(_y.alive)
			{
				{//verticle 3 matched
					Enemy* a = enemyPos(_y.x, _y.y+diffCo(_y,false));
					Enemy* b = enemyPos(_y.x, _y.y-diffCo(_y,false));
					if(a && b && (a->color == _y.color && b->color == _y.color))
					{std::cout << "BEGIN:\n" << a->color << std::endl << b->color << std::endl << _y.color << "\nEND\n";
						a->alive = false;
						b->alive = false;
						_y.alive = false;
					}
				}
				{//horizontal
					Enemy* a = enemyPos(_y.x+diffCo(_y,true), _y.y);
					Enemy* b = enemyPos(_y.x-diffCo(_y,true), _y.y);
					if(a && b && (a->color == _y.color && b->color == _y.color))
					{
						a->alive = false;
						b->alive = false;
						_y.alive = false;
					}
				}
			}
		}
}

Player::Player(ImageInfo i, EnemyList* e) : DrawableObject(i)
{
	theList = e;
	XVel = 0;
	YVel = 0;
	milli = 0;
}
Player::Player(ImageInfo i, int _XVel, int _YVel, EnemyList* e) : DrawableObject(i,_XVel,_YVel) 
{
	theList = e;
	milli = 0;
}
void Player::update()
{
	if(ka.down && !kd.down) XVel = -5;
	if(kd.down && !ka.down) XVel = 5;
	if(ka.down && kd.down) XVel = 0;
	if(!ka.down && !kd.down) XVel = 0;
	
	bulletCD.update();
	milli += bulletCD.milliseconds;
	if(LMB && milli > 1000) 
	{	
		//bulletI = new ImageInfo("bullet.bmp", 0,0, 3,6, image->dest.y,image->dest.y);
		Bullet b(ImageInfo("res/images/bullet.bmp"), true, this, theList);
		bullet.push_back(b);
		milli = 0;
	}
	move();
}
void Player::kill()
{
}


