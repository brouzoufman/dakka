// I could've kept this stuff in pickup_client.h, but I'd rather have clearer
//  delineation between "stuff that's meant to be tinkered with" and "system
//  stuff that shouldn't be tinkered with".


// This defines how many different data points we should sync between the server
//  and the clients.
#define S2C_DATACOUNT   19


// Constants for identifying which data point we want to modify.

#define S2C_D_CLASSNUM      0

// Whether shotgun items (that spawned on the map) should show as SSGs instead.
#define S2C_D_SHOT2SSG      1

// Send score to client so he can display it himself.
#define S2C_D_SCORE         2

// This one's independent from the score rewards.
#define S2C_D_DISPLAYSCORE  3

// And the score threshold as well.
#define S2C_D_GOALSCORE     4

// How many extra lives do we have?
#define S2C_D_LIVESLEFT     5

// Which reward number are we on?
#define S2C_D_REWARDCOUNT   6


// All of these are bonus values. See acs/score/score_defs.h for what they
//  correspond to.
#define S2C_D_BONUSSTART    7

#define S2C_D_BS_BASE         7
#define S2C_D_BS_SPREE        8
#define S2C_D_BS_EFFICIENT    9
#define S2C_D_BS_INFIGHTER    10
#define S2C_D_BS_SWITCHAROO   11
#define S2C_D_BS_SCRAPPING    12
#define S2C_D_BS_CURVEBALL    13
#define S2C_D_BS_AIR          14
#define S2C_D_BS_BONEDRY      15
#define S2C_D_BS_SORELOSER    16
#define S2C_D_BS_BRAWLER      17
#define S2C_D_BS_POINTBLANK   18
