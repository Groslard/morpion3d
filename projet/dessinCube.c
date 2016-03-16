#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>


float zTranslate = -3.0;
float ecartCube=1.5;
GLfloat    xAngle = 0.0, yAngle = 0.0, zAngle = 0.0;



void init(void)
{
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glClear (GL_COLOR_BUFFER_BIT);
   glEnable(GL_DEPTH_TEST);
   glLoadIdentity ();
   gluLookAt (0.0, 0.0, -5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

}


void my_timer(int v)
{

   glutTimerFunc(40, my_timer, 1);

   glutPostRedisplay();
}
void rotateMorpion(char *direction){
// replacement au milieu

if(direction=="UP"){
    yAngle=90.0;
 glRotatef(yAngle, 0.0, 0.0, 1.0);
}else if (direction=="DOWN"){
yAngle=-90.0;
 glRotatef(yAngle, 0.0, 0.0, 1.0);
}else if (direction=="LEFT"){
xAngle=90.0;
 glRotatef(xAngle, 0.0, 1.0, 0.0);
}else if (direction=="RIGHT"){
xAngle=-90.0;
 glRotatef(xAngle, 0.0, 1.0, 0.0);
}




}

void drawCube(float r, float g, float b){
   glPushMatrix();
   glTranslatef(-0.5, -0.5, -0.5);

   glColor3f (r, g, b);
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
 glTranslatef(0.5, 0.5, 0.5);
   glPopMatrix();

}



void display(void)
{

   glClear (GL_COLOR_BUFFER_BIT);
   glClear (GL_DEPTH_BUFFER_BIT);

   glPushMatrix();
   int zMorpion, yMorpion, xMorpion;

   glTranslatef(-ecartCube,-ecartCube,0.0);

      for(zMorpion=0; zMorpion<3; zMorpion++){
  glPushMatrix();
    for(yMorpion=0; yMorpion<3; yMorpion++){
           glPushMatrix();
        for(xMorpion=0; xMorpion<3; xMorpion++){
            //colorie des cubes pour ce reperer lors de la translations
               drawCube(xMorpion,yMorpion,zMorpion);
//
//        // translate profondeur
         glTranslatef(ecartCube, 0.0, 0.0);
        }
        glPopMatrix();
        glTranslatef(0.0, ecartCube, 0.0);
      }
     glPopMatrix();
      glTranslatef(0.0, 0.0, ecartCube);
   }
 glTranslatef(ecartCube,0.0,0.0);
   glPopMatrix();

   glutSwapBuffers();
}

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
  gluPerspective(120,w/h,0,5);
   glMatrixMode (GL_MODELVIEW);
}



//utilisation des fleches claviers
void SpecialInput(int key, int x, int y)
{
switch(key)
{
case GLUT_KEY_UP:
rotateMorpion("UP");
break;
case GLUT_KEY_DOWN:
rotateMorpion("DOWN");
break;
case GLUT_KEY_LEFT:
rotateMorpion("LEFT");
break;
case GLUT_KEY_RIGHT:
rotateMorpion("RIGHT");
break;
}

glutPostRedisplay();
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
   glutSpecialFunc(SpecialInput);
   glutKeyboardFunc(keyboard);
   glutTimerFunc(40, my_timer, 1);

   glutMainLoop();
   return 0;
}

