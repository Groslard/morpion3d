#define CROIX "j2.ppm"
#define ROND "j1.ppm"
#define DEFAULT "nonJoue.ppm"

#define VRAI 1
#define FAUX 0


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
    Face* upFace;
    Face* downFace;
    Face* leftFace;
    Face* rightFace;
    Player* winner;
};

