#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include "morpion.h"


float zTranslate = -3.0;
float ecartCube=1.5;
GLfloat    xAngle = 0.0, yAngle = 0.0, zAngle = 0.0;

Player players[2];
Player* currentPlayer;

Face faces[6];
Face* currentFace;

Cube cubes[3][3][3];

int nbFinishedFaces =0;


void init(void)
{
    glClearColor (0.0, 0.0, 1.0, 0.0);
    glClear (GL_COLOR_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glLoadIdentity ();
    gluLookAt (0.0, 0.0, -2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void initPlayers(){

}

void initCubes(){
}

void initFaces(){

}

void testFaceFinished(Face face){
    // Si tous les cubes de la current face sont joués:
    nbFinishedFaces = nbFinishedFaces + 1;
}

void testFaceWon(Face face){
    // si la face n a pas encore de winner , on regarde si il y a une combinaison gagnante.
    // Si oui, on set le joueur actif comme winner, et on incremente les pts du joueur.
}

void testGameFinished(){
    // Si players[0].pts == 3 && players[1].pts == 3    EGALITE
    // Si players[0].pts > players[1].pts   PLAYERS 1 GAGNE
    // Si players[0].pts < players[1].pts   PLAYERS 2 GAGNE
    // Si non Si nbFinishedFaces == 6 -> on regarde lequel a le plus de points
}

void my_timer(int v)
{
    glutTimerFunc(40, my_timer, 1);
    glutPostRedisplay();
}

void rotateMorpion(char *direction)
{
// replacement au milieu
    if(direction=="UP")
    {
        yAngle=90.0;
        glRotatef(yAngle, 0.0, 0.0, 1.0);
    }
    else if (direction=="DOWN")
    {
        yAngle=-90.0;
        glRotatef(yAngle, 0.0, 0.0, 1.0);
    }
    else if (direction=="LEFT")
    {
        xAngle=90.0;
        glRotatef(xAngle, 0.0, 1.0, 0.0);
    }
    else if (direction=="RIGHT")
    {
        xAngle=-90.0;
        glRotatef(xAngle, 0.0, 1.0, 0.0);
    }
}

void drawCube(float r, float g, float b)
{
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

    for(zMorpion=0; zMorpion<3; zMorpion++)
    {
        glPushMatrix();
        for(yMorpion=0; yMorpion<3; yMorpion++)
        {
            glPushMatrix();
            for(xMorpion=0; xMorpion<3; xMorpion++)
            {
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
    gluPerspective(120,w/h,1,20);
    glMatrixMode (GL_MODELVIEW);
}

//utilisation des fleches claviers
void SpecialInput(int key, int x, int y)
{
    switch(key)
    {
    case GLUT_KEY_UP:
        rotateMorpion("UP");
        // currentFace = faces[currentFace.upFaceId];
        break;
    case GLUT_KEY_DOWN:
        rotateMorpion("DOWN");
        // currentFace = faces[currentFace.downFaceId];
        break;
    case GLUT_KEY_LEFT:
        rotateMorpion("LEFT");
        // currentFace = faces[currentFace.leftFaceId];
        break;
    case GLUT_KEY_RIGHT:
        rotateMorpion("RIGHT");
        // currentFace = faces[currentFace.rightFaceId];
        break;
    }
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
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
    glutSpecialFunc(SpecialInput);
    glutKeyboardFunc(keyboard);
//    glutTimerFunc(40, my_timer, 1);

    glutMainLoop();
    return 0;
}

