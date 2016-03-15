#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


// Transformation de modele = transfomration de matrice (gl translate, gl rotate...)
// transformation de visualisation = deplacement de la camera : glulookat

// Q1 : rotate
// Q2 : rotate + translate


float size = 1.0;

float xRotation = 0.0;
float zTranslate = 0.0;

float incrz = 0.2;

void init(void) 
{
   glClearColor (0.0, 0.0, 1.0, 0.0);
   glEnable (GL_DEPTH_TEST);
   glLoadIdentity();
   gluLookAt (size/2.0, size/2.0, -2.0, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0);
}

void my_timer(int v)
{
   xRotation += 1.0;

   zTranslate += incrz;

   if (zTranslate <= 0.0)
      incrz = 0.2;
   if (zTranslate >= 10.0)
      incrz = -0.2;

   glutTimerFunc(40, my_timer, 1);
   glutPostRedisplay();
}

void drawRec(void){
   // Face rouge
   // devant
   glColor3f (1.0, 0.0, 0.0);
   glBegin(GL_POLYGON);
      glVertex3f (0, 0, 0);
      glVertex3f (size, 0, 0);
      glVertex3f (size/2.0, size, 0);
   glEnd();

   // jaune
   // arriere
   glColor3f (1.0, 1.0, 0.0);
   glBegin(GL_POLYGON);
      glVertex3f (0, 0, size);
      glVertex3f (size, 0, size);
      glVertex3f (size/2.0, size, size);
   glEnd();

   // blanche
   // gauche
   glColor3f (1.0, 1.0, 1.0);
   glBegin(GL_POLYGON);
      glVertex3f (0, 0, 0);
      glVertex3f (0, 0, 1);
      glVertex3f (size/2.0, size, size);
      glVertex3f (size/2.0, size, 0);
   glEnd();

   // bleu
   //droite
   glColor3f (1.0, 0.0, 1.0);
   glBegin(GL_POLYGON);
      glVertex3f (size, 0, 0);
      glVertex3f (size, 0, 1);
      glVertex3f (size/2.0, size, size);
      glVertex3f (size/2.0, size, 0);
   glEnd();

   // gris
   //dessous
   glColor3f (0.5, 0.5, 0.5);
   glBegin(GL_POLYGON);
      glVertex3f (0, 0, 0);
      glVertex3f (0, 0, size);
      glVertex3f (size, 0, size);
      glVertex3f (size, 0, 0);
   glEnd();
}

void display(void)
{
   glClear (GL_COLOR_BUFFER_BIT);
   glClear (GL_DEPTH_BUFFER_BIT);
   
   glPushMatrix();
   
   glTranslatef(size/2.0, size/2.0, size/2.0 + zTranslate);
   glRotatef(xRotation, 1, 0, 0);
   glTranslatef(-size/2.0, -size/2.0, -size/2.0);

   drawRec();

   glPopMatrix();
   glutSwapBuffers();
}

// Appelé quand on modifit la fenêtre
void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   gluPerspective(120,w/h,1,13);
   glMatrixMode (GL_MODELVIEW);
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
   glutTimerFunc(40, my_timer, 1);

   glutMainLoop();
   return 0;
}




