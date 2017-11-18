/*  AVATAR.H */

#ifndef _AVATAR_
#define _AVATAR_

#include <GL/gl.h>           
#include <GL/glu.h>         
#include <GL/glut.h>    
#include <time.h>

#include <stdio.h>
#include <stdlib.h>     
#include <math.h>


/* *** CONSTANTES *** */

#define  windowWidth 800
#define  windowHeight 600

#define true  1
#define false 0
#define TRUE  1
#define FALSE 0

#define KEY_ESC 27
#define KEY_LEFT 37
#define KEY_RIGHT 39

#define PI 3.1415926535898

#define position_Ini                   0.0


/* *** VARIABLES GLOBALES *** */

/* variables temporelles */
float t = 0.f;
float last_t = 0.f;
float delta = 10.f;
int tempsAlea = 0;
float k = 0.001f;
float K = 0.002f;
int IdleRunning = true;

/* paramètres souris et caméra */
int angle_x = 0, angle_y = 0;
int mouse_pos_x = 0, mouse_pos_y = 0;
int mouse_down_is_left = FALSE;
char camera = '7';
char last_cam = '7';


/* *** GEOMETRIE DE L'AVATAR *** */

/* l'avatar */
int  Ma_Tete;
int  Mon_Tronc;
int  Mon_Bras;
int  Mon_AvantBras;
int  Ma_Cuisse;
int  Ma_Main;
int  Mon_Mollet;
int  Mon_Repere;
int  Mon_Pied;
int  Mon_Epaule;
int  Mes_Pecs;
int  Mon_Bassin;
int  Mon_Cou;
int  Mon_Short;	
int  Mon_Nez;
int  Ma_Pupille;
int  Ma_Retine;
int  Ma_Casquette;
int  Ma_Visiere;

/* chaise */
int My_Feet;
int My_Back;
int My_Plan;
int My_Bar;
int My_Haut_Bar;
int My_Feet1;
int My_Roue1;

/* décor */
int Mon_Sol;
int Mon_Mur_Longueur;
int Mon_Toit;

/* gestion de la lumière */
static GLfloat mat_specular[] = { 1.0 , 1.0 , 1.0 , 1.0 };
static GLfloat mat_ambientanddiffuse[] = { 0.4, 0.4 , 0.0 , 1.0 };
static GLfloat mat_shininess[] = { 20.0};
static GLfloat light_position0[] = { 15.0 , 15.0 , 15.0 , 0.0 };
static GLfloat light_position1[] = { 15.0 , 15.0 , -15.0 , 0.0 };
static GLfloat ambient_light0[] = { 0.0 , 0.0 , 0.0 , 0.0 };
static GLfloat diffuse_light0[] = { 0.7 , 0.7 , 0.7 , 1.0 };
static GLfloat specular_light0[] = { 0.1 , 0.1 , 0.1 , 0.1 };
static GLfloat ambient_light1[] = { 0.50 , 0.50 , 0.50 , 1.0 };
static GLfloat diffuse_light1[] = { 0.5 , 1.0 , 1.0 , 1.0 };
static GLfloat specular_light1[] = { 0.5 , 1.0 , 1.0 , 1.0 };


int Step = 0;
int latence = 4;


/* *** ANGLES *** */

enum lateralite{ Gauche = 0, Droit };

float angle_Bras[2];
float angle_AvantBras[2];
float angle_Cuisse[2];
float angle_Mollet[2];
float angle_Main[2];

float angle_Bras_Ini[2] = {-30.0, 15.0};
float angle_AvantBras_Ini[2] = {0.0, 30.0};
float angle_Cuisse_Ini[2] = {20.0, -20.0};
float angle_Mollet_Ini[2] = {0.0, -20.0};
float angle_pied_gauche = 0.0;

float amplitude_Bras;
float amplitude_AvantBras;
float amplitude_Cuisse;
float amplitude_Mollet;
float amplitude_Pied;

float med_Bras;
float med_AvantBras;
float med_Cuisse;
float med_Mollet;
float med_Main;

char move = 'w'; /* mouvement actuel */
char next_move = 'w'; /* prochain mouvement à exécuter */
int way = 1; /* désigne le sens dans lequel va l'avatar (1 pour droite, 0 pour gauche) */
int mode = 0; /* désigne le mode utilisé : automatique ou manuel */

/* positions */
float pos = 0.f;
float last_pos = 0.f;

/* sinus */
float sin_k_t;
float last_sin;


/* *** FONCTIONS *** */

/* mouvements */
char attaque; /* décrit si c'est la jambe gauche ou droite qui avance 
					lors de la marche et de la course */
char start = 'd'; /* décrit l'attaque au début de l'appel à marcher ou courir */
void marcher(float t);
void courir(float t);
void sassoir(float t);
void seLever(float t);
void attendre(float t);
void arreterAttendre(float t);
void demiTour(float t, int assoir);
void danser(float t);
void automatic_key(float t);

/* graphique */
void init_scene();
void render_scene();
void init_angles();
GLvoid initGL();
GLvoid window_display();
GLvoid window_reshape(GLsizei width, GLsizei height); 
GLvoid window_key(unsigned char key, int x, int y); 
GLvoid window_timer(); 
void Faire_Composantes();

/* souris */
GLvoid window_mouseFunc(int button, int state, int x, int y);
GLvoid window_motionFunc(int x, int y);
GLuint raw_texture_load(const char *filename, int width, int height);
		
/* décors */
void render_chair();
void Faire_Chaise();
void render_decor();
void Faire_Decor();

/* rotations et translations */
void rotation_bras_droit(float t);
void rotation_avant_bras_droit(float t);
void rotation_bras_gauche(float t);
void rotation_avant_bras_gauche(float t);
void translation_totale(float t);
void Camera();

/* demi-spheres */
typedef enum { Haut, Bas } MoitieSphere; /* enum nécessaire pour la fonction qui suit */
void render_demi_sphere_pleine(GLUquadricObj* qobj, MoitieSphere moitie, double rayon, int slices, int stacks);
void render_demi_sphere(int scalex, int scaley, float r);


#endif

