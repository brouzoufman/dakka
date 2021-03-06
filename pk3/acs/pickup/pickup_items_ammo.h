#define AMMOCOUNT   28

#define AMMO_SCRAP      0
#define AMMO_PISTOL     1
#define AMMO_SHELL      2
#define AMMO_GRENADE    3
#define AMMO_MINIGUN    4
#define AMMO_FLAMER     5
#define AMMO_ROCKET     6
#define AMMO_CELL       7

int PKP_KnownAmmo[AMMOCOUNT] =
{
    // DAKKA (10)
    "DakkaScrap",
    "DakkaBullet_50AE",
    "DakkaShells",
    "DakkaGrenades",
    "DakkaBullet_5mm",
    "DakkaFlamerFuel",
    "DakkaRockets",
    "DakkaCells",

    // DOOM (4)
    "Clip",
    "Shell",
    "RocketAmmo",
    "Cell",

    // HERETIC (6)
    "GoldWandAmmo",
    "BlasterAmmo",
    "CrossbowAmmo",
    "PhoenixRodAmmo",
    "SkullRodAmmo",
    "MaceAmmo",

    // HEXEN (2)
    "Mana1",
    "Mana2",

    // STRIFE (7)
    "ClipOfBullets",
    "ElectricBolts",
    "PoisonBolts",
    "MiniMissiles",
    "HEGrenadeRounds",
    "PhosphorusGrenadeRounds",
    "EnergyPod",
};


// DAKKA EXTENSION
// If dakka_startmode_ammo is set to a mode that resets your ammo to default
//  for weapons you have, it reads the values from here to determine that
//  default ammo count.
//
// Index 0 is default starting ammo.
// Index 1 is high starting ammo.
// Index 2 is low ammo, for dakka_cl_noammoclick.

#define DAMMO_STARTLOW      0
#define DAMMO_STARTHIGH     1
#define DAMMO_WARNLOW       2

int PKP_DefaultAmmoCount[AMMOCOUNT][3] =
{
    // DAKKA (10)
    { 60, 120, 36},            // scrap
    { 70, 210, 14},            // .50AE
    { 16,  60,  5},            // shells
    {  8,  18,  5},            // grenades
    {160, 400, 70},            // 5mm
    { 12,  24,  9},            // flamer
    { 18,  60, 12},            // rockets
    { 40, 200, 40},            // cells

    // DOOM (4)
    {100, 300, 20},            // bullets
    { 20,  60,  4},            // shells
    { 10,  30,  4},            // rockets
    { 80, 240, 40},            // cells

    // HERETIC (6)
    {100, 300,  0},            // wand
    {100, 300,  0},            // blaster
    { 20,  60,  0},            // crossbow
    { 10,  30,  0},            // phoenix
    {100, 250,  0},            // hellstaff
    { 50, 100,  0},            // firemace

    // HEXEN (2)
    {100, 200,  0},            // mana 1
    { 50, 100,  0},            // mana 2

    // STRIFE (7)
    //  (this will probably *never* come into play, since strife's one big hub)
    {100, 300,  0},            // bullets
    { 30,  60,  0},            // electric
    {  5,  15,  0},            // poison
    { 20,  75,  0},            // missiles
    {  6,  24,  0},            // HE
    {  2,   8,  0},            // phosphorus
    {120, 320,  0},            // energy
};


// DAKKA EXTENSION
// If dakka_startmode_ammo is set to 6, it'll read from these cvars to get the
//  desired amount of ammo.

str PKP_CustomStartAmmoCVars[AMMOCOUNT][2] =
{
    {"dakka_startammo_scrap",    "dakka_startammo_scrap_always"},
    {"dakka_startammo_50ae",     "dakka_startammo_50ae_always"},
    {"dakka_startammo_shells",   "dakka_startammo_shells_always"},
    {"dakka_startammo_grenades", "dakka_startammo_grenades_always"},
    {"dakka_startammo_5mm",      "dakka_startammo_5mm_always"},
    {"dakka_startammo_flamer",   "dakka_startammo_flamer_always"},
    {"dakka_startammo_rockets",  "dakka_startammo_rockets_always"},
    {"dakka_startammo_cells",    "dakka_startammo_cells_always"},
    
    // no one cares about the rest
};


// Yeah, that's... basically it.
