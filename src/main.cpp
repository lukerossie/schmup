#include "SDLW/SDLW.hpp"
#include "gameCore.hpp"

int main()
{
	SDLW_init(SCREEN_WIDTH,SCREEN_HEIGHT,false);//screenWidth, screenHeight, bool fullscreen
	
	Game g;

	while (!quit())
	{		
		g.logic();
		g.render();
	}
}

