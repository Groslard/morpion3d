#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define X .525731112119133606
#define Z .850650808352039932

GLfloat sommets[12][3] =
{
  {-X, 0, Z},
  {X, 0, Z},
  {-X, 0, -Z},
  {X, 0, -Z},
  {0, Z, X},
  {0, Z, -X},
  {0, -Z, X},
  {0, -Z, -X},
  {Z, X, 0},
  {-Z, X, 0},
  {Z, -X, 0},
  {-Z, -X, 0}
};

int sindex[20][3] =
{
  {0, 4, 1},
  {0, 9, 4},
  {9, 5, 4},
  {4, 5, 8},
  {4, 8, 1},
  {8, 10, 1},
  {8, 3, 10},
  {5, 3, 8},
  {5, 2, 3},
  {2, 7, 3},
  {7, 10, 3},
  {7, 6, 10},
  {7, 11, 6},
  {11, 0, 6},
  {0, 1, 6},
  {6, 1, 10},
  {9, 0, 11},
  {9, 11, 2},
  {9, 2, 5},
  {7, 2, 11},
};

float ex=0.0;
float ey=0.0;
float ez=2.0;

float dimx = 1;
float dimy = 1;
float dimz = 1;

float xRotation = 0.0;



void init(void) 
{
   glClearColor (0.0, 0.0, 1.0, 0.0);
   glEnable (GL_DEPTH_TEST);
   
}

void my_timer(int v)
{
   xRotation += 1.0;

   glutTimerFunc(40, my_timer, 1);
   glutPostRedisplay();
}

void draw_triangle(float* v1, float *v2, float *v3){
   
   glBegin(GL_TRIANGLES);
      glColor3f (1.0, 0.0, 0.0);
      glVertex3f (v1[0], v1[1], v1[2]);
      glColor3f (1.0, 1.0, 1.0);
      glVertex3f (v2[0], v2[1], v2[2]);
      glColor3f (1.0, 0.0, 0.0);
      glVertex3f (v3[0], v3[1], v3[2]);
   glEnd();
}

void display(void)
{
   glLoadIdentity();
   gluLookAt (ex, ey, ez, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0);
   glScalef(dimx, dimy, dimz);

   glClear (GL_COLOR_BUFFER_BIT);
   glClear (GL_DEPTH_BUFFER_BIT);
   
   glPushMatrix();
   glRotatef(xRotation, 1, 0, 0);
   int pt;
   for(pt=0; pt<20; pt++){
      draw_triangle(sommets[sindex[pt][0]], sommets[sindex[pt][1]], sommets[sindex[pt][2]]);
   }
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
   glutTimerFunc(40, my_timer, 1);

   glutMainLoop();
   return 0;
}




