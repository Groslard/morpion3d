#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float size = 6.0;
int npts = 60;

float incrx = 0.05;
float incry = 0.05;

float xTranslate = 0.0, yTranslate = 0.0;

void init(void) 
{
   glClearColor (0.0, 0.0, 1.0, 0.0);
   glEnable (GL_DEPTH_TEST);
   glLoadIdentity();
   gluLookAt (0.0, 0.0, -2.0, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0);
}

void my_timer(int v)
{

   xTranslate += incrx;
   yTranslate += incry;

   // les 0.1 correspondent à la moitié su cercle
   if (xTranslate >= size/2 - 0.1 )
      incrx = -0.05;
   if (xTranslate <= -size/2 + 0.1)
      incrx = 0.05;

   if (yTranslate >= size - 0.1)
      incry = -0.05;
   if (yTranslate <= 0.0 + 0.1)
      incry = 0.05;

   glutTimerFunc(40, my_timer, 1);

   glutPostRedisplay();
}

void drawRec(void){
   glColor3f (1.0, 1.0, 1.0);
   glBegin(GL_LINE_LOOP);
      glVertex3f (0, 0, 1);
      glVertex3f (size, 0, 1);
      glVertex3f (size, size, 1);
      glVertex3f (0, size, 1);
   glEnd();
}

void drawBall(void){
   double x[npts];
   double y[npts];
   double step = (2*M_PI)/npts;

   glTranslatef(xTranslate, yTranslate, 0.0);

   int pt;
   for(pt=0; pt<npts; pt++){
      x[pt]=cos((pt+1)*step)*0.1;
      y[pt]=sin((pt+1)*step)*0.1;
      // donc taille de la balle = 2*0.1 = 0.2
   }

   // rond jaune
   glColor3f (1.0, 1.0, 0.0);
   glBegin(GL_POLYGON);
      for(pt=0; pt<npts; pt++){
         glVertex3f (x[pt], y[pt], 1.0);
      }
   glEnd();
}

void display(void)
{
   glClear (GL_COLOR_BUFFER_BIT);
   glClear (GL_DEPTH_BUFFER_BIT);
   
   glPushMatrix();
   glTranslatef(-size/2.0, -size/2.0, 0.0);
   drawRec();

   glTranslatef(size/2.0, 0.0, 0.0);
   drawBall();
   
   glPopMatrix();
   glutSwapBuffers();
}

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




