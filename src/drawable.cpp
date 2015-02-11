#include "SDLW/SDLW.hpp"
#include "drawable.hpp"

DrawableObject::DrawableObject() : x(0), y(0), anim(&y)
{

}
DrawableObject::DrawableObject(ImageInfo i) : image(i), x(i.dest.x), y(i.dest.y), anim(&y), XVel(0), YVel(0)
{
	
}
DrawableObject::DrawableObject(ImageInfo i, int _XVel, int _YVel) : image(i), x(0), y(0), anim(&y), XVel(_XVel), YVel(_YVel)
{

}
void DrawableObject::move()
{
	x += XVel == 0 ? 0 : (abs((int)(XVel*((double)dtime/15000.0))) > 0 ? (int)(XVel*((double)dtime/15000.0)) : (XVel > 0 ? 1 : -1));
	y += YVel == 0 ? 0 : (abs((int)(YVel*((double)dtime/15000.0))) > 0 ? (int)(YVel*((double)dtime/15000.0)) : (YVel > 0 ? 1 : -1));
}	
void DrawableObject::draw()
{
	image.dest.x = x;
	image.dest.y = y;
	blit(image);
}
void DrawableObject::update()
{	
	move();
}

bool intersects(ImageInfo a, ImageInfo b)
{
	int atop = a.dest.y;
	int abot = a.dest.y+a.h;
	int btop = b.dest.y;
	int bbot = b.dest.y+b.h;
	int aleft = a.dest.x;
	int aright = a.dest.x+a.w;
	int bleft = b.dest.x;
	int bright = b.dest.x+b.w;
	
	return(
	/*if a intersects b*/
		(((abot >= btop && abot <= bbot) && ((aleft >= bleft && aleft <= bright) || (aright <= bright && aright >= bleft)))//from top
			||((abot >= btop && abot <= bbot) && ((aleft >= bleft && aleft <= bright) || (aright <= bright && aright >= bleft)))//from bot
			||((aleft >= bleft && aleft <= bright) && ((abot >= btop && abot <= bbot) || (abot >= btop && abot <= bbot)))//from left
			||((aright <= bright && aright >= bleft) && ((abot >= btop && abot <= bbot) || (abot >= btop && abot <= bbot))))//from right
		||
	/*if b intersects a*/
		(((bbot >= atop && bbot <= abot) && ((bleft >= aleft && bleft <= aright) || (bright <= aright && bright >= aleft)))//from top
			||((bbot >= atop && bbot <= abot) && ((bleft >= aleft && bleft <= aright) || (bright <= aright && bright >= aleft)))//from bot
			||((bleft >= aleft && bleft <= aright) && ((bbot >= atop && bbot <= abot) || (bbot >= atop && bbot <= abot)))//from left
			||((bright <= aright && bright >= aleft) && ((bbot >= atop && bbot <= abot) || (bbot >= atop && bbot <= abot))))//from right
	);	 
}

