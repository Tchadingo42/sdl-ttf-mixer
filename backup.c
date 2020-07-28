#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

int				main(int argc, char **argv)
{
	SDL_Surface		*fenetre;
	SDL_Surface		*carre;
	SDL_Surface		*perso;
	SDL_Event		event;
	SDL_Rect		position_carre;
	SDL_Rect		position_perso;
	Uint32			green, red;

	fenetre = NULL;
	carre = NULL;
	if (SDL_Init(SDL_INIT_VIDEO))
	{
		fprintf(stderr, "Error init : %s\n", SDL_GetError());
	}
	fenetre = SDL_SetVideoMode(1280, 720, 32, SDL_HWSURFACE);
	SDL_FillRect(fenetre, NULL, SDL_MapRGB(fenetre->format, 255, 0, 0));
	green = SDL_MapRGB(fenetre->format, 0, 255, 0);
	// nouvelle surface
	carre = SDL_CreateRGBSurface(SDL_HWSURFACE, 50, 50, 32, 0, 0, 0, 0);
	SDL_FillRect(carre, NULL, green);
	position_carre.x = 50;
	position_carre.y = 50;
	SDL_BlitSurface(carre, NULL, fenetre, &position_carre);
	// surface personage
	perso = IMG_Load("life.png");
	position_perso.x = 0;
	position_perso.y = 0;
	SDL_BlitSurface(perso, NULL, fenetre, &position_perso);
	SDL_FreeSurface(perso);
	SDL_Flip(fenetre);
	while (1)
	{
		SDL_WaitEvent(&event);
		if (event.type == SDL_QUIT)
		{
			break ;
		}

	}
	SDL_FreeSurface(fenetre);
	SDL_FreeSurface(carre);
	SDL_Quit();
	return (0);
}
