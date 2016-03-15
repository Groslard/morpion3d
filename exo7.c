#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define npts 100

float ex=0.0;
float ey=3.0;
float ez=-2.0;

float dimx = 1;
float dimy = 1;
float dimz = 1;

double cos_values[npts];
double sin_values[npts];

void init(void) 
{
   glClearColor (0.0, 0.0, 1.0, 0.0);
   glEnable (GL_DEPTH_TEST);

   int pt;
   

   double step = (2*M_PI)/npts;
   for(pt=0; pt<npts; pt++){
      cos_values[pt]=cos((pt+1)*step)/2;
      sin_values[pt]=sin((pt+1)*step)/2;
   }
}

void drawCylindre(float r, float g, float b){
   glPushMatrix();
   glTranslatef(0.0, -0.5, 0.0);
   glColor3f (r, g, b);
   int pt;
   
   
   glBegin(GL_POLYGON);
      for(pt=0; pt<npts; pt++){
         glVertex3f (cos_values[pt], 0, sin_values[pt]);
      }
   glEnd();

   glBegin(GL_POLYGON);
      for(pt=0; pt<npts; pt++){
         glVertex3f (cos_values[pt], 0.5, sin_values[pt]);
      }
   glEnd();

   for(pt=0; pt<npts-1; pt++){
      glBegin(GL_POLYGON);
      glVertex3f (cos_values[pt], 0, sin_values[pt]);
      glVertex3f (cos_values[pt], 0.5, sin_values[pt]);
      glVertex3f (cos_values[pt+1], 0.5, sin_values[pt+1]);
      glVertex3f (cos_values[pt+1], 0, sin_values[pt+1]);
      glEnd();
   }
   glBegin(GL_POLYGON);
   glVertex3f (cos_values[npts-1], 0, sin_values[npts-1]);
   glVertex3f (cos_values[npts-1], 0.5, sin_values[npts-1]);
   glVertex3f (cos_values[0], 0.5, sin_values[0]);
   glVertex3f (cos_values[0], 0, sin_values[0]);
   glEnd();
   glPopMatrix();
}



void drawCube(float r, float g, float b){
   glPushMatrix();
   glTranslatef(-0.5, -0.5, -0.5);

   glColor3f (0.5, 0.5, 0.5);
   // devant
   glBegin(GL_POLYGON);
      glVertex3f (0, 0, 0);
      glVertex3f (1, 0, 0);
      glVertex3f (1, 1, 0);
      glVertex3f (0, 1, 0);
   glEnd();

   // arriere
   glBegin(GL_POLYGON);
      glVertex3f (0, 0, 1);
      glVertex3f (1, 0, 1);
      glVertex3f (1, 1, 1);
      glVertex3f (0, 1, 1);
   glEnd();

   // gauche
   glBegin(GL_POLYGON);
      glVertex3f (0, 0, 0);
      glVertex3f (0, 0, 1);
      glVertex3f (0, 1, 1);
      glVertex3f (0, 1, 0);
   glEnd();

   //droite
   glBegin(GL_POLYGON);
      glVertex3f (1, 0, 0);
      glVertex3f (1, 0, 1);
      glVertex3f (1, 1, 1);
      glVertex3f (1, 1, 0);
   glEnd();

   //dessous
   glBegin(GL_POLYGON);
      glVertex3f (0, 0, 0);
      glVertex3f (0, 0, 1);
      glVertex3f (1, 0, 1);
      glVertex3f (1, 0, 0);
   glEnd();
   
   //dessus
   glColor3f (r, g, b);
   glBegin(GL_POLYGON);
      glVertex3f (0, 1, 0);
      glVertex3f (0, 1, 1);
      glVertex3f (1, 1, 1);
      glVertex3f (1, 1, 0);
   glEnd();

   glPopMatrix();
}

void display(void)
{
   glLoadIdentity();
   gluLookAt (ex, ey, ez, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0);
   glScalef(dimx, dimy, dimz);

   glClear (GL_COLOR_BUFFER_BIT);
   glClear (GL_DEPTH_BUFFER_BIT);
   
   glPushMatrix();

   int numl, numc;
   for(numl=0; numl<10; numl++){
      glPushMatrix();
      for(numc=0; numc<10; numc++){
         if((numc+numl)%2==0){
            drawCube(1,1,1);

            glTranslatef(0.0, 1.0, 0.0);
            if(numc<4)
               drawCylindre(0.5, 0.5, 0.5);
            if(numc>6)
               drawCylindre(1, 1, 0.0);
            glTranslatef(0.0, -1.0, 0.0);
         }else{
            drawCube(0,0,0);
         }
         glTranslatef(0.0, 0.0, 1.0);
      }
      glPopMatrix();
      glTranslatef(1.0, 0.0, 0.0);
   }
   
   // drawCylindre(1,1,1);
   // drawCube(0,0,0);

   

   glPopMatrix();
   glutSwapBuffers();
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
   glutKeyboardFunc(keyboard);

   glutMainLoop();
   return 0;
}




