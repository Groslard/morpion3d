#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


// Transformation de modele = transfomration de matrice (gl translate, gl rotate...)
// transformation de visualisation = deplacement de la camera : glulookat

// Q1 : rotate
// Q2 : rotate + translate


float size = 1.0;

float xRotation = 0.0, yRotation = 0.0;

void init(void) 
{
   glClearColor (0.0, 0.0, 1.0, 0.0);
   glEnable (GL_DEPTH_TEST);
   glLoadIdentity();
}

void my_timer(int v)
{
   xRotation += .75;
   yRotation += .375;
   glutTimerFunc(40, my_timer, 1);
   glutPostRedisplay();
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

   // bleu
   //droite
   glColor3f (0.0, 0.0, 1.0);
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
   glEnd();
}

void display(void)
{
   glLoadIdentity ();
   gluLookAt (0.0, 0.0, -2.0, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0);
   glClear (GL_COLOR_BUFFER_BIT);
   glClear (GL_DEPTH_BUFFER_BIT);
   
   glPushMatrix();
   
   glTranslatef(size/2, size/2, size/2);
   glRotatef(xRotation, 1, 0, 0);
   glTranslatef(-size/2, -size/2, -size/2);
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
   gluPerspective(120,w/h,1,3);
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




