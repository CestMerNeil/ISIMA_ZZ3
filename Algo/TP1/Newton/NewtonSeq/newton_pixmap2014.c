/* -------------------------------------------------------------------------- */
/* Methode de NEWTON pour le calcul des racines d'une fonction f(x)=x^3-1     */
/* xn+1 = xn + f(xn) / f'(xn)                                                 */
/* -------------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>
#include <X11/Xatom.h> /* Pour la fermeture de la fenetre avec le bouton x */

#include "complexe.h"
#include "fonctions.h"

/* -------------------------------------------------------------------------- */
/* Les variables pour XWindow                                                 */
/* -------------------------------------------------------------------------- */
char         *tit_racine = "Newton";
Display      *display;
Window        racine;        /* fenetre mere de toutes les autres fenetres       */

GC            cg_cp;         /* contexte graphique pour le dessin definitif      */
Colormap      cmap;          /* table de couleurs par defaut                     */
unsigned long val_pixels[6]; /* les indices des cellules de couleurs allouees dans cmap */
int           fait_coul = {DoRed | DoGreen | DoBlue};
unsigned long noir, blanc;   /* couleurs noir et blanche                         */
int           i;
int           depth_def;	 /* Profondeur par défaut de l'écran */
XColor        couleur, exact;

Drawable      image;         /* Drawable contenant la Pixmap   */
int           flag_cal=0;    /* flag pour le calcul de l'image */


/* -------------------------------------------------------------------------- */
/* Fonction "main"  du programme newton                                       */
/* -------------------------------------------------------------------------- */
int main(int argc, char **argv)
{
	int               ecran;
	XEvent            ev;
	unsigned long     masque_valeur;
	XGCValues         valeurs_gc;
	
	XSizeHints        indic;
	char              caractere[10];
	KeySym            touche;

	Atom              protocoles[1]; /* Pour la fermeture de la fenetre avec le bouton x */
	
	unsigned int      xe, ye;        /* coordonnees de l'ecran */
	unsigned int      c;             /* couleur */
	complexe_t        x;

	int               encore, i;
	
	/* --------------------------------------------------------- */
	/* Connexion au serveur X                                    */
	/* --------------------------------------------------------- */
	display = XOpenDisplay(NULL);
	if (!display) {
		fprintf(stderr, "Impossible d'ouvrir le display.\n");
		fprintf(stderr, "Assurez-vous que la variable DISPLAY est initialisee.\n");
		fprintf(stderr, "Elle doit contenir, par exemple : \"termx:0\"\n");
		exit(1);
	}

	/* --------------------------------------------------------- */
	/* Consultation de certaines caracteristiques du serveur X.  */
	/* --------------------------------------------------------- */
	ecran = DefaultScreen(display);
	blanc = WhitePixel(display,ecran);
	noir = BlackPixel(display,ecran);

	/* --------------------------------------------------------- */
	/* Allocation des couleurs                                   */
	/* --------------------------------------------------------- */
	depth_def = DefaultDepth(display, ecran);
	cmap = DefaultColormap(display,ecran);

	/* allocation de couleurs rouge, vert, bleu */
	if (XAllocNamedColor(display, cmap, "indian red", &couleur, &exact)) 
		val_pixels[0] = couleur.pixel;
	else
		val_pixels[0] = noir;

	if (XAllocNamedColor(display, cmap, "navy blue", &couleur, &exact)) 
		val_pixels[1] = couleur.pixel;
	else
		val_pixels[1] = blanc;  

	if (XAllocNamedColor(display, cmap, "forest green", &couleur, &exact)) 
		val_pixels[2] = couleur.pixel;
	else
		val_pixels[2] = noir;

	/* --------------------------------------------------------- */
	/* Creation de la fenetre top-niveau du nom de "Newton"      */
	/* --------------------------------------------------------- */
	indic.x = 200; indic.y = 300;
	indic.width = 1024; indic.height = 1024;
	indic.flags = PPosition | PSize;
	racine = XCreateSimpleWindow(display, DefaultRootWindow(display),
			    indic.x, indic.y, indic.width, indic.height,
			    1, noir, blanc);
	/* Definition des proprietes standards de la fenetre top-niveau 
	   a l'intention du gestionnaire de fenetres */
	XSetStandardProperties(display, racine, 
						   tit_racine, tit_racine, None, argv, argc, &indic);
	
	/* Pour la fermeture de la fenetre avec le bouton x */
	protocoles[0] = XInternAtom(display, "WM_DELETE_WINDOW", False);
	XSetWMProtocols(display, racine, protocoles, 1);
	
	/* Selection des evenements interessants pour la fenetre top-niveau */
	XSelectInput(display, racine, KeyPressMask | ExposureMask | StructureNotifyMask);

	/* --------------------------------------------------------- */
	/* Creation d'un contexte graphique dessin */
	/* --------------------------------------------------------- */
	valeurs_gc.foreground = noir;
	valeurs_gc.background = blanc;
	valeurs_gc.line_width = 1;
	valeurs_gc.function = GXcopy;
	masque_valeur = GCForeground | GCBackground | GCLineWidth | GCFunction;
	cg_cp = XCreateGC(display, racine, masque_valeur, &valeurs_gc);

	XMapRaised(display, racine);

	/* Creation de l'image */
	image=XCreatePixmap(display,racine,indic.width,indic.height,depth_def);
	XSetForeground(display,cg_cp,blanc);
	XFillRectangle(display,image,cg_cp,0,0,indic.width,indic.height);
	
	/* --------------------------------------------------------- */
	/* Boucle Principale */
	/* --------------------------------------------------------- */
	encore = True;
	while (encore) {
		XNextEvent(display, &ev);
		switch (ev.type) {
			case Expose :
				while ( XCheckTypedEvent(display, Expose, &ev) ); // purge des ev. Expose
				
				/* ev.xexpose.width et ev.xexpose.height sont les dimensions de la zone à rafraichir */
				if (ev.xexpose.count == 0) {
					if (flag_cal == 0) {
						printf("Je redessine : Window size=(%d, %d)\n", indic.width, indic.height);
						
						for (xe=0; xe<indic.width; xe++) {
							for (ye=0; ye<indic.height; ye++) {
								x.re = (double)XMIN + ((double)xe*(XMAX-XMIN))/((double)(indic.width-1)); 
								x.im = (double)YMAX - ((double)ye*(YMAX-YMIN))/((double)(indic.height-1));
							
								if (x.re==0 && x.im==0) c=0; 
								else c = couleur3(x);
							
								XSetForeground(display, cg_cp, val_pixels[c]);
								XDrawPoint(display, image, cg_cp, xe,ye);
							}
							XCopyArea(display,image,racine,cg_cp,xe,0,1,indic.height,xe,0);
						}
						
						flag_cal = 1;
					}
					else {
						printf("Je recopie ...\n");
						XCopyArea(display,image,racine,cg_cp,0,0,indic.width,indic.height,0,0);
					}

				}
				break;
     
			case MappingNotify :
				XRefreshKeyboardMapping(&(ev.xmapping));
				break;

			case ConfigureNotify : 
				if (ev.xconfigure.window == racine) {
					while ( XCheckTypedEvent(display, ConfigureNotify, &ev) ); // purge des ev. Configure
					
					 /* recuperation de la nouvelle position et 
					   la nouvelle taille de la fenetre racine */
					indic.x = ev.xconfigure.x;
					indic.y = ev.xconfigure.y;
					
					if( (indic.width != ev.xconfigure.width) ||
						 (indic.height != ev.xconfigure.height)) { 
						indic.width = ev.xconfigure.width;
						indic.height = ev.xconfigure.height;
						printf("configreNotify: Window size=(%d, %d)\n", indic.width, indic.height); 

						XFreePixmap(display,image);
						image=XCreatePixmap(display,racine,indic.width,indic.height,depth_def);
						XSetForeground(display,cg_cp,blanc);
						XFillRectangle(display,image,cg_cp,0,0,indic.width,indic.height);

						/* Certaine ConfigureNotify n'est pas suivi d'evenement Expose */ 
						for (xe=0; xe<indic.width; xe++) {
							for (ye=0; ye<indic.height; ye++) {
								x.re = (double)XMIN + ((double)xe*(XMAX-XMIN))/((double)(indic.width-1)); 
								x.im = (double)YMAX - ((double)ye*(YMAX-YMIN))/((double)(indic.height-1));
								
								if (x.re==0 && x.im==0) c=0; 
								else c = couleur3(x);
								
								XSetForeground(display, cg_cp, val_pixels[c]);
								XDrawPoint(display, image, cg_cp, xe,ye);
							}
							XCopyArea(display,image,racine,cg_cp,xe,0,1,indic.height,xe,0);
						}
					}
				}
				break;
				
			case ClientMessage : /* Pour la fermeture de la fenetre avec le bouton x */
				printf("Fermeture de la fenetre\n");
				encore = False;
				break;		
				
			case KeyPress :
				i = XLookupString(&(ev.xkey), caractere, 10, &touche, 0);
				printf("Touche Fin\n");
				if (touche == XK_End) encore = False;
				break;
			
		}
	}

	XDestroyWindow(display,racine);
	XFreeGC(display, cg_cp);
	XFreePixmap(display,image);
	XCloseDisplay(display);
	
	return 0;
}

