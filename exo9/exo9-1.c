#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include "ppm.c"


static GLuint texName[1];
GLubyte* data;
int width, height;

float ex=0;
float ey=0;
float ez=3;
float pas_camera=1;

void init(void)
{
   glClearColor (0, 0, 0, 0);
   glEnable(GL_DEPTH_TEST);

   data=glmReadPPM("brick10.ppm", &width , &height); 
   glGenTextures(1, texName);

   glBindTexture(GL_TEXTURE_2D, texName[0]);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
                   GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                   GL_NEAREST);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width,
                height, 0, GL_RGB, GL_UNSIGNED_BYTE,
                data);

   glEnable(GL_TEXTURE_2D);
}

void display(void)
{
   glLoadIdentity ();
   gluLookAt (ex,ey,ez,   0,0,-100.0,   0.0,1.0,0.0);
   glClear (GL_COLOR_BUFFER_BIT);
   glClear (GL_DEPTH_BUFFER_BIT);

   glBindTexture(GL_TEXTURE_2D, texName[0]);
   glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
   glColor3f(1,1,0);


   glTranslatef(-2.,0.,0);
   glBegin(GL_QUADS);
   glTexCoord2f(1.0, 1.0); glVertex3f(0.0, 0.0, 0.0);
   glTexCoord2f(0.0, 1.0); glVertex3f(1.0, 0.0, 0.0);
   glTexCoord2f(0.0, 0.0); glVertex3f(1.0, 1.0, 0.0);
   glTexCoord2f(1.0, 0.0); glVertex3f(0.0, 1.0, 0.0);
   glEnd();

   glTranslatef(2.,0.,0);

   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0); glVertex3f(0.0, 0.0, 0.0);
   glTexCoord2f(0.0, 1.0); glVertex3f(1.0, 0.0, 0.0);
   glTexCoord2f(1.0, 1.0); glVertex3f(1.5, 1.0, 0.0);
   glTexCoord2f(1.0, 0.0); glVertex3f(0.5, 1.0, 0.0);
   glEnd();

   glTranslatef(-2.,-2.0,0);

   glBegin(GL_TRIANGLES);
   glTexCoord2f(0.0, 0.0); glVertex3f(0.0, 0.0, 0.0);
   glTexCoord2f(0.0, 1.0); glVertex3f(0.5, 1.0, 0.0);
   glTexCoord2f(1.0, 1.0); glVertex3f(1.0, 0.0, 0.0);
   glEnd();

   glTranslatef(2.,0.0,0);

   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0); glVertex3f(0.0, 0.0, 0.0);
   glTexCoord2f(0.0, 1.0); glVertex3f(0.5, 1.0, 0.0);
   glTexCoord2f(1.0, 1.0); glVertex3f(1.0, 1.0, 0.0);
   glTexCoord2f(1.0, 0.0); glVertex3f(1.5, 0.0, 0.0);
   glEnd();


   glutSwapBuffers();
}



void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   gluPerspective(90, 1, 1, 10);
   glMatrixMode (GL_MODELVIEW);
}





void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
      case 'x':
         ex=ex+pas_camera;
         break;
      case 'X':
         ex=ex-pas_camera;
         break;
      case 'y':
         ey=ey+pas_camera;
         break;
      case 'Y':
         ey=ey-pas_camera;
         break;
      case 'z':
         ez=ez+pas_camera;
         break;
      case 'Z':
         ez=ez-pas_camera;
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
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize(500, 500);
   glutInitWindowPosition(100, 100);
   glutCreateWindow(argv[0]);
   init();
   glutReshapeFunc(reshape);
   glutDisplayFunc(display);
   glutKeyboardFunc (keyboard);
   glutMainLoop();
   return 0;
}