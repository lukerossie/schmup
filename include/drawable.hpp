#pragma once
#include "SDLW/SDLW.hpp"

bool intersects(ImageInfo,ImageInfo);

class DrawableObject
{
	private:
	
	public:
	class Animator
	{
		public:
		bool trigger;
		int newYDest;
		int* yDest;
		int animVel;
		
		Animator(int* _y) : yDest(_y), animVel(10), trigger(false) 
		{
		}
		void moveTo(int _ny)
		{
			newYDest = _ny;
			trigger = true;
		}
		void update()
		{
			if(trigger)
			{
				for(int i = 0; i < animVel; i++)
				{
					if(newYDest == *yDest)
					{
						trigger = false;
						return;
					}
					if(newYDest > *yDest)
					{
						int new1 = *yDest + 1;
						*yDest = new1;
					}
					if(newYDest < *yDest)
					{
						int new1 = *yDest - 1;
						*yDest = new1;
					}
				}
			}
		}
	};
	
	Animator anim;
	int XVel;
	int YVel;
	int x;
	int y;
	ImageInfo image;
	
	DrawableObject();
	DrawableObject(ImageInfo i);
	DrawableObject(ImageInfo i, int _XVel, int _YVel);
	
	void move();
	void draw();
	void update();
};
	
