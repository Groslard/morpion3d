#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

float ex=5;
float ey=5;
float ez=3;

float dimx = 1;
float dimy = 1;
float dimz = 1;

void init(void) 
{
   glClearColor (0.0, 0.0, 1.0, 0.0);
   glEnable (GL_DEPTH_TEST);
}


void drawRec(void){
   // Face rouge
   // devant
   glColor3f (1.0, 0.0, 0.0);
   glBegin(GL_POLYGON);
      glVertex3f (0, 0, 0);
      glVertex3f (1, 0, 0);
      glVertex3f (1, 1, 0);
      glVertex3f (0, 1, 0);
   glEnd();

   // jaune
   // arriere
   glColor3f (1.0, 1.0, 0.0);
   glBegin(GL_POLYGON);
      glVertex3f (0, 0, 1);
      glVertex3f (1, 0, 1);
      glVertex3f (1, 1, 1);
      glVertex3f (0, 1, 1);
   glEnd();

   // blanche
   // gauche
   glColor3f (1.0, 1.0, 1.0);
   glBegin(GL_POLYGON);
      glVertex3f (0, 0, 0);
      glVertex3f (0, 0, 1);
      glVertex3f (0, 1, 1);
      glVertex3f (0, 1, 0);
   glEnd();

   //droite
   glColor3f (1.0, 0.0, 1.0);
   glBegin(GL_POLYGON);
      glVertex3f (1, 0, 0);
      glVertex3f (1, 0, 1);
      glVertex3f (1, 1, 1);
      glVertex3f (1, 1, 0);
   glEnd();

   // gris
   //dessus
   glColor3f (0.5, 0.5, 0.5);
   glBegin(GL_POLYGON);
      glVertex3f (0, 1, 0);
      glVertex3f (0, 1, 1);
      glVertex3f (1, 1, 1);
      glVertex3f (1, 1, 0);
   glEnd();

   // vert
   //dessous
   glColor3f (0.0, 1.0, 0.0);
   glBegin(GL_POLYGON);
      glVertex3f (0, 0, 0);
      glVertex3f (0, 0, 1);
      glVertex3f (1, 0, 1);
      glVertex3f (1, 0, 0);
   glEnd();
}

void display(void)
{
   glLoadIdentity ();
   gluLookAt (ex, ey, ez, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
   printf("Position de l'oeil xyz = %f %f %f \n", ex, ey, ez);
   glClear (GL_COLOR_BUFFER_BIT);
   glClear (GL_DEPTH_BUFFER_BIT);
   glScalef(dimx, dimy, dimz);
   drawRec();

   

   glutSwapBuffers();
}

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   gluPerspective(120,w/h,1,20);
   glMatrixMode (GL_MODELVIEW);
}



void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
      case 'l':
         dimx=dimx*2;
         break;
      case 'L':
         dimx=dimx/2;
         break;
      case 'h':
         dimy=dimy*2;
         break;
      case 'H':
         dimy=dimy/2;
         break;
      case 'p':
         dimz=dimz*2;
         break;
      case 'P':
         dimz=dimz/2;
         break;
      case 'v':
         dimx=dimx*2;
         dimy=dimy*2;
         dimz=dimz*2;
         break;
      case 'V':
         dimx=dimx/2;
         dimy=dimy/2;
         dimz=dimz/2;
         break;
      case 'x':
         ex=ex+0.05;
         break;
      case 'X':
         ex=ex-0.05;
         break;
      case 'y':
         ey=ey+0.05;
         break;
      case 'Y':
         ey=ey-0.05;
         break;
      case 'z':
         ez=ez+0.05;
         break;
      case 'Z':
         ez=ez-0.05;
         break;
      case 27:
         exit(0);
         break;
   }
   glutPostRedisplay();
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
   glutInitWindowSize (500, 500); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow (argv[0]);
   init ();
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);

   glutMainLoop();
   return 0;
}




