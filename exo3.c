#include <GL/glut.h>
#include <stdlib.h>


float xRotation = 0.0, yRotation = 0.0;
float zTranslate = -3.0;


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

   glClear (GL_COLOR_BUFFER_BIT);
   glClear (GL_DEPTH_BUFFER_BIT);

   glPushMatrix();
   glTranslatef(0.0, 0.0, zTranslate);
   glRotatef(xRotation, 1, 0, 0);
   glRotatef(yRotation, 0, 1, 0);
   glScalef(2.0,2.0,2.0);

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


