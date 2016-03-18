#define CROIX "croix.ppm"
#define ROND "croix.ppm"
#define DEFAULT "brick10.ppm"

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
    int upFaceId;
    int downFaceId;
    int leftFaceId;
    int rightFaceId;
    Player* winner;
};