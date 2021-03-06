#define TMPITEM_COUNT       24

#define TMP_LEFTFIRE        0
#define TMP_RIGHTFIRE       1
#define TMP_LEFTCLICK       2
#define TMP_RIGHTCLICK      3
#define TMP_LEFTRELEASE     4
#define TMP_RIGHTRELEASE    5
#define TMP_INFINITEAMMO    6

#define TMP_ABNORMALHEALTH  7
#define TMP_HEALTH300       8
#define TMP_HEALTH200       9
#define TMP_HEALTH50        10
#define TMP_HEALTH25        11
#define TMP_HEALTH0         12

#define TMP_AMMO1_25        13
#define TMP_AMMO1_0         14

#define TMP_AMMO2_25        15
#define TMP_AMMO2_0         16

#define TMP_KNOWNARMOR      17
#define TMP_ARMOR100        18
#define TMP_ARMOR75         19
#define TMP_ARMOR50         20
#define TMP_ARMOR25         21

#define TMP_SSG_ROLLFIRE    22
#define TMP_MINIGUN_FASTER  23

int TempChecks[TMPITEM_COUNT];

int TempItems[TMPITEM_COUNT] =
{
    "MainFired",
    "AltFired",
    "MainClicked",
    "AltClicked",
    "MainReleased",
    "AltReleased",
    "DakkaInfiniteAmmo",
    "AbnormalHealth",
    "HealthOver200",
    "HealthOver100",
    "HealthUnder50",
    "HealthUnder25",
    "HealthUnder0",
    "Ammo1Under25",
    "Ammo1Empty",
    "Ammo2Under25",
    "Ammo2Empty",
    "HUD_KnownArmor",
    "HUD_Armor100",
    "HUD_Armor75",
    "HUD_Armor50",
    "HUD_Armor25",
    "DakkaSSG_RollFire",
    "DakkaMinigun_FireFast",
};


// Keep this in sync with armor items in pickup/pickup_items_armor.h.
int TempArmorItems[ARMORCOUNT] =
{
    "HUD_GreenArmor",
    "HUD_GreenArmor",
    "HUD_BlueArmor",
    "HUD_BlueArmor",
    "HUD_SilverArmor",
    "HUD_GoldArmor",
    "HUD_TanArmor",
    "HUD_SilverArmor",
    "HUD_RedArmor",

    // Dakka armors
    "HUD_GreenArmor",
    "HUD_BlueArmor",
    "HUD_GreenArmor",
};



function void Dakka_UpdateTemporaryItems(void)
{
    int i;
    int pln = PlayerNumber();

    TempChecks[TMP_LEFTFIRE]        = inputDown(BT_ATTACK);
    TempChecks[TMP_RIGHTFIRE]       = inputDown(BT_ALTATTACK);
    TempChecks[TMP_LEFTCLICK]       = inputPressed(BT_ATTACK);
    TempChecks[TMP_RIGHTCLICK]      = inputPressed(BT_ALTATTACK);
    TempChecks[TMP_LEFTRELEASE]     = inputReleased(BT_ATTACK);
    TempChecks[TMP_RIGHTRELEASE]    = inputReleased(BT_ALTATTACK);

    TempChecks[TMP_INFINITEAMMO]    = HasInfiniteAmmo();

    int health = GetActorProperty(0, APROP_Health);

    TempChecks[TMP_ABNORMALHEALTH]  = middle(50, health, 100) != health;
    TempChecks[TMP_HEALTH300]       = health > 200;
    TempChecks[TMP_HEALTH200]       = middle(101, health, 200) == health;
    TempChecks[TMP_HEALTH50]        = middle( 25, health,  49) == health;
    TempChecks[TMP_HEALTH25]        = middle(  1, health,  24) == health;
    TempChecks[TMP_HEALTH0]         = health <= 0;



    // pickup/pickup_pickup_armor.h
    int armorIndex  = Armor_CurrentArmorIndex();

    // I'd just use armorCount here, but ACS is case-insensitive...
    //  fucking hate that.
    int armorInv    = CheckInventory("BasicArmor");

    if (armorIndex == -1)
    {
        TempChecks[TMP_KNOWNARMOR]  = false;

        // ARMOR100/75/50/25 isn't used if we have an unknown armor.
        // I'm lazy.

        for (i = 0; i < ARMORCOUNT; i++)
        {
            SetInventory(TempArmorItems[i], 0);
        }
    }
    else
    {
        TempChecks[TMP_KNOWNARMOR]  = true;

        int armorHUDItem = TempArmorItems[armorIndex];

        for (i = 0; i < ARMORCOUNT; i++)
        {
            int curItem = TempArmorItems[i];
            SetInventory(curItem, stricmp(curItem, armorHUDItem) == 0);
        }

        int armorMax      = PKP_ArmorData[armorIndex][ARM_MAXPOINTS];
        int armorQuadrant = (armorInv * 4) / armorMax;

        TempChecks[TMP_ARMOR100] = armorQuadrant >= 3;
        TempChecks[TMP_ARMOR75]  = armorQuadrant == 2;
        TempChecks[TMP_ARMOR50]  = armorQuadrant == 1;
        TempChecks[TMP_ARMOR25]  = armorQuadrant <= 0;
    }



    // pickup/pickup_pickup_weapons.h
    int wepIndex    = Weapon_CurrentWeaponIndex();
    int ammo1Name   = PKP_KnownGuns[wepIndex][WEP_AMMO1];
    int ammo2Name   = PKP_KnownGuns[wepIndex][WEP_AMMO2];

    int hasAmmo1;
    int hasAmmo2;

    // ACS does not have operator short-circuiting.
    // It really fucking needs operator short-circuiting.
    if (wepIndex == -1)
    {
        hasAmmo1 = false;
        hasAmmo2 = false;
    }
    else
    {
        hasAmmo1 = !stringBlank(ammo1Name);
        hasAmmo2 = !stringBlank(ammo2Name);
    }

    if (!hasAmmo1)
    {
        TempChecks[TMP_AMMO1_25]        = false;
        TempChecks[TMP_AMMO1_0]         = false;
    }
    else
    {
        int ammo1Cur = CheckInventory(ammo1Name);
        int ammo1Max = GetAmmoCapacity(ammo1Name);
        int ammo1Percent = itof(ammo1Cur) / ammo1Max;

        // note: 1 is actually 1.0 / 65536, do not get confused
        TempChecks[TMP_AMMO1_25]        = middle(1, ammo1Percent, 0.25 - 1) == ammo1Percent;
        TempChecks[TMP_AMMO1_0]         = ammo1Percent <= 0;
    }

    if (!hasAmmo2)
    {
        TempChecks[TMP_AMMO2_25]        = false;
        TempChecks[TMP_AMMO2_0]         = false;
    }
    else
    {
        int ammo2Cur = CheckInventory(ammo2Name);
        int ammo2Max = GetAmmoCapacity(ammo2Name);
        int ammo2Percent = itof(ammo2Cur) / ammo2Max;

        // note: 1 is actually 1.0 / 65536, do not get confused
        TempChecks[TMP_AMMO2_25]        = middle(1, ammo2Percent, 0.25 - 1) == ammo2Percent;
        TempChecks[TMP_AMMO2_0]         = ammo2Percent <= 0;
    }

    TempChecks[TMP_SSG_ROLLFIRE] = GetUserCVar(pln, "dakka_cl_ssgrollfire");
    
    switch (GetUserCVar(pln, "dakka_cl_fullerautostyle"))
    {
      default:
        TempChecks[TMP_MINIGUN_FASTER] = TempChecks[TMP_RIGHTFIRE];
        break;
      
      case 1:
        TempChecks[TMP_MINIGUN_FASTER] = inputDown(BT_ZOOM);
        break;
      
      case 2:
        TempChecks[TMP_MINIGUN_FASTER] = inputDown(BT_RELOAD);
        break;
    }

    for (i = 0; i < TMPITEM_COUNT; i++)
    {
        int item        = TempItems[i];
        int getItem     = TempChecks[i];

        SetInventory(item, getItem);
    }
}
