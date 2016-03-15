#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>


float xRotation = 0.0, yRotation = 0.0;
float zTranslate = -3.0;

int npts = 100;


void init(void) 
{
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glClear (GL_COLOR_BUFFER_BIT);
   glEnable(GL_DEPTH_TEST);
   glLoadIdentity ();
   gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}


void my_timer(int v)
{
   xRotation += .75;
   yRotation += .375;
   glutTimerFunc(40, my_timer, 1);

   glutPostRedisplay();
}



void display(void)
{
   double step = (2*M_PI)/npts;

   double cos_values[npts];
   double sin_values[npts];
   int pt;

   for(pt=0; pt<npts; pt++){
      cos_values[pt]=cos((pt+1)*step);
      sin_values[pt]=sin((pt+1)*step);
   }

   glClear (GL_COLOR_BUFFER_BIT);
   glClear (GL_DEPTH_BUFFER_BIT);

   glPushMatrix();
   glTranslatef(0.0, 0.0, zTranslate);
   glRotatef(xRotation, 1, 0, 0);
   glRotatef(yRotation, 0, 1, 0);
   glScalef(2.0,2.0,2.0);

   // rond jaune
   glColor3f (1.0, 1.0, 0.0);
   glBegin(GL_POLYGON);
      for(pt=0; pt<npts; pt++){
         glVertex3f (cos_values[pt], sin_values[pt], 0);
      }
   glEnd();

   // rond blanc
   glColor3f (1.0, 1.0, 1.0);
   glBegin(GL_POLYGON);
      for(pt=0; pt<npts; pt++){
         glVertex3f (cos_values[pt], sin_values[pt], 2);
      }
   glEnd();

   glColor3f (0.0, 0.0, 1.0);
   
   
   for(pt=0; pt<npts-1; pt++){
      glBegin(GL_POLYGON);
      glVertex3f (cos_values[pt], sin_values[pt], 0);
      glVertex3f (cos_values[pt], sin_values[pt], 2);
      glVertex3f (cos_values[pt+1], sin_values[pt+1], 2);
      glVertex3f (cos_values[pt+1], sin_values[pt+1], 0);
      glEnd();
   }
   glBegin(GL_POLYGON);
   glVertex3f (cos_values[npts-1], sin_values[npts-1], 0);
   glVertex3f (cos_values[npts-1], sin_values[npts-1], 2);
   glVertex3f (cos_values[0], sin_values[0], 2);
   glVertex3f (cos_values[0], sin_values[0], 0);
   glEnd();
   

   glPopMatrix();
   glutSwapBuffers();
}

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   glFrustum (-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
   glMatrixMode (GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
      case 27:
         exit(0);
         break;
   }
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
   glutInitWindowSize (300, 300); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow (argv[0]);
   init ();
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutTimerFunc(40, my_timer, 1);

   glutMainLoop();
   return 0;
}


