/*****************************************************************************
File: TD3-avatar-skel.c

Informatique Graphique IG1
IFIPS
Christian Jacquemin, Université Paris 11

Copyright (C) 2007 University Paris 11 
This file is provided without support, instruction, or implied
warranty of any kind.  University Paris 11 makes no guarantee of its
fitness for a particular purpose and is not liable under any
circumstances for any damages or loss whatsoever arising from the use
or inability to use this file or items derived from it.
******************************************************************************/
/*  AVATAR.C */

#include "avatar.h"

int main(int argc, char **argv) 
{  
	/* affichage des touches dans la console */
	printf("  Mouvements :\na: s'assoir, r: courir, m: marcher, s: demi-tour, d: danser\n");
	printf("  Vues :\n4: dessus, 5: derrier, 6: devant, 7: incline, 8: cote\n");
	printf("  Modes :\n0: manuel, 1: aleatoire\n\n");
	
	/* initialisation  des paramètres de GLUT en fonction
	  des arguments sur la ligne de commande */
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	/* définition et création de la fenêtre graphique */
	glutInitWindowSize(windowWidth,windowHeight);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Avatar anime de Manfred et Sacha");

	/* initialisation pour la fonction rand */
	srand(time(NULL));

	// initialisation de OpenGL et de la scène
	initGL();  
	init_scene();

	/* choix des procédures de callback pour 
	le tracé graphique */
	glutDisplayFunc(&window_display);
	/* le redimensionnement de la fenêtre */
	glutReshapeFunc(&window_reshape);
	/* la gestion des événements clavier */
	glutKeyboardFunc(&window_key);
	/* la gestion des clicks souris */
	glutMouseFunc(&window_mouseFunc);
	/* la gestion des déplacement souris */
	glutMotionFunc(&window_motionFunc);
	/* fonction appelée régulièrement entre deux gestions d´événements */
	glutTimerFunc(latence,&window_timer,Step);

	/* la boucle prinicipale de gestion des événements utilisateur */
	glutMainLoop();  

	return 1;
}

GLuint raw_texture_load(const char *filename, int width, int height)
{
     GLuint texture;
     unsigned char *data;
     FILE *file;
     
     /* open texture data */
     file = fopen(filename, "rb");
     if (file == NULL) return 0;
     
     /* allocate buffer */
     data = (unsigned char*) malloc(width * height * 4);
     
     /* read texture data */
     fread(data, width * height * 4, 1, file);
     fclose(file);
     
     /* allocate a texture name */
     glGenTextures(1, &texture);
     
     /* select our current texture */
     glBindTexture(GL_TEXTURE_2D, texture);
     
     /* select modulate to mix texture with color for shading */
     glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
     
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_DECAL);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_DECAL);
     
     /* when texture area is small, bilinear filter the closest mipmap */
     glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
     /* when texture area is large, bilinear filter the first mipmap */
     glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
     
     /* texture should tile */
     glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
     glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
     
     /* build our texture mipmaps */
     gluBuild2DMipmaps(GL_TEXTURE_2D, 4, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);
     
     /* free buffer */
     free(data);
     
     return texture;
 }


GLvoid initGL() 
{
	/* initialisation de l´éclairement */

	/* définition de deux source lumineuses */
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light0);
	glLightfv(GL_LIGHT1, GL_AMBIENT, ambient_light1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse_light1);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position0);
	glLightfv(GL_LIGHT1, GL_POSITION, light_position1);

	/* activation de l´éclairement */
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	/* rendre un objet transparent avec glcolor4f */
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);


	/* propriétés matérielles des objets */
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_ambientanddiffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glShadeModel( GL_SMOOTH );
	glEnable(GL_COLOR_MATERIAL);
	
	/* modification de la couleur du ciel */
	glClearColor(0.8, 0.4, 0.4, 1.0);
	   
	/* z-buffer */
	glEnable(GL_DEPTH_TEST);
}
  
void init_scene()
{
	/* initialise des display lists des composantes cylindriques du corps */
	Faire_Composantes();
	Faire_Chaise();
	Faire_Decor();

	amplitude_Bras 
	= .5 * (angle_Bras_Ini[ Droit ] - angle_Bras_Ini[ Gauche ]);
	amplitude_AvantBras 
	= .5 * (angle_AvantBras_Ini[ Droit ] - angle_AvantBras_Ini[ Gauche ]);
	amplitude_Cuisse 
	= .5 * (angle_Cuisse_Ini[ Droit ] - angle_Cuisse_Ini[ Gauche ]);
	amplitude_Mollet 
	= .5 * (angle_Mollet_Ini[ Droit ] - angle_Mollet_Ini[ Gauche ]);

	med_Bras 
	= .5 * (angle_Bras_Ini[ Droit ] + angle_Bras_Ini[ Gauche ]);
	med_AvantBras 
	= .5 * (angle_AvantBras_Ini[ Droit ] + angle_AvantBras_Ini[ Gauche ]);
	med_Cuisse 
	= .5 * (angle_Cuisse_Ini[ Droit ] + angle_Cuisse_Ini[ Gauche ]);
	med_Mollet 
	= .5 * (angle_Mollet_Ini[ Droit ] + angle_Mollet_Ini[ Gauche ]);
}

/* fonction de call-back pour l´affichage dans la fenêtre */

GLvoid window_display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	render_scene();

	/* trace la scène grapnique qui vient juste d'être définie */
	glFlush();
}

/* fonction de call-back pour le redimensionnement de la fenêtre */

GLvoid window_reshape(GLsizei width, GLsizei height)
{  
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-20, 20, -20, 20, -1000, 1000);

	/* toutes les transformations suivantes s´appliquent au modèle de vue */
	glMatrixMode(GL_MODELVIEW);
}

/* fonction de call-back pour la gestion des événements clavier */

GLvoid window_key(unsigned char key, int x, int y) 
{  		
	int actif = 1;
	switch (key) {  /* toutes les touches activables dans les deux modes possibles */ 
		case KEY_ESC:  
			exit(1);                    
			break; 
		
		case ' ':  
			if (IdleRunning) {
				glutTimerFunc(latence,NULL,Step);
				IdleRunning = false;
			} 
			
			else {
				glutTimerFunc(latence,&window_timer,Step);
				IdleRunning = true;
			}
			break; 
		
		case '+': delta *= 1.501; break; 
		case '-': delta /= 1.51; break; 
		case '4': camera = '4'; break;
		case '5': camera = '5'; break;
		case '6': camera = '6'; break;
		case '7': camera = '7'; break;
		case '8': camera = '8'; break;
		case '1': mode = 1; break;
		case '0': mode = 0; break;
		
		case 'a':
			if ((pos > 10) || (pos < -10))
				next_move = 'a';
		break;
		
		default:
			actif = 0; break;
	 }     
	  
	if (mode == 0) { /* mode manuel */
		switch (key) {
			case 'm': next_move = 'm'; break;
			case 'r': next_move = 'r'; break;
			case 'w': next_move = 'w'; break;
			case 'l': next_move = 'l'; break;
			case 'd': /* pour la dance, on vérifie qu'il ne va pas percuter une chaise */
				if ((pos > -9.5) && (pos < 9.5)) 
					next_move = 'd';
				break;
			case 's': next_move = 's'; break;
			default : /* aucune touche n'a été pressée */
				if (actif == 0) 
					printf("La touche n'est pas active.\n");
				break;
		}
	} 
}

/* fonction qui choisit une touche de façon aléatoire, 
 en vérifiant que le mouvement sélectionné est faisable */

void automatic_key(float t) {
	
	/* temps aléatoire durant lequel l'action ne change pas */
	if (tempsAlea == 0)
		tempsAlea = rand()%3000 + 1000;
	
	/* on effectue l'action tant qu'on a pas atteint cette durée */
	if (t > tempsAlea) {
		int m;
		if ((pos > 10) || (pos < -10)) { /* s'il est vers une chaise */
			if (move != 'a') { 
				/* si l'avatar est face à la chaise, on choisit entre s'assoir et demi-tour */
				if (((pos < -10) && (way == 0)) || ((pos > 10) && (way == 1))) {
					m = rand()%3;
					if (m < 2) next_move = 'a';
					else next_move = 's';
				}
				else { /* sinon, on choisit entre marcher, courir, demi-tour, danser et attendre */
					m = rand()%5;
					switch (m) {
						case 0: next_move = 'm'; break;
						case 1: next_move = 'r'; break;
						case 2: next_move = 'w'; break;
						case 3: 
							if ((pos > -9.5) && (pos < 9.5))
								next_move = 'd'; 
							break;
						case 4: next_move = 's'; break;
						default : break;
					}
				}
			}
			else  /* si l'avatar est assis, on le fait se lever */
				next_move = 'l';
		}
		else { /* si l'avatar est loin d'une chaise */
			m = rand()%5;
			switch (m) { /* on choisit entre marcher, courir, demi-tour, danser et attendre */
				case 0: next_move = 'm'; break;
				case 1: next_move = 'r'; break;
				case 2: next_move = 'w'; break;
				case 3: /* on vérifie qu'il peut danser et ne va pas percuter une chaise */
					if ((pos > -9.5) && (pos < 9.5)) 
						next_move = 'd'; 
					break;
				case 4: next_move = 's'; break;
				default : break;
			}
		}
		/* une fois le mouvement changé, on remet tempsAlea à 0 pour 
		  indiquer à la fonction qu'il faut de nouveau retirer un nombre */
		tempsAlea = 0;
	}
}


/* fonction de call-back de gestion des clicks souris */

GLvoid window_mouseFunc(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON) {
		mouse_pos_x = x;
		mouse_pos_y = y;
		mouse_down_is_left = TRUE;
	}
	else {
		mouse_down_is_left = FALSE;
	}
}

/* fonction de call-back de gestion des déplacement de la souris */

GLvoid window_motionFunc(int x, int y)
{
	if( !mouse_down_is_left )
	return;

	angle_x += y - mouse_pos_y;
	angle_y += x - mouse_pos_x;

	mouse_pos_x = x;
	mouse_pos_y = y;

	glutPostRedisplay();
}

/* fonction de call-back appelée régulièrement */

GLvoid window_timer() 
{
	t += delta;
	float sinus;
	
	/* mode automatique */
	if (mode == 1)
		automatic_key(t);
	
	/* on recadre la position du joueur lorsqu'il est face à une chaise */
	if (pos > 10) pos = 10.01;
	else if (pos < -10) pos = -10.01;
	
	/* on commance par vérifier si l'avatar n'a pas atteint une chaise */
	if ((((pos > 10) && (way == 1)) || ((pos < -10) && (way == 0)))
	&& ((move == 'r') || (move == 'm'))) {
		move = 'w'; /* l'avatar attent */
		t = 0;
	}
	
	/* pour le demi-tour, on change next_move si move == next_move pour
	 * pouvoir rentrer dans le prochain if (attente de l'avatar par défaut */
	if ((move == 's') && (next_move == 's'))
		next_move = 'w';
	
    /* transitions */
    if (next_move != move) {
		/* lorsque l'avatar marche ou court */
		if ((move == 'r') || (move == 'm')) {
			
			/* on regarde si la transition est possible */
			if (move == 'r') sinus = sin(k*t*3);
			else if (move == 'm') sinus = sin(k*t);
			
			if ((angle_Bras[Droit] > -2) && (angle_Bras[Droit] < 2) 
			&& (last_sin - sinus < 0) && (next_move != 'l')) {
				if ((next_move == 'y') && (t > 3000))  {
					move = 'w';
					next_move = 'w';
					t = 0;
				}
				else if (next_move != 'y') {
					move = next_move;
					last_pos = pos;
					t = 0;
				}
			}
		}	
		/* lorsqu'il attent debout */
		else if ((move == 'w') && (next_move != 'l')){
			if (((pos < 10) && (pos > -10)) ||
			  (((pos > 10) && (way == 0)) || ((pos < -10) && (way == 1)))) {
				move = 'x';
				last_pos = pos;
				angle_pied_gauche = 0;
				t = 0;
			}
			else if ((next_move == 'a') || (next_move == 's')) {
				move = 'x';
				last_pos = pos;
				angle_pied_gauche = 0;
				t = 0;
			}
		}
		/* lorsqu'il a finit d'attendre et peut de nouveau faire quelquechose */
		else if ((move == 'x') && (t > 300)) {
			move = next_move;
			last_pos = pos;
			t = 0;
		}
		/* lorqu'il vient de faire demi-tour */
		else if ((move == 's') && (t > 500)) {
			move = next_move;
			t = 0;
		}
		/* lorsqu'il est assis, on regarde s'il veut se lever */
		else if ((move == 'a') && (angle_Cuisse[Droit] >= 88) && (next_move == 'l')) { 
			move = 'l';
			next_move = 'w';
			t = 0;
		}
		/* lorsqu'il vient de finir de se lever et qu'un autre mouvement est en attente */
		else if ((move == 'l') && (angle_Cuisse[Droit] < 2) 
		&& ((next_move == 'm') || (next_move == 'r') || (next_move == 's') || (next_move == 'a'))) { 
			move = next_move;
			last_pos = pos;
			t = 0;
		}
		/* s'il vient de se lever et qu'aucun mouvement est demandé */
		else if ((move == 'l') && (angle_Cuisse[Droit] < 2)){
			move = 'w'; 
			next_move = 'w';
			t = 0; 
		}
		/* lorsqu'il dance */
		else if ((move == 'd') && (angle_Cuisse[Gauche] < 1) && (angle_Cuisse[Gauche] > -1)) { 
			if ((next_move == 'y') && (t > 3000))  {
				move = 'w';
				next_move = 'w';
				t = 0;
			}
			else if (next_move != 'y') {
				move = next_move;
				last_pos = pos;
				t = 0;
			}
		}
		
		if (((move == 'd') || (move == 'r') || (move == 'm')) && (move == next_move)) {
			next_move = 'y'; }
	}

	if (((move == 'd') || (move == 'r') || (move == 'm')) && (next_move == move) 
	  && (angle_Cuisse[Gauche] < 1) && (angle_Cuisse[Gauche] > -1)) {
		if (move == 'd') 
			t = 300;
		else t = 0;
		
		last_pos = pos;
		next_move = 'y';
	}
	
	/* si l'avatar commence à s'assoir et qu'il est déjà dans le bon sens, on avance le temps */
	if ((move == 'a') && ((t < 0.5*1000) && (((pos < -10) && (way == 1)) || ((pos > 10) && (way == 0)))))
		t = 500;
	
	/* appel de la fonction associée au mouvement */
	if (move == 'm')
		marcher(t);
	else if (move == 'r')
		courir(t);
	else if (move == 'a')
		sassoir(t);
	else if (move == 'l')
		seLever(t);
	else if (move == 'w')
		attendre(t);
	else if (move == 'x')
		arreterAttendre(t);
	else if (move == 's')
		demiTour(t, 0);
	else if (move == 'd')
		danser(t);
 
	glutTimerFunc(latence,&window_timer,++Step);
  
	glutPostRedisplay();
}


/* Modifie les angles de l'avatar pour le faire marcher
 * Modifie la variable change_move
 */
 
void marcher(float t) {

	sin_k_t = sin(0.001*t*6);
	
	/* modification de la position */
	if (way == 1)
		pos = last_pos + t/1000;
	else 
		pos = last_pos - t/1000;
	
	angle_Bras[Gauche]= med_Bras + amplitude_Bras*sin_k_t;
	angle_Bras[Droit]= med_Bras - amplitude_Bras*sin_k_t;
	
	angle_AvantBras[Gauche]= med_AvantBras + amplitude_AvantBras*sin_k_t;
	angle_AvantBras[Droit]= med_AvantBras- amplitude_AvantBras*sin_k_t;
	
	angle_Cuisse[Gauche]= med_Cuisse + amplitude_Cuisse*sin_k_t;
	angle_Cuisse[Droit]= med_Cuisse - amplitude_Cuisse*sin_k_t;
	
	angle_Mollet[Gauche]= med_Mollet + amplitude_Mollet*sin_k_t;
	angle_Mollet[Droit]= med_Mollet - amplitude_Mollet*sin_k_t;
	
	last_sin = sin_k_t;
}

/* Modifie les angles de l'avatar pour le faire courir
 * Modifie la variable change_move
 */
void courir(float t) {
	
	sin_k_t = sin(0.001*t*10);
	
	/* modification de la position de l'avatar */
	if (way == 1)
		pos = last_pos + 3*t/1000;
	else 
		pos = last_pos - 3*t/1000;
	
	/* modification des angles de l'avatar */
	angle_Bras[Gauche]= med_Bras + 1.6*amplitude_Bras*sin_k_t;
	angle_Bras[Droit]= med_Bras - 1.6*amplitude_Bras*sin_k_t;
	
	angle_AvantBras[Gauche]= med_AvantBras + 1.6*amplitude_AvantBras*sin_k_t;
	angle_AvantBras[Droit]= med_AvantBras- 1.6*amplitude_AvantBras*sin_k_t;
	
	angle_Cuisse[Gauche]= med_Cuisse + 1.6*amplitude_Cuisse*sin_k_t;
	angle_Cuisse[Droit]= med_Cuisse - 1.6*amplitude_Cuisse*sin_k_t;
	
	angle_Mollet[Gauche]= med_Mollet + 1.6*amplitude_Mollet*sin_k_t;
	angle_Mollet[Droit]= med_Mollet - 1.6*amplitude_Mollet*sin_k_t;
	
	last_sin = sin_k_t;
}

/* Permet au perso de s'assoir (vérifie s'il doit faire un demi-tour avant */
void sassoir(float t) {
	
	if ((t < 0.5*1000) && (((pos < -10) && (way == 0)) || ((pos > 10) && (way == 1)))) { 
		demiTour(t, 1); /* rotation de l'avatar */
	}
	else if ((t < 1000) && (t > 500)) { /* l'avatar s'assoie */
		/* angles cuisses et mollets */
		angle_Cuisse[Gauche]= 90*(t-500)/500;
		angle_Cuisse[Droit]= 90*(t-500)/500;
		angle_Mollet[Gauche]= -90*(t-500)/500;
		angle_Mollet[Droit]= -90*(t-500)/500;	
		
		/* angle bras, pour éviter la collision */
		angle_Bras[Gauche] = 10*(t-500)/500;
		angle_Bras[Droit] = 10*(t-500)/500;
		
		/* on modifie le sens de la marche */
		if (pos < -10)
			way = 1;
		else if (pos > 10)
			way = 0;
	}	
}

/* Leve le personnage (vérifier s'il est assis lors de l'appel de la fonction */

void seLever(float t) {
	
	if (t < 0.5*1000) { /* l'avatar se lève */
		angle_Cuisse[Gauche]= -45*t/250 + 90;
		angle_Cuisse[Droit]= -45*t/250 + 90;
		
		angle_Mollet[Gauche]= +45*t/250 - 90;
		angle_Mollet[Droit]= +45*t/250 - 90;	
		
		angle_Bras[Gauche] = -10*(t-500)/500;
		angle_Bras[Droit] = -10*(t-500)/500;
	}	
}

/* Fais attendre l'avatar (main sur la hanche + tappotement du pied */

void attendre(float t) {
			
	/* on met tous les angles à 0 */
	angle_Cuisse[Gauche] = 0;
	angle_Cuisse[Droit] = 0;
	
	angle_Mollet[Gauche] = 0;
	angle_Mollet[Droit] = 0;
	
	angle_Bras[Gauche]= 0;
	angle_Bras[Droit] = 0;
	
	angle_AvantBras[Gauche]= 0;
	angle_AvantBras[Droit]= 0;

	/* première étape : placement de la main sur la hanche */
	if (t <= 300){
		angle_Bras[Droit] = 30*t/300;
		angle_AvantBras[Droit]= -80*t/300;
	}
	else { /* deuxième étape : tapotement du pied et maintient de la position du bras */
		angle_Bras[Droit] = 30;
		angle_AvantBras[Droit]= -80;
		
		int t2 = t;
		/* mouvement du pied qui montre qu'il attend */
		if (t2%300 < 150)
			angle_pied_gauche = 30*(t2%300)/150;
		else angle_pied_gauche = 30 - 30*(t2%150)/150;
	}
}

/* replace progressivement le bras droit du perso */

void arreterAttendre(float t) {
	angle_Bras[Droit] = 30 -30*t/300;
	angle_AvantBras[Droit]= -80 +80*t/300;
}


/* Fait faire un demi-tour au perso.
  Les jambes montent légèrement à tour de role pendant le demi-tour 
  et les bras font des va-et-vient */
  
void demiTour(float t, int assoir) {

	if (t < 250) {
		if (t < 125) {
			angle_Cuisse[Gauche] = 20*t/125;
			angle_Mollet[Gauche] = -20*2*t/125;
			angle_Bras[Gauche] = 20*t/125;
			angle_Bras[Droit] = -20*t/125;
		}
		else {
			angle_Cuisse[Gauche] =  20 -20*(t-125)/125;
			angle_Mollet[Gauche] = -40 +20*2*(t-125)/125;
			angle_Bras[Gauche] = 20 -20*(t-125)/125;
			angle_Bras[Droit] = -20 +20*(t-125)/125;
		}
	}
	else if (t < 500) {
		if (t < 375) {
			angle_Cuisse[Droit] = 20*(t-250)/125;
			angle_Mollet[Droit] = -20*2*(t-250)/125;
			angle_Bras[Gauche] = -20*(t-250)/125;
			angle_Bras[Droit] = 20*(t-250)/125;
		}
		else {
			angle_Cuisse[Droit] =  20 -20*(t-375)/125;
			angle_Mollet[Droit] = -40 +20*2*(t-375)/125;
			angle_Bras[Gauche] = -20 +20*(t-375)/125;
			angle_Bras[Droit] = 20 -20*(t-375)/125;
		}
	}
	
	if (t > 500 - delta) {
		/* à la fin, on change le sens et on passe en attente */
		if (way == 1) way = 0;
		else way = 1;
	}
}

/* Fais danser l'avatar */ 

void danser(float t) {
	
	if (t < 300) { /* placement des bras pour la transition */
		angle_Bras[Gauche] = 30*t/300;
		angle_Bras[Droit] = 30*t/300;
		angle_AvantBras[Gauche] = 140*t/300;
		angle_AvantBras[Droit] = 140*t/300; 
		
		/* initialisation des angles des jambes */
		angle_Cuisse[Gauche] = 0;
		angle_Cuisse[Droit] = 0;
		angle_Mollet[Gauche] = 0;
		angle_Mollet[Droit] = 0;
	}
	else { /* début de la dance */
		
		/* modification de la position */
		if ((way == 1) && (pos > -9.5))
			pos = last_pos - (t-300)/2000;
		else if ((way == 0) && (pos < 9.5))
			pos = last_pos + (t-300)/2000;
		
		int t2 = t; /* permet de faire un modulo (uniquement sur entier) */
		t2 = t2%600; 
		if (t2 < 300) { /* 1ère phase */
			/* va-et-vient des jambes */
			if (t2 < 150) { 
				angle_Cuisse[Gauche] = 30*t2/150;
				angle_Cuisse[Droit] = -30*t2/150;
				angle_Mollet[Gauche] = -60 + 60*t2/150;
			
			}
			else {
				angle_Cuisse[Gauche] = 30 -30*(t2-150)/150;
				angle_Cuisse[Droit] = -30 +30*(t2-150)/150;
				angle_Mollet[Droit] = -60*(t2-150)/150;
			}
			
			/* extension des bras */
			angle_Bras[Gauche] = 90 - 80*t2/300;
			angle_Bras[Droit] = 90 - 80*t2/300;
			angle_AvantBras[Gauche] = 140*t2/300;
			angle_AvantBras[Droit] = 140*t2/300;
		}
		else { /* 2ème phase : inverse de la première */
			if (t2 < 450) {
				angle_Cuisse[Gauche] = -30*(t2-300)/150;
				angle_Cuisse[Droit] = 30*(t2-300)/150;
				angle_Mollet[Droit] = -60 + 60*(t2-300)/150;
			}
			else {
				angle_Cuisse[Gauche] = -30 +30*(t2-450)/150;
				angle_Cuisse[Droit] = 30 -30*(t2-450)/150;
				angle_Mollet[Gauche] = -60*(t2-450)/150;
			}
			angle_Bras[Gauche] = 10 + 80*(t2-300)/300;
			angle_Bras[Droit] = 10 + 80*(t2-300)/300;
			angle_AvantBras[Gauche] = 140 -140*(t2-300)/300;
			angle_AvantBras[Droit] = 140 -140*(t2-300)/300;
		}
	}
}

/* Description des composantes de l'avatar */

void Faire_Composantes() {
	
	GLUquadricObj* qobj;

	/* attribution des indentificateurs de display lists */
	Ma_Tete =  glGenLists(18); /* génère la liste des mambers */
	Mon_Tronc = Ma_Tete + 1;
	Mon_Bras = Ma_Tete + 2;
	Mon_AvantBras = Ma_Tete + 3;
	Ma_Cuisse = Ma_Tete + 4;
	Mon_Mollet = Ma_Tete + 5;
	Mon_Pied = Ma_Tete + 6;
	Ma_Main = Ma_Tete + 7;
	Ma_Casquette = Ma_Tete + 8;
	Mon_Epaule = Ma_Tete + 9;
	Mes_Pecs = Ma_Tete + 10;
	Mon_Bassin = Ma_Tete + 11;
	Mon_Cou = Ma_Tete + 12;
	Mon_Short = Ma_Tete + 13;
	Mon_Nez = Ma_Tete + 14;
	Ma_Pupille = Ma_Tete + 15;
	Ma_Retine = Ma_Tete + 16;
	Ma_Visiere = Ma_Tete + 17;
	
	/* tete objet et quadrique */
	/* compilation de la display list de la sphère */
	glNewList(Ma_Tete, GL_COMPILE );
		glutSolidSphere(1.5, 20, 20);
	glEndList();

	/* allocation d´une description de quadrique */
	qobj = gluNewQuadric();
	/* la quadrique est pleine */
	gluQuadricDrawStyle(qobj, GLU_FILL); 
	/* les ombrages, s´il y en a, sont doux */
	gluQuadricNormals(qobj, GLU_SMOOTH);


	/* compilation des display lists des cylindres */
	/* On crée les objets */
	glNewList(Mon_Cou, GL_COMPILE);
		gluCylinder(qobj, 0.8, 0.8, 2, 20, 20);
	glEndList();
 
	glNewList(Mon_Tronc, GL_COMPILE);
		gluCylinder(qobj, 2.1, 2.3, 5.5, 20, 20);
	glEndList();

	glNewList(Mes_Pecs, GL_COMPILE);
		glutSolidSphere(3, 20, 20);
	glEndList();

	glNewList(Mon_Bassin, GL_COMPILE);
		glutSolidSphere(2.1, 20, 20);
	glEndList();

	glNewList(Mon_Bras, GL_COMPILE);
		glutSolidSphere(2.5, 20, 20);
	glEndList();

	glNewList(Mon_AvantBras, GL_COMPILE);
		glutSolidSphere(2, 20, 20);
	glEndList();

	glNewList(Ma_Cuisse, GL_COMPILE); 
		glutSolidSphere(2.8, 20, 20);
	glEndList();

	glNewList(Mon_Mollet, GL_COMPILE);
		glutSolidSphere(2.8, 20, 20);
	glEndList();

	glNewList(Mon_Pied, GL_COMPILE);
		render_demi_sphere_pleine(qobj, Haut, 1, 10, 10);
	glEndList();
  
	glNewList(Ma_Main, GL_COMPILE);
		glutSolidSphere(.5, 20, 20);
	glEndList();

	glNewList(Mon_Short, GL_COMPILE);
		gluCylinder(qobj, 0.7, 0.7, 3.7, 10, 10);
	glEndList();

	glNewList(Mon_Epaule, GL_COMPILE);
		render_demi_sphere(20, 20, 0.7);
	glEndList();
	
	glNewList(Mon_Nez, GL_COMPILE); 
		glutSolidSphere(0.45, 10, 10);
	glEndList();
	
	glNewList(Ma_Pupille, GL_COMPILE); 
		glutSolidSphere(0.3, 10, 10);
	glEndList();
	
	glNewList(Ma_Retine, GL_COMPILE); 
		glutSolidSphere(0.15, 10, 10);
	glEndList();
	
	glNewList(Ma_Casquette, GL_COMPILE); 
		glutSolidSphere(1.35, 10, 10);
	glEndList();
	
	glNewList(Ma_Visiere, GL_COMPILE); 
		glutSolidSphere(1.35, 10, 10);
	glEndList();
}

/* render_demi_sphere()
 * Trace une demi-sphere fermée (pleine)
 */ 
void render_demi_sphere_pleine(GLUquadricObj* qobj, MoitieSphere moitie, double rayon, int slices, int stacks)
{
	int i, j, debut = (moitie == Haut ? slices / 2 : 0), fin = (moitie == Haut ? slices : slices / 2);
	glPushMatrix();
		glScalef(rayon, rayon, rayon);
		for(i = debut; i <= fin; ++i)
		{
			double lat0 = PI * (-0.5 + (double) (i - 1) / slices);
			double z0 = sin(lat0);
			double zr0 = cos(lat0);

			double lat1 = PI * (-0.5 + (double) i / slices);
			double z1 = sin(lat1);
			double zr1 = cos(lat1);

			glBegin(GL_QUAD_STRIP);
			for(j = 0; j <= stacks; ++j)
			{
				double lng = 2 * PI * (double) (j - 1) / stacks;
				double x = cos(lng);
				double y = sin(lng);

				glNormal3d(x * zr0, y * zr0, z0);
				glVertex3d(x * zr0, y * zr0, z0);

				glNormal3d(x * zr1, y * zr1, z1);
				glVertex3d(x * zr1, y * zr1, z1);
			}
			glEnd();
		}
		gluDisk(qobj, 0, 1, slices, stacks);
	glPopMatrix();
}

/* render_demi_sphere()
 * Trace une demi-sphere creuse 
 */ 
void render_demi_sphere(int scalex, int scaley, float r) {
	
	int i, j;
	GLfloat v[scalex*scaley][3];
 
	for (i=0; i<scalex; ++i) {
	  for (j=0; j<scaley; ++j) {
		v[i*scaley+j][0]=r*cos(j*2*M_PI/scaley)*cos(i*M_PI/(2*scalex));
		v[i*scaley+j][1]=r*sin(i*M_PI/(2*scalex));
		v[i*scaley+j][2]=r*sin(j*2*M_PI/scaley)*cos(i*M_PI/(2*scalex));
      }
	}
 
	glBegin(GL_QUADS);
      for (i=0; i<scalex-1; ++i) {
		for (j=0; j<scaley; ++j) {
          glVertex3fv(v[i*scaley+j]);
		  glVertex3fv(v[i*scaley+(j+1)%scaley]);
          glVertex3fv(v[(i+1)*scaley+(j+1)%scaley]);
          glVertex3fv(v[(i+1)*scaley+j]);
        }
      }
	glEnd();
}	



/* Modifie la "position" de la caméra : 5 positions possibles.
  Remet les angles liés à la souris à 0 si un changement est effectué */

void Camera() {
	
	if (camera == '4') glRotatef(0, 1, 0, 0);
	else if (camera == '5') glRotatef(-80, 1, 0, 0); 
	else if (camera == '6') {
		glRotatef(-80, 1, 0, 0);
		glRotatef(180, 0, 0, 1);
	}
	else if (camera == '7') {
		glRotatef(-75, 1, 0, 0);
		glRotatef(-7, 0, 0, 1);
	}
	else if (camera == '8') {
		glRotatef(-80, 1, 0, 0);
		glRotatef(-90, 0, 0, 1);
	}
	
	if (camera != last_cam) {
		angle_x = 0; 
		angle_y = 0;
		last_cam = camera;
	}
}


/* Affichage des éléments */

void render_scene()
{
	Camera();

	/* souris */
	glRotatef(angle_x, 1, 0, 0);	
	glRotatef(angle_y, 0, -1, 0);
  
	float coefScale;

	glPushMatrix();
	  translation_totale(t);

	  /* TRONC ET BASSIN (même repère) */
	  glColor3f(0.000, 0.749, 1.000);
	  glPushMatrix();
		glTranslatef(0, 0, 0.7);
		glScalef(1, 0.5, 1);
		glCallList(Mon_Tronc);
		glColor3f(1.000, 0.271, 0.000);
		glCallList(Mon_Bassin);
	  glPopMatrix();
	   
	  /* PECTORAUX */
	  glColor3f(0.000, 0.749, 1.000);
	  glPushMatrix();
		coefScale = 0.45;
		glTranslatef(0, 0.1, 6.5);
		glScalef(1, coefScale, coefScale+0.05);
		glCallList(Mes_Pecs);
	  glPopMatrix();
		
	  /* TETE, COU, NEZ ET YEUX */
	  glPushMatrix();
		glTranslatef(0, 0.1, 9.5);
		glColor3f(0.871, 0.722, 0.529);
		glCallList(Ma_Tete);
		glTranslatef(0, 0, -2);
		glTranslatef(0, -0.1, -0.2);
		glCallList(Mon_Cou);
		glTranslatef(0, 0, 2);
		glPushMatrix(); /* CASQUETTE */
			glTranslatef(0, -0.5, 1.15);
			glColor3f(0.000, 0.000, 0.545);
			glRotatef(36, 1, 0, 0);
			glCallList(Ma_Casquette);
			glTranslatef(0, -1.2, -0.15);
			glScalef(0.9, 1, 0.1);
			glCallList(Ma_Visiere);
		glPopMatrix();
		glPushMatrix(); /* NEZ */
			glTranslatef(0, 1.5, 0);
			glColor3f(0.871, 0.722, 0.529);
			glScalef(0.7, 1, 1);
			glCallList(Mon_Nez);
		glPopMatrix();
		glPushMatrix(); /* YEUX */
			glColor3f(1, 1, 1);
			glTranslatef(0.65, 1.2, 0.65);
			glCallList(Ma_Pupille);
			glTranslatef(0, 0.25, 0);
			glColor3f(0, 0, 0);
			glCallList(Ma_Retine);
			glTranslatef(-1.3, -0.25, 0);
			glColor3f(1, 1, 1);
			glCallList(Ma_Pupille);
			glTranslatef(0, 0.25, 0);
			glColor3f(0, 0, 0);
			glCallList(Ma_Retine);
		glPopMatrix();
	  glPopMatrix();
	  
	  /* CUISSE SHORT MOLLET PIED DROIT */
		glPushMatrix();			
			glTranslatef(1.1, 0, 0);
			glColor3f(1.000, 0.271, 0.000);
			glRotatef(180 + angle_Cuisse[Droit], 1, 0, 0);
			glTranslatef(0, 0, -0.25);
			glCallList(Mon_Short);
			glColor3f(0.871, 0.722, 0.529);
			glTranslatef(0, 0, 2.8);
			coefScale = 0.22;
			glScalef(coefScale, coefScale, 1);
			glCallList(Ma_Cuisse);
			glScalef(1.0/coefScale, 1.0/coefScale, 1);
			glPushMatrix();
				glTranslatef(0, 0, 2.5);
				glColor3f(0.871, 0.722, 0.529);
				glRotatef(angle_Mollet[Droit], 1, 0, 0);
				glTranslatef(0, 0, 2.4);
				coefScale = 0.18;
				glScalef(coefScale, coefScale, 1);
				glCallList(Mon_Mollet);
				glScalef(1.0/coefScale, 1.0/coefScale, 1);
				glPushMatrix();
					glTranslatef(0, 0, 2.9);
					glColor3f(0.000, 0.749, 1.000);
					glRotatef(180, 1, 0, 0);
					glScalef(0.6, 1.2, 0.8);
					glTranslatef(0, 0.5, 0);
					glCallList(Mon_Pied);
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
		

	  /* CUISSE SHORT MOLLET PIED GAUCHE */

	  glPushMatrix();						
			glTranslatef(-1.1, 0, 0);
			glColor3f(1.000, 0.271, 0.000);
			glRotatef(180 + angle_Cuisse[Gauche], 1, 0, 0);
			glTranslatef(0, 0, -0.25);
			glCallList(Mon_Short);
			glColor3f(0.871, 0.722, 0.529);
			glTranslatef(0, 0, 2.8);
			coefScale = 0.22;
			glScalef(coefScale, coefScale, 1);
			glCallList(Ma_Cuisse);
			glScalef(1.0/coefScale, 1.0/coefScale, 1);
			glPushMatrix();
				glTranslatef(0, 0, 2.5);
				glColor3f(0.871, 0.722, 0.529);
				glRotatef(angle_Mollet[Gauche], 1, 0, 0);
				glTranslatef(0, 0, 2.4);
				coefScale = 0.18;
				glScalef(coefScale, coefScale, 1);
				glCallList(Mon_Mollet);
				glScalef(1.0/coefScale, 1.0/coefScale, 1);
				glPushMatrix();
					glTranslatef(0, 0, 2.9);
					glColor3f(0.000, 0.749, 1.000);
					glRotatef(180, 1, 0, 0);
					glScalef(0.6, 1.2, 0.8);
					glRotatef(angle_pied_gauche, 1, 0, 0);
					glTranslatef(0, 0.5, 0);
					glCallList(Mon_Pied);
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
	  
	  /* AVANT BRAS BRAS ET MAIN DROITE */
	  
		   /* AVANT BRAS, BRAS, EPAULE ET MAIN DROITE */
		  glPushMatrix();
			
			glTranslatef(3, 0, 7); 					/* on place le repère pour la rotation */
			glColor3f(0.000, 0.749, 1.000);
			glRotatef(180, 1, 0, 0);				/* inversion axe Oz pour faire la rotation dans le bon sens */
			rotation_bras_droit(t);			 	/* on effectue la rotation */
			
			/* EPAULE */
			glPushMatrix();
				coefScale = 2.0;					
				glTranslatef(0, 0, 1.3);		
				glRotatef(-90, 1, 0, 0);			/* rotation de la demi-sphere (face vers le bas) */
				glScalef(1, coefScale, 1);			/* étirement de la demi-sphere */
				glCallList(Mon_Epaule);
			glPopMatrix();
			
			/* BRAS */
			coefScale = 0.17;
			glScalef(coefScale, coefScale, 1); 		/* on transforme la sphere en ellipsoïde */
			glTranslatef(0, 0, 2.7); 					/* on translate une deuxieme fois pour l'affichage du bras */
			glColor3f(0.871, 0.722, 0.529);
			glCallList(Mon_Bras);	
			glScalef((1.0/coefScale),(1.0/coefScale),1); /* on annule le glScalef précédent */
			
			/* AVANT BRAS */
			glPushMatrix();
				glTranslatef(0, 0, 2.4); 			/* même procédé (translation-rotation-translation-affichage) */
				rotation_avant_bras_droit(t);
			
				glTranslatef(0, -0.1, 1.4);
				glScalef(coefScale, coefScale, 1);
				glCallList(Mon_AvantBras);
				
				glScalef((1.0/coefScale),(1.0/coefScale),1);
				
				/* MAIN */
				glPushMatrix();
					glTranslatef(0, 0, 2.3);
					glColor3f(0.871, 0.722, 0.529);
					glScalef(0.62, 1, 1.25);
					glCallList(Ma_Main);
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
	   
	  /* AVANT BRAS BRAS ET MAIN GAUCHE */
	  
		  glPushMatrix();
			
			glTranslatef(-3, 0, 7); 					/* on place le repère pour la rotation */
			glColor3f(0.000, 0.749, 1.000);
			glRotatef(180, 1, 0, 0);				/* inversion axe Oz pour faire la rotation dans le bon sens */
			rotation_bras_gauche(t);			 	/* on effectue la rotation */
			
			/* EPAULE */
			glPushMatrix();
				coefScale = 2.0;					
				glTranslatef(0, 0, 1.3);		
				glRotatef(-90, 1, 0, 0);			/* rotation de la demi-sphere (face vers le bas) */
				glScalef(1, coefScale, 1);			/* étirement de la demi-sphere */
				glCallList(Mon_Epaule);
			glPopMatrix();
			
			/* BRAS */
			coefScale = 0.17;
			glScalef(coefScale, coefScale, 1); 		/* on transforme la sphere en ellipsoïde */
			glTranslatef(0, 0, 2.7); 					/* on translate une deuxieme fois pour l'affichage du bras */
			glColor3f(0.871, 0.722, 0.529);
			glCallList(Mon_Bras);	
			glScalef((1.0/coefScale),(1.0/coefScale),1); /* on annule le glScalef précédent */
			
			/* AVANT BRAS */
			glPushMatrix();
				glTranslatef(0, 0, 2.4); 			/* même procédé (translation-rotation-translation-affichage) */
				rotation_avant_bras_gauche(t);
				
				glTranslatef(0, -0.1, 1.4);
				glScalef(coefScale, coefScale, 1);
				glCallList(Mon_AvantBras);
				
				glScalef((1.0/coefScale),(1.0/coefScale),1);
				
				/* MAIN */
				glPushMatrix();
					glTranslatef(0, 0, 2.3);
					glColor3f(0.871, 0.722, 0.529);
					glScalef(0.62, 1, 1.25);
					glCallList(Ma_Main);
				glPopMatrix();
				
			glPopMatrix();
			
		glPopMatrix();
	
	glPopMatrix();
    
    /* translation pour le décors */
    
    /* chaises et décor */
    glPushMatrix(); 
		/* chaises */
		glTranslatef(0, -16*pos, 0);
		glTranslatef(0, 167.5, -6.7);
		glRotatef(180, 0, 0, 1);
		render_chair();
		glTranslatef(0, 167.5*2, 0);
		glRotatef(180, 0, 0, 1);
		render_chair();
		
		/* décor */
		glTranslatef(-10, -16*20, -3.95);
		render_decor();
    glPopMatrix();
    
  /* permutation des buffers lorsque le tracé est achevé */
  glutSwapBuffers();
}

/* rotations à effectuer pour le bras droit */

void rotation_bras_droit(float t)
{
	if((move == 'm') || (move == 'r') || (move == 'd') || (move == 'a') 
	  || (move == 'l')) 
		glRotatef(angle_Bras[Droit], 1, 0, 0);
	else if ((move == 'w') || (move == 'x')) {
		glRotatef(angle_Bras[Droit], 0, 1, 0);
	}
}

/* rotations à effectuer pour l'avant-bras droit */

void rotation_avant_bras_droit(float t)
{
	if((move == 'm') || (move == 'r') || (move == 'd')) { 
		if (move == 'd') {
			int t2 = t;
			t2 = t2%600;
			if (t2 < 300)
				glTranslatef(0, -t2/(300.0*2.1), 0);
			else
				glTranslatef(0, -(300.0/(300.0*2.1)) +(t2-300.0)/(300.0*2.1), 0);
		}
		glRotatef(angle_AvantBras[Droit], 1, 0, 0);
	}
	else if ((move == 'w') || (move == 'x')) {
		if (move == 'x')
			glTranslatef(-0.48 + 0.45*t/300, 0, 0);
		else if (t < 300)
			glTranslatef(-0.48 + 0.45*(300-t)/300, 0, 0);
		else glTranslatef(-0.48, 0, 0);
			
		glRotatef(angle_AvantBras[Droit], 0, 1, 0);
	}
}

/* rotations à effectuer pour le bras gauche */

void rotation_bras_gauche(float t)
{
	if((move == 'm') || (move == 'r') || (move == 'd') || (move == 'a') || (move == 'l'))
		glRotatef(angle_Bras[Gauche], 1, 0, 0);
	else if (move == 'w') {
		glRotatef(angle_Bras[Gauche], 0, 1, 0);
	}
}

/* rotations à effectuer pour l'avant-bras gauche */

void rotation_avant_bras_gauche(float t)
{
	if((move == 'm') || (move == 'r') || (move == 'd')) {
		if (move == 'd') {
			int t2 = t;
			t2 = t2 % 600;
			if (t2 < 300)
				glTranslatef(0, -t2/(300.0*2.1), 0);
			else 
				glTranslatef(0, -(300.0/(300.0*2.1)) +(t2-300.0)/(300.0*2.1), 0);
		}
		glRotatef(angle_AvantBras[Gauche], 1, 0, 0);
	}
	else if(move == 'w') {
		glRotatef(angle_AvantBras[Gauche], 0, 1, 0);
	}
}

/* translate la totalité de l'avatar (effectue aussi les rotations pour changer de sens */

void translation_totale(float t)
{
	/* si l'avatar va vers la gauche, on fais une rotation de 180 degrés */
	if (way == 0)
		glRotatef(180, 0, 0, 1);
		
	/* s'il est assis */
	if (move == 'a') {
		/* première étape : rotation */
		if ((t <= 0.5*1000) && (((pos < -10) && (way == 0)) || ((pos > 10) && (way == 1))))
			glRotatef(t*180/500, 0, 0, 1);
		else if ((t < 1000) && (t >= 500)) { /* deuxieme étape : il s'assoit */
			glTranslatef(0, -5*(t-500)/500, -5*cos((angle_Cuisse[Gauche]*PI/180) + PI)-5);
		} //-5*cos((angle_Cuisse[Gauche]*PI/180) + PI)-5
		else if (t >= 1000) { /* dernière étape : il reste assis */
			glTranslatef(0, -5, -5);
		}
	}
	/* s'il fait un demi-tour */
	if (move == 's') {
		if (t <= 500 - delta) /* première étape : rotation */
			glRotatef(t*180/500, 0, 0, 1); 
	}
	/* s'il se lève */
	else if (move == 'l') {
		if (t < 500) { /* on lève l'avatar */
			glTranslatef(0, 5*(t/500) -5, -5*cos((angle_Cuisse[Gauche]*PI/180) + PI) -5);
		}
	}
	/* s'il court */
	else if (move == 'r') {
		glTranslatef(0, 0, 0.5*(-cos(k*t*10*2)+1));
	}

}

/* affiche la chaise */

void render_chair() { 
  
  glPushMatrix();
   glRotatef(90, 0, 0, 1);
   float scale = 0.4f;
   // on réduit de 2 la taille de la chaise
   glScalef(scale, scale, scale);
   
    glPushMatrix();
  //barre supérieur
    glTranslatef(0, 0, 1);
    glColor3f(1,1,1);
    glCallList(My_Bar);
    glPushMatrix();
		//cache trou
		glTranslatef( 0,0, 5);
		glColor3f(1,1,1);
		glCallList(My_Haut_Bar);
	glPopMatrix();
	//dossier
    glPushMatrix();
		glTranslatef( 1.15,0, 10);
		glColor3f(0.000, 0.000, 0.545);
		glScalef(0.5f, 4.f, 3.f);
		glCallList(My_Back);
	glPopMatrix();
	//siège
	glPushMatrix();
		glColor3f(0.000, 0.000, 0.545);
		glTranslatef( 5, 0, 0);
		glRotatef(90, 0, 1, 0);
		glScalef(.5f, 3.f, 2.f);
		glCallList(My_Plan);
	glPopMatrix();
  glPopMatrix();
  
  //Barre inférieure
  glPushMatrix();
	glTranslatef(5,0, -7);
	glColor3f(1,1,1);
	glCallList(My_Feet);
  glPopMatrix();
  
  //création des barres sopport
  glPushMatrix();
	//1ere barre
	glRotatef(90, 0, 1, 0);
	glTranslatef( 8, 0, 0);
	glColor3f(1,1,1);
	glCallList(My_Feet1);
	glPushMatrix();
		//2 ème barre
		glTranslatef( 0, 5, 5);
		glRotatef(90, 1, 0, 0);
		glColor3f(1,1,1);
		glCallList(My_Feet1);
		
		//1ere roue
		glPushMatrix();
			glColor3f(0.2,0,0);
			glScalef(1.70f, 1.2f, 1.2f);
			glTranslatef( 0.2, 0, -0.1);
			glCallList(My_Roue1);
		glPopMatrix();
		
		//2ème roue
		glPushMatrix();
			glScalef(1.70f, 1.2f, 1.2f);
			glTranslatef( 0.2, 0, 8);
			glColor3f(0.2,0,0);
			glCallList(My_Roue1);
		glPopMatrix();
	glPopMatrix();
	
	//3eme roue
	glPushMatrix();
		glScalef(1.70f, 1.2f, 1.2f);
		glTranslatef( 0.2, 0, 8);
		glColor3f(0.2,0,0);
		glCallList(My_Roue1);
	glPopMatrix();
	
	//4eme roue
	glPushMatrix();
		glScalef(1.70f, 1.2f, 1.2f);
		glTranslatef( 0.2, 0, 0);
		glColor3f(0.2,0,0);
		glCallList(My_Roue1);
	glPopMatrix();
  glPopMatrix();
  
  glPopMatrix();
}

/* Description des éléments de la chaise */

void Faire_Chaise() {
	GLUquadricObj* qobj;

	// attribution des indentificateurs de display lists
	My_Plan =  glGenLists(7);
	My_Back = My_Plan + 1;
	My_Bar = My_Plan + 2;
	My_Feet = My_Plan + 3;
	My_Haut_Bar = My_Plan + 4;
	My_Feet1 = My_Plan + 5;
	My_Roue1 = My_Plan + 6;


	/* allocation d´une description de quadrique */
	qobj = gluNewQuadric();
	/* la quadrique est pleine */
	gluQuadricDrawStyle(qobj, GLU_FILL);
	/* les ombrages, s´il y en a, sont doux */
	gluQuadricNormals(qobj, GLU_SMOOTH);


	/* compilation des display lists des cylindres */
	/* On crée les objets */
 
	glNewList(My_Back, GL_COMPILE);
		glutSolidSphere( 2.0 , 20, 20 );
	glEndList();

	glNewList(My_Bar, GL_COMPILE);
		gluCylinder(qobj, 1, 1, 5, 20, 20);
	glEndList();

	/* haut de la barre */
	glNewList(My_Haut_Bar, GL_COMPILE);
		glutSolidSphere( 1, 20, 20 );
	glEndList();

	/* le siège */
	glNewList(My_Plan, GL_COMPILE);
		glutSolidSphere( 3.0 , 20, 20 );
	glEndList();

	/* la barre support */
	glNewList(My_Feet, GL_COMPILE);
		gluCylinder(qobj, 1.25, 1.25, 8, 20, 20);
	glEndList();

	/* bas de la barre support */
	glNewList(My_Feet1, GL_COMPILE);
		gluCylinder(qobj, 1, 1, 10, 20, 20);
	glEndList();

	/* roue de la barre support */
	glNewList(My_Roue1, GL_COMPILE);
		glutSolidSphere( 1.0 , 20, 20 );
	glEndList();
}

/* affiche le décors */

void render_decor() {
	
	int i;
	/* le sol, de 2 couleurs différentes */
	glPushMatrix();
		for (i=0; i<50; i++) {
			if (i%2 == 0) 
				glColor3f(0.9, 0.9, 0.9);
			else 
				glColor3f(0.75, 0.75, 0.75);
			glCallList(Mon_Sol);
			glTranslatef(0, 20, 0);
		}
		glTranslatef(0, -20*50, 0);
	glPopMatrix();
	
	/* les murs d'une seule couleur */
	glColor3f(0.8, 0.4, 0.4);
	glPushMatrix();
		glRotatef(90, 0, 1, 0);
		glTranslatef(-50, 0, 0);
		glCallList(Mon_Mur_Longueur);
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(-50, 0, 50);
		glCallList(Mon_Toit);
	glPopMatrix();
}
 
/* Description des éléments du décors */
 
void Faire_Decor() {
  
	GLUquadricObj* qobj;

	/* attribution des indentificateurs de display lists */
	Mon_Sol =  glGenLists(7);
	Mon_Mur_Longueur = Mon_Sol + 1;
	Mon_Toit = Mon_Sol + 2;

	/* allocation d´une description de quadrique */
	qobj = gluNewQuadric();
	/* la quadrique est pleine */
	gluQuadricDrawStyle(qobj, GLU_FILL);
	/* les ombrages, s´il y en a, sont doux */
	gluQuadricNormals(qobj, GLU_SMOOTH);
	
	glNewList(Mon_Sol, GL_COMPILE);
		glRectf( 0, 0, 500, 20);
	glEndList();
  
	glNewList(Mon_Mur_Longueur, GL_COMPILE);
		glRectf( 0, 0, 50, 50*20);
	glEndList();
  
	glNewList(Mon_Toit, GL_COMPILE);
		glRectf( 0, 0, 50, 50*20);
	glEndList();
}

