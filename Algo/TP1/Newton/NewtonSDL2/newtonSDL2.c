/* -------------------------------------------------------------------------- */
/* Methode de NEWTON pour le calcul des racines d'une fonction f(x)=x^3-1     */
/* xn+1 = xn + f(xn) / f'(xn)                                                 */
/* -------------------------------------------------------------------------- */
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "complexe.h"
#include "fonctions.h"

#define NB_COLORS      6

/* ~~~~~~~~~~~~~~~~~~~~ Structures du moteur de jeu ~~~~~~~~~~~~~~~~~~~~~ */
typedef struct color_s {
	Uint8 r;
	Uint8 g;
	Uint8 b;
	Uint8 a;
} color_t;

/* ~~~~~~~~~~~~~~~~~~ Variables ressources graphiques ~~~~~~~~~~~~~~~~~~ */
SDL_Window   *window   = NULL;
int width = 600, height = 600;

SDL_Renderer *renderer = NULL;

/* Table de couleurs : indian red, navy blue, forest green, black, white, */
color_t tabColors[NB_COLORS] = { {205, 92, 92, 255},
                                 {0, 0, 128, 255}, 
								 {34, 139, 34, 255},
                                 {0, 0, 0, 255}, {225, 225, 225, 255},
                                 {239, 155, 15, 255} };
int valPixels[NB_COLORS] = {0, 1, 2}; /* les indices de couleurs */

/*
 * Dessiner l'ecran graphique
 * Entrees :
 *      width  : largeur de la fenetre en nb de pixels
 *      height : hauteur de la fenetre en nb de pixels
 */
void afficherEcran(size_t width, size_t height)
{
	size_t     xe = 0, ye = 0;
	size_t     c;
	complexe_t x;
	
	for (xe=0; xe<width; xe++)
		for (ye=0; ye<height; ye++) {
			x.re = (double)XMIN + ((double)xe*(XMAX-XMIN))/((double)(width-1)); 
			x.im = (double)YMAX - ((double)ye*(YMAX-YMIN))/((double)(height-1));
							
			if (x.re==0 && x.im==0) c=0; 
				else c = couleur3(x);
							
			SDL_SetRenderDrawColor(renderer, tabColors[valPixels[c]].r, 
											 tabColors[valPixels[c]].g, 
											 tabColors[valPixels[c]].b, 
											 tabColors[valPixels[c]].a);
			SDL_RenderDrawPoint( renderer, xe, ye);
	}
		
	SDL_RenderPresent(renderer);
}

/* -------------------------------------------------------------------------- */
/* Fonction "main"  du programme newton                                       */
/* -------------------------------------------------------------------------- */
int main(int argc, char **argv)
{
	SDL_Event     event;	

	int running = 1;
		
	/* ~~~~~~~~~~~~~~ Initialisation des ressources graphiques ~~~~~~~~~~~~~~ */
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
		fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}

	window = SDL_CreateWindow("Image fractal par Methode de Newton", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

	if (window == NULL) {
		fprintf(stderr, "Echec de creation de la fenetre graphique : %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED ); /*  SDL_RENDERER_SOFTWARE */
	if (renderer == NULL) {
		fprintf(stderr, "Echec de creation de renderer : %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}
	
    SDL_EventState(SDL_MOUSEWHEEL,SDL_DISABLE);   // Desactive la roulette de la souris
    SDL_EventState(SDL_MOUSEMOTION,SDL_DISABLE);  // Desactive le deplacement de la souris
    SDL_EventState(SDL_MULTIGESTURE,SDL_DISABLE); // Desactive touche multiples
    SDL_EventState(SDL_USEREVENT,SDL_DISABLE);    // Desactive les evenements utilisateur

   /* ~~~~~~~~~~~~~~~~~~ Bouocle de traitements des evenements ~~~~~~~~~~~~~~~~~~ */
	while (running) {
		while (SDL_PollEvent(&event)) {
			switch(event.type) {
				case SDL_WINDOWEVENT:
					switch (event.window.event) {
						case SDL_WINDOWEVENT_CLOSE:
							printf("Close window\n");
							running = 0;
							break;
						case SDL_WINDOWEVENT_SIZE_CHANGED:
							width = event.window.data1;
							height = event.window.data2;
							printf("New window size : %d %d\n", width, height);
							afficherEcran(width, height);
							break;
						case SDL_WINDOWEVENT_EXPOSED:
							printf("Exposed\n");
							afficherEcran(width, height);
					}
					break;
					
					case SDL_MOUSEBUTTONDOWN:
						printf("Appui :%d %d\n", event.button.x, event.button.y);
					break;
					
					case SDL_QUIT :
						printf("On quitte\n");
						running = 0;
			}
		}
		SDL_Delay(100); //  delai minimal (en millisecondes)
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}

