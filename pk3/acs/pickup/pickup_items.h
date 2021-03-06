// Defining pickups themselves is handled here.


// This is, quite simply, the amount of pickup types that this ACS is equipped
//  to handle.
#define PICKUPCOUNT     24


// How many items can you get from each pickup?
#define PK_RECEIVECOUNT 3


// Define item constants here. Because "item 0" doesn't mean shit.
#define It_Fist             0
#define It_Chainsaw         1
#define It_Pistol           2
#define It_Shotgun          3
#define It_SuperShotgun     4
#define It_Chaingun         5
#define It_RocketLauncher   6
#define It_PlasmaRifle      7
#define It_BFG9000          8

#define It_ShotgunDropped   9
#define It_ChaingunDropped  10

#define It_GreenArmor       11
#define It_BlueArmor        12

#define It_ST_Minigun           13
#define It_ST_GrenadeLauncher   14
#define It_ST_Railgun           15
#define It_ST_BFG10k            16

#define It_Hexen_Helm           17
#define It_Hexen_Amulet         18
#define It_Hexen_MeshArmor      19
#define It_Hexen_Shield         20
#define It_Hexen_Bracers        21

#define It_GreenArmorVanilla    22
#define It_BlueArmorVanilla     23

// Here, you have the items that each pickup will give you. Each pickup can give
//  as many as PK_RECEIVECOUNT items.
//
// Note that index 0 is not for class 0 in pickup_classes.h, but actually for
//  Cl_Unknown.
//
// And we group by pickup and not by class because it's more useful contextually
//  to see "oh, this is the place where everyone gets health bonuses" than "oh,
//  he gets a soulsphere up there and a stimpack up there so this is the health
//  bonus index I guess... or is it megasphere?".
//
// Talking from experience.

int PKP_ReceiveItems[PICKUPCOUNT][CLASSCOUNT][PK_RECEIVECOUNT] =
{
    {
        {"Fist"},
        {"DWep_Fists"},
    },
    {
        {"Chainsaw"},
        {"DWep_Scrappers"},
    },
    {
        {"Pistol"},
        {"DWep_Pistols"},
    },
    {
        {"Shotgun"},
        {"DWep_Shotgun"},
    },
    {
        {"SuperShotgun"},
        {"DWep_SuperShotgun"},
    },
    {
        {"Chaingun"},
        {"DWep_Minigun"},
    },
    {
        {"RocketLauncher"},
        {"DWep_Impaler"},
    },
    {
        {"PlasmaRifle"},
        {"DWep_PlasmaLance"},
    },
    {
        {"BFG9000"},
        {"DWep_BFG9000"},
    },
    
    { // Dropped
        {"Shotgun"},
        {"DWep_Shotgun"},
    },
    { // Dropped
        {"Chaingun"},
        {"DWep_Minigun"},
    },


    {
        {"GreenArmor"},
        {"Dakka_GreenArmor"},
    },
    {
        {"BlueArmor"},
        {"Dakka_BlueArmor"},
    },


    // Skulltag pickups
    { // Minigun
        {"Minigun"},
        {"DWep_Minigun"},
    },
    { // Grenade launcher
        {"GrenadeLauncher"},
        {"DWep_Impaler"},
    },
    { // Railgun
        {"Railgun"},
        {"DWep_PlasmaLance"},
    },
    { // BFG10k
        {"BFG10k"},
        {"DWep_BFG9000"},
    },
    
    {
        {"PlatinumHelm"},
        {"Dakka_GreenArmor"},
    },
    {
        {"AmuletOfWarding"},
        {"Dakka_GreenArmor"},
    },
    {
        {"MeshArmor"},
        {"Dakka_BlueArmor"},
    },
    {
        {"FalconShield"},
        {"Dakka_BlueArmor"},
    },
    { // Bracers
        {"Dakka_ArmorBonus"},
        {"Dakka_ArmorBonus"},
    },


    {
        {"GreenArmor"},
        {"GreenArmor"},
    },
    {
        {"BlueArmor"},
        {"BlueArmor"},
    },
};



// How many of those items are we going to get?
int PKP_ReceiveCount[PICKUPCOUNT][CLASSCOUNT][PK_RECEIVECOUNT] =
{
    // Weapons
    {
        {1},
        {1},
    },
    {
        {1},
        {1},
    },
    {
        {1},
        {1},
    },
    {
        {1},
        {1},
    },
    {
        {1},
        {1},
    },
    {
        {1},
        {1},
    },
    {
        {1},
        {1},
    },
    {
        {1},
        {1},
    },
    {
        {1},
        {1},
    },
    
    { // Dropped shotgun
        {1},
        {1},
    },
    { // Dropped chaingun
        {1},
        {1},
    },


    // Armor
    {
        {1},
        {75},
    },
    {
        {1},
        {150},
    },



    // Skulltag pickups
    { // Minigun
        {1},
        {1},
    },
    { // Grenade launcher
        {1},
        {1},
    },
    { // Railgun
        {1},
        {1},
    },
    { // BFG10k
        {1},
        {1},
    },
    
    
    // Hexen armor
    { // Helm
        {1},
        {75},
    },
    { // Amulet
        {1},
        {75},
    },
    { // Mesh armor
        {1},
        {150},
    },
    { // Shield
        {1},
        {150},
    },
    { // Bracers
        {50},
        {50},
    },


    // Armor (dakka_vanillahealtharmor on)
    {
        {1},
        {1},
    },
    {
        {1},
        {1},
    },
};



// And should this item *always* be picked up?
// This not only forces a pickup message, but also forces consumption
//  of the pickup. PARRAY_NOCONSUME will still block consumption, however.
int PKP_AlwaysPickup[PICKUPCOUNT][CLASSCOUNT] =
{
    // Weapons
    {
        false,
        false,
    },
    {
        false,
        false,
    },
    {
        false,
        false,
    },
    {
        false,
        false,
    },
    {
        false,
        false,
    },
    {
        false,
        false,
    },
    {
        false,
        false,
    },
    {
        false,
        false,
    },
    {
        false,
        false,
    },
    {
        false,
        false,
    },
    {
        false,
        false,
    },


    // Armor
    {
        false,
        false,
    },
    {
        false,
        false,
    },



    // Skulltag pickups
    { // Minigun
        false,
        false,
    },
    { // Grenade launcher
        false,
        false,
    },
    { // Railgun
        false,
        false,
    },
    { // BFG10k
        false,
        false,
    },


    // Hexen armor items
    {
        false,
        false,
    },
    {
        false,
        false,
    },
    {
        false,
        false,
    },
    {
        false,
        false,
    },
    {
        false,
        false,
    },


    // Armor (dakka_vanillahealtharmor on)
    {
        false,
        false,
    },
    {
        false,
        false,
    },
};
