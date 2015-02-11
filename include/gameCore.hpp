#include "SDLW/SDLW.hpp"
#include "bullets.hpp"
#include "clock.hpp"

class Game
{
	private:
	Player player;
	DrawableObject black;
	Clock gameClock;
	EnemyList EL_2;//probably better to store the seed for the grid and make the grid for each level
	
	public:
	Game() : gameClock(), EL_2(10,5, 500, 10, 10), black(ImageInfo("res/images/black.bmp")), player(ImageInfo("res/images/ship.bmp",0,0,26,36,(SCREEN_WIDTH/2)-36,SCREEN_HEIGHT-50), &EL_2)
	{
		
	}
	
	void logic()
	{	
		SDL_Delay(10);
		gameClock.update();
		dtime=(double)(gameClock.microseconds);
		switch(level)
		{
			case 0:
			{
			
			}
			break;
			case 1:
			{
							
			}
			break;
			case 2:
			{
				bullet.erase(std::remove_if(bullet.begin(), bullet.end(), [](Bullet b) { return !b.alive; }), bullet.end());
				
				player.update();
				for(auto &x : EL_2.grid)
				{
					for(auto &y : x)
					{
						y.update();
					}
				}
				for(auto &b : bullet)
				{
					b.update();
				}
				{//grid update, a bunch of crap goes here because my EnemyList class doesn't know about the player cuz im retarded
					EL_2.update();
					for(auto &_x : EL_2.grid)
					{
						Enemy* ptr;
						int highest = 0;
						for(auto &_y : _x)
						{	
							if(_y.y > highest) 
							{
								highest = _y.y;
								ptr = &_y;
							}
						}
						if(rand() % 500 < 1)//how often you want him to shoot bullets goes here
						{
							Bullet b(ImageInfo("res/images/bullet.bmp"), false, ptr, &player, &EL_2);
							bullet.push_back(b);
						}
					}
				}
			}
			break;
		}
	}
	void render()
	{
		switch(level)
		{
			case 0:
			{
			
			}
			break;
			case 1:
			{
							
			}
			break;
			case 2:
			{
				black.draw();
				drawText((string("FPS: ")+std::string(std::to_string(gameClock.FPS))).c_str(), 12, 0,0, 255,255,255, 0,0,0);//(char *text, size, x,y, fR,fG,fB, bR,bG,bB)
				drawText((string("millis: ")+std::string(std::to_string(gameClock.lapsedMilli))).c_str(), 12, 0,100, 255,255,255, 0,0,0);
				drawText((string("dtime: ")+std::string(std::to_string(dtime))).c_str(), 12, 0,200, 255,255,255, 0,0,0);
				drawText((string("HP: ")+std::string(std::to_string(EL_2.m.hp))).c_str(), 12, 350,100, 255,255,255, 0,0,0);
				{
					for(auto &x : EL_2.grid)//& because you have to draw the actual thing, since you change e.dest.x in the function
					{
						for(auto &y : x)
						{
							if(y.alive) y.draw();
						}
					}
					EL_2.m.draw();
				}
				for(auto &b : bullet)
				{
					b.draw();
				}
				player.draw();
				flip();//render
			}
			break;
		}
	}
};
