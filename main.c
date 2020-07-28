#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

int				main(int argc, char **argv)
{
	SDL_Surface		*fenetre;
	SDL_Surface		*carre;
	SDL_Surface		*perso;
	SDL_Surface		*text1;
	TTF_Font		*font_hud;
	SDL_Color		font_white = {255, 255, 255};
	SDL_Rect		position_text1;
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
	TTF_Init();
	fenetre = SDL_SetVideoMode(1280, 720, 32, SDL_HWSURFACE);
	SDL_FillRect(fenetre, NULL, SDL_MapRGB(fenetre->format, 255, 0, 0));
	green = SDL_MapRGB(fenetre->format, 0, 255, 0);
	// nouvelle surface
	carre = SDL_CreateRGBSurface(SDL_HWSURFACE, 50, 50, 32, 0, 0, 0, 0);
	SDL_FillRect(carre, NULL, green);
	position_carre.x = 450;
	position_carre.y = 450;
	SDL_BlitSurface(carre, NULL, fenetre, &position_carre);
	// surface personage
	perso = IMG_Load("life.png");
	position_perso.x = 0;
	position_perso.y = 0;
	SDL_BlitSurface(perso, NULL, fenetre, &position_perso);
	SDL_FreeSurface(perso);
	SDL_Flip(fenetre);
	// creer une police
	font_hud = TTF_OpenFont("hud_font.ttf", 18);
	// creer un text
	text1 = TTF_RenderText_Blended(font_hud, "100%", font_white);
	position_text1.x = 70;
	position_text1.y = 18;
	SDL_BlitSurface(text1, NULL, fenetre, &position_text1);
	SDL_FreeSurface(text1);
	SDL_Flip(fenetre);
	// son
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
	Mix_Chunk *music;
	music = Mix_LoadWAV("shotgun.wav");
	while (1)
	{
		SDL_WaitEvent(&event);
		if (event.type == SDL_QUIT)
		{
			break ;
		}
		if (event.type == SDL_KEYUP)
		{
			if (event.key.keysym.sym == SDLK_p)
			{
				Mix_PlayChannel(-1 , music, 0);
			}

		}

	}
	Mix_CloseAudio();
	SDL_FreeSurface(fenetre);
	SDL_FreeSurface(carre);
	TTF_Quit();
	SDL_Quit();
	return (0);
}
