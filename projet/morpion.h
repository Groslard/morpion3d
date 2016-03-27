#define CROIX "crateX.ppm"
#define ROND "crateO.ppm"
#define DEFAULT "crate.ppm"


#define VRAI 1
#define FAUX 0

#define ROTATESPEED 1


typedef struct Color Color;
struct Color
{
    float r;
    float g;
    float b;
};

typedef struct Player Player;
struct Player
{
    char* pathTexture;
    GLuint texture;
    char* name;
    int pts;
};

typedef struct Cube Cube;
struct Cube
{
    Player* player;
};

typedef struct Face Face;
struct Face
{
    Cube* cubes[9];
    Face* leftFace;
    Face* rightFace;
    Player* winner;
};

