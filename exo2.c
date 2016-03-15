#include <stdlib.h>
#include <GL/glut.h>

double r = 1.0, g = 0.0, b=0.0;
int delay = 1;
double color_speed = 0.0001;
/* 
  Dessine la scene 
*/
void display(void)
{
/* Vide l'ecran */
   glClear (GL_COLOR_BUFFER_BIT);

/* Dessine le polygone */
   glColor3f (1.0, 1.0, 1.0);
   // 2. primitive utilisée : GL_POLYGON, au lieu de GL_QUADS
   glBegin(GL_QUADS);
      glVertex3f (0.0, 0.0, 0.0);
      glVertex3f (0.5, 0.0, 0.0);
      glVertex3f (0.5, 0.5, 0.0);
      glVertex3f (0.0, 0.5, 0.0);
   glEnd();

   /* Dessine le triangle */
  printf("%f %f %f\n", r, g, b );
  glColor3f (r, g, b);
  // 2. primitive utilisée : GL_POLYGON, au lieu de GL_QUADS
  glBegin(GL_TRIANGLES);
  glVertex3f (0.0, 0.0, 0.0);
  glVertex3f (0.5, 0.25, 0.0);
  glVertex3f (0.0, 0.5, 0.0);
  glEnd();

/* Force le rendu maintenant */
  glFlush ();
}



void timerFunc(int x) {

  srand(time(NULL));
  int nb=rand()%3+1;
  switch(nb){
    case 1:
      if (r>=1.0){
        r=0.0;
      }else{
        r+=color_speed;
      }
      break;
    case 2:
      if (g>=1.0){
        g=0.0;
      }else{
        g+=color_speed;
      }
      break;
    case 3:
      if (b>=1.0){
        b=0.0;
      }else{
        b+=color_speed;
      }
      break;
  }
  
  glutTimerFunc(delay,timerFunc, 0);
  glutPostRedisplay();
}


/* 
  Initialisation de l'etat OpenGl
*/ 
void init (void)
{
/* Choisir la couleur d'effacement */
   glClearColor (0.0, 0.0, 0.0, 0.0);

/* Selectionner la matrice de projection */
   glMatrixMode(GL_PROJECTION);

/* Initilialise la matrice de projection */
   glLoadIdentity();

/* Clipping de cadrage */
   glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}





/* Sortie de l'application : touche ESC */
static void
key(unsigned char k, int x, int y)
{
  switch (k) {
  case 27:  /* Escape */
    exit(0);
    break;
  default:
    return;
  }
  glutPostRedisplay();
}

int main(int argc, char** argv)
{

/* Initialisation de la GLUT */
   glutInit(&argc, argv);


/* Choix du mode d'affichage */
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);


/* Creation de la fenetre puis choix de  
   sa taille et de sa position
*/
   glutInitWindowSize (250, 250);
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("exo1");

   init ();

/* Connexion callbacks puis boucle d'evenements */
   glutDisplayFunc(display);
   glutKeyboardFunc(key);
   glutTimerFunc(delay,timerFunc, 0);
   glutMainLoop();


   return 0;  
}