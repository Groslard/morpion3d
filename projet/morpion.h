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
    Color color;
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
    Cube* cubes[6];
    int upFaceId;
    int downFaceId;
    int leftFaceId;
    int rightFaceId;
    Player* winner;
};
