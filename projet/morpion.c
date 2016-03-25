#include <GL/glut.h>
#include <GL/gl.h>
#include <stdlib.h>
#include <stdio.h>
#include "morpion.h"
#include <math.h>
#include "ppm.c"


// variables de texture
GLubyte* data;
int width, height;

GLuint defaultTexture;
GLuint solTexture;


float ecartCube=1.5;

Player player1;
Player player2;

Player* currentPlayer;
Player* waintingPlayer;

Face faces[4];
Face* currentFace;

Cube cubes[3][3][3];
Cube* selectedCube;

int nbFinishedFaces =0;


int xrotate = 0;
int rotate_final = 0;
int rotate_available = VRAI;
int* temp;

float selectEffect = 1.0;
int reduce = VRAI;

//variable de sol
float largeurCarreSol=1.0;
int nbCarreSol=10;



// initialisation des variales de lumière
// Proprietes de l'objet (sa matiere)
//
GLfloat mat_ambient[] = { 0.7, 0.7, 0.7, 1.0 };
GLfloat mat_diffuse[] = { 0.1, 0.1, 0.1, 1.0 };
GLfloat mat_specular[] = { 1, 1, 1, 1 };
GLfloat mat_shininess[] = { 70.0 };
GLfloat mat_emission[] = {0, 0, 0, 0};

// Proprietes de la source lumineuse
//
GLfloat light_ambient[] = { 0.4, 0.4, 0.4, 0 };
GLfloat light_diffuse[] = { 0.3, 0.3, 0.3, 0 };
GLfloat light_specular[] = { .9, .9,.9, 0 };
GLfloat light_position[] = { -7.0, 2.0, 5.0, 1.0 };

// Proprietes generales de l'eclairage
//
GLfloat general_light_ambient[] = { 0.2, 0.2, 0.2, 1.0 };

/**
*
*
*GAME INITIALISATION
*
*
***/
void initPlayers()
{
    player1.pathTexture = CROIX;
    player1.name = "Player 1";
    player1.pts = 0;

    player2.pathTexture = ROND;
    player2.name = "Player 2";
    player2.pts = 0;

    currentPlayer = &player1;
    waintingPlayer = &player2;
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

    return texNames[0];
}

void initTextures()
{
    glClearColor (0, 0, 0, 0);
    glEnable(GL_DEPTH_TEST);

    solTexture=createTexture(SOL);
    defaultTexture = createTexture(DEFAULT);
    player1.texture = createTexture(player1.pathTexture);
    player2.texture = createTexture(player2.pathTexture);
}

void initLight()
{

    glEnable(GL_LIGHTING);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, general_light_ambient);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glEnable(GL_LIGHT0);

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);

}
void initFaces()
{
    int l, c;
    int i=0;

    for (l=0; l<3; l++)
    {
        for (c=0; c<3; c++)
        {
            // devant
            faces[0].cubes[i]=&cubes[c][l][0];
            // droite
            faces[1].cubes[i]=&cubes[2][l][c];
            // derriere
            faces[2].cubes[i]=&cubes[2-c][l][2];
            // gauche
            faces[3].cubes[i]=&cubes[0][l][2-c];
            i++;
        }
    }

    // devant
    faces[0].leftFace = &faces[3];
    faces[0].rightFace = &faces[1];

    // droite
    faces[1].leftFace = &faces[0];
    faces[1].rightFace = &faces[2];

    // derriere
    faces[2].leftFace = &faces[1];
    faces[2].rightFace = &faces[3];

    // gauche
    faces[3].leftFace = &faces[2];
    faces[3].rightFace = &faces[0];

    currentFace = &faces[0];
}

void init(void)
{
    initPlayers();
    initTextures();
    initFaces();

    glClearColor (0.3, 0.3, 0.3, 0.0);
    glClear (GL_COLOR_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glLoadIdentity ();
    gluLookAt (0.0, 0.0, -2.7*ecartCube, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

/**
*
*
*GAME ALGORITHM
*
*
***/

void endTurn()
{

    Player *tmp = currentPlayer;
    currentPlayer = waintingPlayer;
    waintingPlayer = tmp;
}

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

void select_timer(int v)
{
    if(reduce == VRAI){
        selectEffect-=0.04;
    }else{
        selectEffect+=0.04;
    }
    glutPostRedisplay();
    if(selectEffect < 0){
        reduce = FAUX;
        selectedCube->player = currentPlayer;
        selectEffect = 0.0;
    }
    if(selectEffect < 1.0){
         glutTimerFunc(1, select_timer, 1);
    }else{
        reduce = VRAI;
        selectedCube = NULL;
        endTurn();
    }

}

void selectCube(Cube* cube)
{
    if(cube->player == NULL && selectedCube == NULL){
        selectedCube = cube;
        glutTimerFunc(50, select_timer, 1);
    }
}


/***
*
*
* DRAW FUNCTIONS
*
*
***/

void rotate_timer(int v)
{
    if(xrotate < rotate_final)
    {
        xrotate += 2;
        glutTimerFunc(ROTATESPEED, rotate_timer, 1);
    }
    else if(xrotate > rotate_final)
    {
        xrotate -= 2;
        glutTimerFunc(ROTATESPEED, rotate_timer, 1);
    }
    else
    {
        if(xrotate<0)
        {
            xrotate = 360 + xrotate;
        }
        else if(xrotate >360)
        {
            xrotate = xrotate%360;
        }
        rotate_available = VRAI;
    }
    glutPostRedisplay();
}

void rotateMorpion(char *direction)
{
    if(rotate_available == VRAI)
    {
        if(direction=="RIGHT")
        {
            rotate_final = xrotate - 90;
            currentFace = currentFace->rightFace;
        }
        else if (direction=="LEFT")
        {
            rotate_final = xrotate + 90;
            currentFace = currentFace->leftFace;
        }
        glutTimerFunc(ROTATESPEED, rotate_timer, 1);
        rotate_available = FAUX;
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
    glNormal3f(0.0, 0.0, 0.0);
    glTexCoord2f(0.0, 0.0);
    glVertex3f (0, 0, 0);
    glNormal3f(1.0, 0.0, 0.0);
    glTexCoord2f(0.0, 1.0);
    glVertex3f (1, 0, 0);
    glNormal3f(1.0, 1.0, 0.0);
    glTexCoord2f(1.0, 1.0);
    glVertex3f (1, 1, 0);
    glNormal3f(0.0, 1.0, 0.0);
    glTexCoord2f(1.0, 0.0);
    glVertex3f (0, 1, 0);
    glEnd();

    // arriere
    glBegin(GL_POLYGON);
    glNormal3f(0.0, 0.0, 1.0);
    glTexCoord2f(0.0, 0.0);
    glVertex3f (0, 0, 1);
    glNormal3f(1.0, 0.0, 1.0);
    glTexCoord2f(0.0, 1.0);
    glVertex3f (1, 0, 1);
    glNormal3f(1.0, 1.0, 1.0);
    glTexCoord2f(1.0, 1.0);
    glVertex3f (1, 1, 1);
    glNormal3f(0.0, 1.0, 1.0);
    glTexCoord2f(1.0, 0.0);
    glVertex3f (0, 1, 1);
    glEnd();

    // gauche
    glBegin(GL_POLYGON);
    glNormal3f(0.0, 0.0, 0.0);
    glTexCoord2f(0.0, 0.0);
    glVertex3f (0, 0, 0);
    glNormal3f(0.0, 0.0, 1.0);
    glTexCoord2f(0.0, 1.0);
    glVertex3f (0, 0, 1);
    glNormal3f(0.0, 1.0, 1.0);
    glTexCoord2f(1.0, 1.0);
    glVertex3f (0, 1, 1);
    glNormal3f(0.0, 1.0, 0.0);
    glTexCoord2f(1.0, 0.0);
    glVertex3f (0, 1, 0);
    glEnd();

    //droite
    glBegin(GL_POLYGON);
    glNormal3f(1.0, 0.0, 0.0);
    glTexCoord2f(0.0, 0.0);
    glVertex3f (1, 0, 0);
    glNormal3f(1.0, 0.0, 1.0);
    glTexCoord2f(0.0, 1.0);
    glVertex3f (1, 0, 1);
    glNormal3f(1.0, 1.0, 1.0);
    glTexCoord2f(1.0, 1.0);
    glVertex3f (1, 1, 1);
    glNormal3f(1.0, 1.0, 0.0);
    glTexCoord2f(1.0, 0.0);
    glVertex3f (1, 1, 0);
    glEnd();

    //dessous
    glBegin(GL_POLYGON);
    glNormal3f(0.0, 0.0, 0.0);
    glTexCoord2f(0.0, 0.0);
    glVertex3f (0, 0, 0);
    glNormal3f(0.0, 0.0, 1.0);
    glTexCoord2f(0.0, 1.0);
    glVertex3f (0, 0, 1);
    glNormal3f(1.0, 0.0, 1.0);
    glTexCoord2f(1.0, 1.0);
    glVertex3f (1, 0, 1);
    glNormal3f(1.0, 0.0, 0.0);
    glTexCoord2f(1.0, 0.0);
    glVertex3f (1, 0, 0);
    glEnd();

    //dessus
    glBegin(GL_POLYGON);
    glNormal3f(0.0, 1.0, 0.0);
    glTexCoord2f(0.0, 0.0);
    glVertex3f (0, 1, 0);
    glNormal3f(0.0, 1.0, 1.0);
    glTexCoord2f(0.0, 1.0);
    glVertex3f (0, 1, 1);
    glNormal3f(1.0, 1.0, 1.0);
    glTexCoord2f(1.0, 1.0);
    glVertex3f (1, 1, 1);
    glNormal3f(1.0, 1.0, 0.0);
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
    Cube* cube;
    for(zMorpion=0; zMorpion<3; zMorpion++)
    {
        glPushMatrix();
        for(yMorpion=0; yMorpion<3; yMorpion++)
        {
            glPushMatrix();
            for(xMorpion=0; xMorpion<3; xMorpion++)
            {
                if(zMorpion!=1 || xMorpion!=1)
                {
                    glPushMatrix();
                    cube = &cubes[xMorpion][yMorpion][zMorpion];
                    if(cube == selectedCube){
                        glScalef(selectEffect, selectEffect, selectEffect);
                    }
                    Player* cubePlayer = cube->player;
                    if(cubePlayer == NULL)
                    {
                        drawCube(defaultTexture);
                    }
                    else
                    {
                        drawCube(cubePlayer->texture);
                    }
                    glPopMatrix();
                }
                glTranslatef(-ecartCube, 0.0, 0.0);
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

void printText(int x, int y, char *string, void *font)
{
    int len,i; // len donne la longueur de la chaîne de caractères

    glRasterPos2f(x,y); // Positionne le premier caractère de la chaîne
    len = (int) strlen(string); // Calcule la longueur de la chaîne
    for (i = 0; i < len; i++) glutBitmapCharacter(font,string[i]); // Affiche chaque caractère de la chaîne
}

void display(void)
{

    glClear (GL_COLOR_BUFFER_BIT);
    glClear (GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST); 	// Active le test de profondeur
    glEnable(GL_LIGHTING); 	// Active l'éclairage
    glEnable(GL_LIGHT0); 	// Allume la lumière n°1


    glPushMatrix();
    glRotatef(xrotate, 0.0, 1.0, 0.0);
    glTranslatef(ecartCube,-ecartCube,-ecartCube);
    initLight();
    glEnable(GL_TEXTURE_2D);
    drawMorpion();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();


    glPushMatrix();
    printText(6,6, GLUT_BITMAP_9_BY_15,"coucou");
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
    switch (key)
    {
    case '1':
        selectCube(currentFace->cubes[0]);
        break;
    case '2':
        selectCube(currentFace->cubes[1]);
        break;
    case '3':
        selectCube(currentFace->cubes[2]);
        break;
    case '4':
        selectCube(currentFace->cubes[3]);
        break;
    case '5':
        selectCube(currentFace->cubes[4]);
        break;
    case '6':
        selectCube(currentFace->cubes[5]);
        break;
    case '7':
        selectCube(currentFace->cubes[6]);
        break;
    case '8':
        selectCube(currentFace->cubes[7]);
        break;
    case '9':
        selectCube(currentFace->cubes[8]);
        break;
    case 27:
        exit(0);
        break;
    }
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
    glutInitWindowSize (1000, 1000);
    glutInitWindowPosition (400, 50);

    glutCreateWindow ("Super Morpion 3D");
    init ();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(SpecialInput);
    glutKeyboardFunc(keyboard);

    glutMainLoop();
    return 0;
}

