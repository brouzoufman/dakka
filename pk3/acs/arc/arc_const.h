#define ARCTYPES 7

#define ARC_S_NEXT    0
#define ARC_S_COLUMNS 1

str STR_ArcData[ARCTYPES][ARC_S_COLUMNS] =
{
    {"LanceArcShot_Power0"},
    {"LanceArcShot_Power1"},
    {"LanceArcShot_Power2"},
    {"LanceArcShot_Power3"},
    {"LanceArcShot_Power4"},
    {"LanceArcShot_Power5"},
    {"LanceArcShot_Power6"},
};


// how far one step of this arc can go, in map units. integer.
#define ARC_I_RANGE         0

// the higher this is, the more heavily the arc will want to go forward.
//  fixed point.
#define ARC_I_ANGLEWEIGHT   1

// if above zero, the angle between the arc's line of fire and the target can be
//  no higher than this value. fixed point, in turns.
#define ARC_I_ANGLELIMIT    2

// if 0, the arc will head off straight in the direction of whatever it arcs
//  through. if 1.0, the arc will keep facing the same direction the shooter's
//  facing. fixed point.
#define ARC_I_KEEPHEADING   3

// if 0, arcs will always spawn on the center of their target. if 1, arcs will
//  spawn anywhere on the target's hitbox, at random.
#define ARC_I_RANDOMOFFSET  4

// askdjasd
#define ARC_I_COLUMNS       5


str INT_ArcData[ARCTYPES][ARC_I_COLUMNS] =
{
    {320, 5.0, 0.2, 0.75, 0.6},
    {320, 5.0, 0.2, 0.75, 0.6},
    {320, 5.0, 0.2, 0.75, 0.6},
    {320, 5.0, 0.2, 0.75, 0.6},
    {320, 5.0, 0.2, 0.75, 0.6},
    {320, 5.0, 0.2, 0.75, 0.6},
    {320, 5.0, 0.2, 0.75, 0.6},
};