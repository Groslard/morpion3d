#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include "morpion.h"

#include "ppm.c"


// variables de texture
GLubyte* data;
int width, height;

GLuint defaultTexture;


float zTranslate = -3.0;
float ecartCube=1.5;
GLfloat    xAngle = 0.0, yAngle = 0.0, zAngle = 0.0;

Player players[2];
Player* currentPlayer;

Face faces[6];
Face* currentFace;

Cube cubes[3][3][3];

int nbFinishedFaces =0;



/**
*
*
*GAME INITIALISATION
*
*
***/
void initPlayers()
{
    players[0].pathTexture = CROIX;
    players[0].name = "Player 1";
    players[0].pts = 0;

    players[1].pathTexture = ROND;
    players[1].name = "Player 2";
    players[1].pts = 0;

    currentPlayer = &players[0];
}

GLuint createTexture(char* texPath)
{
    GLuint texNames[1];
    data=glmReadPPM(texPath, &width , &height);
    glGenTextures(1, texNames);

    glBindTexture(GL_TEXTURE_2D, texNames[0]);
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
    return texNames[0];
}

void initTextures()
{
    glClearColor (0, 0, 0, 0);
    glEnable(GL_DEPTH_TEST);

    // TODO : remplacer les 0,1,2 par une variable qu on incremente dans la fonction ?
    defaultTexture = createTexture(DEFAULT);
    players[0].texture = createTexture(ROND);
    players[0].texture = createTexture(CROIX);
}

void initFaces()
{

}

void init(void)
{
    initPlayers();
    initTextures();
    initFaces();

    glClearColor (0.0, 0.0, 1.0, 0.0);
    glClear (GL_COLOR_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glLoadIdentity ();
    gluLookAt (0.0, 0.0, -3*ecartCube, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}



/**
*
*
*GAME ALGORITHM
*
*
***/

void testFaceFinished(Face face)
{
    // Si tous les cubes de la current face sont joués:
    nbFinishedFaces = nbFinishedFaces + 1;
}

void testFaceWon(Face face)
{
    // si la face n a pas encore de winner , on regarde si il y a une combinaison gagnante.
    // Si oui, on set le joueur actif comme winner, et on incremente les pts du joueur.
}

void testGameFinished()
{
    // Si players[0].pts == 3 && players[1].pts == 3    EGALITE
    // Si players[0].pts > players[1].pts   PLAYERS 1 GAGNE
    // Si players[0].pts < players[1].pts   PLAYERS 2 GAGNE
    // Si non Si nbFinishedFaces == 6 -> on regarde lequel a le plus de points
}


/***
*
*
* DRAW FUNCTIONS
*
*
***/

void my_timer(int v)
{
    glutTimerFunc(40, my_timer, 1);
    glutPostRedisplay();
}

void rotateMorpion(char *direction)
{

    /**
    * TODO : au lieu de faire un glrotate, tu memorise de cb faut rotate, et tu fais appel au timer
    * C est donc le timer qui va se rappeler n fois jusqu a ce que le cube soit rotate comme il faut
    * il faut donc utiliser   glutTimerFunc(40, my_timer, 1) apres avoir initialisé les variables de rotation
    **/
    if(direction=="UP")
    {
        yAngle=90.0;
        glRotatef(yAngle, 1.0, 0.0, 0.0);
    }
    else if (direction=="DOWN")
    {
        yAngle=-90.0;
        glRotatef(yAngle, 1.0, 0.0, 0.0);
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

void drawCube(GLuint texName)
{

    glPushMatrix();
    glTranslatef(-0.5, -0.5, -0.5);
    glBindTexture(GL_TEXTURE_2D, texName);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    // devant

    glBegin(GL_POLYGON);
    glTexCoord2f(0.0, 0.0);
    glVertex3f (0, 0, 0);
    glTexCoord2f(0.0, 1.0);
    glVertex3f (1, 0, 0);
    glTexCoord2f(1.0, 1.0);
    glVertex3f (1, 1, 0);
    glTexCoord2f(1.0, 0.0);
    glVertex3f (0, 1, 0);
    glEnd();

    // arriere

    glBegin(GL_POLYGON);
    glTexCoord2f(0.0, 0.0);
    glVertex3f (0, 0, 1);
    glTexCoord2f(0.0, 1.0);
    glVertex3f (1, 0, 1);
    glTexCoord2f(1.0, 1.0);
    glVertex3f (1, 1, 1);
    glTexCoord2f(1.0, 0.0);
    glVertex3f (0, 1, 1);
    glEnd();

    // gauche

    glBegin(GL_POLYGON);
    glTexCoord2f(0.0, 0.0);
    glVertex3f (0, 0, 0);
    glTexCoord2f(0.0, 1.0);
    glVertex3f (0, 0, 1);
    glTexCoord2f(1.0, 1.0);
    glVertex3f (0, 1, 1);
    glTexCoord2f(1.0, 0.0);
    glVertex3f (0, 1, 0);
    glEnd();

    //droite

    glBegin(GL_POLYGON);
    glTexCoord2f(0.0, 0.0);
    glVertex3f (1, 0, 0);
    glTexCoord2f(0.0, 1.0);
    glVertex3f (1, 0, 1);
    glTexCoord2f(1.0, 1.0);
    glVertex3f (1, 1, 1);
    glTexCoord2f(1.0, 0.0);
    glVertex3f (1, 1, 0);
    glEnd();

    //dessous

    glBegin(GL_POLYGON);
    glTexCoord2f(0.0, 0.0);
    glVertex3f (0, 0, 0);
    glTexCoord2f(0.0, 1.0);
    glVertex3f (0, 0, 1);
    glTexCoord2f(1.0, 1.0);
    glVertex3f (1, 0, 1);
    glTexCoord2f(1.0, 0.0);
    glVertex3f (1, 0, 0);
    glEnd();

    //dessus


    glBegin(GL_POLYGON);
    glTexCoord2f(0.0, 0.0);
    glVertex3f (0, 1, 0);
    glTexCoord2f(0.0, 1.0);
    glVertex3f (0, 1, 1);
    glTexCoord2f(1.0, 1.0);
    glVertex3f (1, 1, 1);
    glTexCoord2f(1.0, 0.0);
    glVertex3f (1, 1, 0);
    glEnd();
    glTranslatef(0.5, 0.5, 0.5);
    glPopMatrix();
}

void drawMorpion()
{

    int zMorpion, yMorpion, xMorpion;

    glPushMatrix();

    for(zMorpion=0; zMorpion<3; zMorpion++)
    {
        glPushMatrix();
        for(yMorpion=0; yMorpion<3; yMorpion++)
        {
            glPushMatrix();
            for(xMorpion=0; xMorpion<3; xMorpion++)
            {
                Player* cubePlayer = cubes[xMorpion][yMorpion][zMorpion].player;
                if(cubePlayer == NULL)
                {
                    drawCube(defaultTexture);
                }
                else
                {
                    drawCube(cubePlayer->texture);
                }
                glTranslatef(ecartCube, 0.0, 0.0);
            }
            glPopMatrix();
            glTranslatef(0.0, ecartCube, 0.0);
        }
        glPopMatrix();
        glTranslatef(0.0, 0.0, ecartCube);
    }
    glPopMatrix();
}

/***
*
*
* GL FUNCTIONS
*
*
***/

void display(void)
{

    glClear (GL_COLOR_BUFFER_BIT);
    glClear (GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
    glTranslatef(-ecartCube,-ecartCube,-ecartCube);
    drawMorpion();
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


/***
*
*
* KEYBOARD FUNCTIONS
*
*
***/

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



/***
*
*
* MAIN FUNCTION
*
*
***/
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

    glutMainLoop();
    return 0;
}
