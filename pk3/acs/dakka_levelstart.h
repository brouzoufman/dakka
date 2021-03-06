// Weapon start modes:
//  - 0: do nothing special
//
//  - 1: use custom weapon start mode (aka. give and take what the server says to
//       give and take away)
//
//  - Anything above 1: Any weapon with a power rating at or below the value of
//      dakka_startmode_weapons is given to you; anything else is taken away
//
// Note that this and dakka_startmode_ammo can only work with weapons defined in
//  the pickup system.
//
// Start mode weapon and ammo data is stored in pickup/pickup_items_weapons.h
//  and pickup_items_ammo.h to keep stuff like that together (unlike samsara)



// We look up ammo types the weapon uses in Pickup_KnownGuns
//  - in pickup/pickup_items_weapons.h
//
// When ammo is reset with the low, high, or pistol-only method, any ammo that
//  you can't use with your current weapons gets taken away. If you have 120
//  rockets on leaving a map, but no impaler to use them in, tough shit I guess,
//  because they're gone.
//
// When using the "max out ammo" option, this is ignored. You can also choose
//  whether to ignore this per ammo type when using custom ammo reset values.
//
// AMMOCOUNT is in 'pickup/pickup_items_ammo.h'.
int Start_AmmoToKeep[AMMOCOUNT];



function void Dakka_StartMode_Weapons(int classNum, int entered, int lostWeapons)
{
    // Do nothing on normal coop respawn
    if (!(entered || lostWeapons)) { return; }

    int startMode = GetCVar("dakka_startmode_weapons");
    if (startMode <= 0) { return; }

    if (startMode == 1)
    {
        Dakka_StartMode_CustomWeps(classNum);
    }
    else
    {
        Dakka_StartMode_NormalWeps(classNum, startMode);
    }
}


function void Dakka_StartMode_NormalWeps(int classNum, int startMode)
{
    for (int i = 0; i < CLASSWEAPONS; i++)
    {
        str wepName  = Dakka_ClassWeapons[i][classNum+1];
        int wepPower = Dakka_ClassWeaponPowers[i][classNum+1];
        int wepIndex = Weapon_WeaponIndex(wepName);

        // We use this to ignore the fists (and originally, pistols and scrappers too).
        // But we don't want to take away ammo for them either, that's bad
        int ignore = Dakka_ClassWep_StartModeIgnore[i][classNum+1];

        if (!ignore)
        {
            if (startMode < wepPower)
            {
                if (CheckWeapon(wepName)) { SetWeapon("DWep_Pistols"); }
                TakeInventory(wepName, 0x7FFFFFFF);
                continue;
            }

            // Can't do ammo-related stuff with guns we don't recognize
            if (wepIndex == -1)
            {
                GiveInventory(wepName, 1);
                continue;
            }
        }

        str ammo1Name = PKP_KnownGuns[wepIndex][WEP_AMMO1];
        str ammo2Name = PKP_KnownGuns[wepIndex][WEP_AMMO2];

        int willHaveGun = CheckInventory(wepName) || !ignore;
        int gotAmmo1    = !stringBlank(ammo1Name);
        int gotAmmo2    = !stringBlank(ammo2Name);

        if (gotAmmo1)
        {
            int ammo1Index = Ammo_AmmoIndex(ammo1Name);
            int ammo1Count = CheckInventory(ammo1Name);
        }

        if (gotAmmo2)
        {
            int ammo2Index = Ammo_AmmoIndex(ammo2Name);
            int ammo2Count = CheckInventory(ammo2Name);
        }

        if (!ignore)
        {
            GiveInventory(wepName, 1);

            if (gotAmmo1) { SetInventory(ammo1Name, ammo1Count); }
            if (gotAmmo2) { SetInventory(ammo2Name, ammo2Count); }
        }
    }
}


function void Dakka_StartMode_CustomWeps(int classNum)
{
    for (int i = 0; i < CLASSWEAPONS; i++)
    {
        str wepName  = Dakka_ClassWeapons[i][classNum+1];
        int wepIndex = Weapon_WeaponIndex(wepName);
        
        // If we don't recognize the weapon, don't do anything with it
        if (wepIndex == -1) { continue; }
        
        str customCVar = PKP_KnownGuns[wepIndex][WEP_STARTCVAR];
        int customGive = 0;

        if (!stringBlank(customCVar))
        {
            customGive = GetCVar(customCVar);
            
            if (customGive < 0)
            {
                if (CheckWeapon(wepName)) { SetWeapon("DWep_Pistols"); }
                TakeInventory(wepName, 0x7FFFFFFF);
                continue;
            }
        }

        str ammo1Name = PKP_KnownGuns[wepIndex][WEP_AMMO1];
        str ammo2Name = PKP_KnownGuns[wepIndex][WEP_AMMO2];

        int willHaveGun = CheckInventory(wepName) || (customGive > 0);
        int gotAmmo1    = !stringBlank(ammo1Name);
        int gotAmmo2    = !stringBlank(ammo2Name);

        if (gotAmmo1)
        {
            int ammo1Index = Ammo_AmmoIndex(ammo1Name);
            int ammo1Count = CheckInventory(ammo1Name);
        }

        if (gotAmmo2)
        {
            int ammo2Index = Ammo_AmmoIndex(ammo2Name);
            int ammo2Count = CheckInventory(ammo2Name);
        }

        if (customGive > 0)
        {
            GiveInventory(wepName, 1);

            if (gotAmmo1) { SetInventory(ammo1Name, ammo1Count); }
            if (gotAmmo2) { SetInventory(ammo2Name, ammo2Count); }
        }
    }
}



// Ammo start modes:
//  - 0: Do nothing with ammo.
//
//  - 1: Start every weapon you have with a small amount of default ammo,
//          defined in 'pickup/pickup_items_ammo.h'.
//
//  - 2: Start every weapon you have with a large amount of default ammo.
//
//  - 3: Start every weapon you have with max ammo.
//
//  - 3: Start every weapon you have with a power rating below 3 with default
//          ammo, and take away ammo for every other weapon.
//
//  - 4: Start every weapon you have with a power rating below 3 with max ammo,
//          and take away ammo for every other weapon.

function void Dakka_StartMode_Ammo(int classNum, int entered, int lostAmmo)
{
    // Do nothing on normal coop respawn
    if (!(entered || lostAmmo)) { return; }

    int startMode = GetCVar("dakka_startmode_ammo");
    int i;

    if (startMode <= 0 || startMode > 5) { return; }

    // These all basically use the same logic except for how much ammo you get,
    //  and whether only pistol-class or lower weapons should get ammo.
    for (i = 0; i < AMMOCOUNT; i++)
    {
        Start_AmmoToKeep[i] = false;
    }

    int giveLargeAmmo = startMode == 2;
    int giveMaxAmmo   = startMode == 3;
    int onlyPistols   = startMode == 4;
    int customValues  = startMode == 5;

    // Determine which ammo should be given
    if (!giveMaxAmmo)
    {
        for (i = 0; i < WEAPONCOUNT; i++)
        {
            int wepName   = PKP_KnownGuns[i][WEP_NAME];

            // I honestly have no idea why I didn't include this here earlier
            if (!CheckInventory(wepName)) { continue; }

            // If we're only grabbing pistol start weapons, check power rating
            if (onlyPistols)
            {
                int j;
                int isPistol = false;

                // Also we only give a crap about pistol start weapons
                //  for *our* class
                for (j = 0; j < CLASSWEAPONS; j++)
                {
                    int startRating = Dakka_ClassWeaponPowers[j][classNum+1];
                    if (startRating > 2) { continue; }

                    int startWep = Dakka_ClassWeapons[j][classNum+1];

                    if (!stricmp(wepName, startWep))
                    {
                        isPistol = true;
                        break;
                    }
                }

                // well shit
                if (!isPistol) { continue; }
            }

            int ammo1Name = PKP_KnownGuns[i][WEP_AMMO1];
            int ammo2Name = PKP_KnownGuns[i][WEP_AMMO2];

            // The stingBlank check's for optimization - if there's no ammo type,
            //  don't check, as Ammo_AmmoIndex's expensive when called as many
            //  times as it is here
            if (!stringBlank(ammo1Name))
            {
                int ammo1Index = Ammo_AmmoIndex(ammo1Name);
                Start_AmmoToKeep[ammo1Index] = true;
            }

            if (!stringBlank(ammo2Name))
            {
                int ammo2Index = Ammo_AmmoIndex(ammo2Name);
                Start_AmmoToKeep[ammo2Index] = true;
            }
        }
    }
    
    // Now distribute the ammo that should be given, and take the ammo
    //  that shouldn't be given
    
    for (i = 0; i < AMMOCOUNT; i++)
    {
        str ammoName = PKP_KnownAmmo[i];
        int always     = giveMaxAmmo;
        str alwaysCVar = PKP_CustomStartAmmoCVars[i][1];
        if (customValues && !stringBlank(alwaysCVar)) { always = GetCVar(alwaysCVar); }
        
        if (always || Start_AmmoToKeep[i])
        {
            int newAmount;
            
            if (customValues)
            {
                str amountCVar = PKP_CustomStartAmmoCVars[i][0];
                if (stringBlank(amountCVar)) { newAmount = PKP_DefaultAmmoCount[i][DAMMO_STARTLOW]; }
                else                         { newAmount = GetCVar(amountCVar); }
            }
            else if (giveMaxAmmo)   { newAmount = GetAmmoCapacity(ammoName); }
            else if (giveLargeAmmo) { newAmount = PKP_DefaultAmmoCount[i][DAMMO_STARTHIGH]; }
            else                    { newAmount = PKP_DefaultAmmoCount[i][DAMMO_STARTLOW]; }
            
            if (newAmount >= 0) { SetInventory(ammoName, newAmount); }
        }
        else
        {
            SetInventory(ammoName, 0);
        }
    }
}



// Health start modes (includes armor):
//
//  - 0: Do nothing.
//  - 1: Enter the map with full health and no armor. Default.
//  - 2: Enter the map with full health, and a set of green armor.
//  - 3: Enter the map with a soulsphere and a set of blue armor.
//  - 4: Enter the map with a megasphere.

function void Dakka_StartMode_Health(int classNum, int freshStart, int respawning)
{
    if (!(freshStart || respawning)) { return; }

    int startmode = GetCVar("dakka_startmode_health");

    if (startmode == 0) { return; }

    int curHP = GetActorProperty(0, APROP_Health);
    int maxHP = getMaxHealth();

    switch (startmode)
    {
      default:
        SetActorProperty(0, APROP_Health, maxHP);
        TakeInventory("BasicArmor", 0x7FFFFFFF);
        break;

      case 2:
        SetActorProperty(0, APROP_Health, maxHP);
        TakeInventory("BasicArmor", 0x7FFFFFFF);
        Pickup_DoPickup(It_GreenArmor, classNum, false);
        break;

      case 3:
        SetActorProperty(0, APROP_Health, maxHP);
        TakeInventory("BasicArmor", 0x7FFFFFFF);
        Pickup_DoPickup(It_BlueArmor,  classNum, false);
        GiveInventory("Pickup_Soulsphere", 1);
        break;

      case 4:
        SetActorProperty(0, APROP_Health, maxHP);
        TakeInventory("BasicArmor", 0x7FFFFFFF);
        GiveInventory("Pickup_Megasphere", 1);
        break;
      
      case 5:
        SetActorProperty(0, APROP_Health, max(50, curHP));
        break;
    }
}


// Corresponds to dakka_startmode_backpack. 0 means "do nothing",
//  1 means "give backpack", -1 means "take all backpacks".
//
// Dakka_Backpacks is in dakka_const.h.
int Backpack_AmmoBefore[AMMOCOUNT];

function void Dakka_BackpackStart(int entered, int lostEverything)
{
    if (!(entered || lostEverything)) { return; }
    
    int backpackStart = GetCVar("dakka_startmode_backpack");
    if (backpackStart == 0) { return; }

    int i, ammoName, ammoInv;

    // Take backpack on new map
    if (backpackStart < 0)
    {
        for (i = 0; i < BACKPACKCOUNT; i++)
        {
            TakeInventory(Dakka_BackpackItems[i], 0x7FFFFFFF);
        }

        // Cap ammo at new max ammo capacity
        for (i = 0; i < AMMOCOUNT; i++)
        {
            ammoName = PKP_KnownAmmo[i];
            ammoInv  = CheckInventory(ammoName);

            TakeInventory(ammoName, ammoInv - GetAmmoCapacity(ammoName));
        }

        return;
    }

    // Give backpack

    for (i = 0; i < AMMOCOUNT; i++)
    {
        Backpack_AmmoBefore[i] = CheckInventory(PKP_KnownAmmo[i]);
    }

    GiveInventory("DakkaBackpackItem", 1);

    for (i = 0; i < AMMOCOUNT; i++)
    {
        ammoName = PKP_KnownAmmo[i];
        ammoInv  = CheckInventory(ammoName);

        TakeInventory(ammoName, ammoInv - Backpack_AmmoBefore[i]);
    }
}


// Four cases:
// - Starting new hub:          entered true,  returning false, doesn't have hub tracker
// - Entering new map in hub:   entered true,  returning false, has hub tracker
// - Returning to map in hub:   entered true,  returning true,  has hub tracker
// - Respawning:                entered false, returning false, might have hub tracker

function void Dakka_DoLevelSpawn(int entered, int returning)
{
    // Detect if we're moving around in the same hub
    int hasHubTracker = CheckInventory("HubTracker");

    // Unless we have dakka_ignorehubs on because thanks DUMP
    int ignoreHubs = GetCVar("dakka_ignorehubs");

    // Handle respawns normally
    int newHub     =  entered && !hasHubTracker;
    int intraHub   = (entered &&  hasHubTracker) || returning;
    int respawning = !(entered || returning);
    int freshStart = newHub || (ignoreHubs && !respawning);

    GiveInventory("HubTracker", 1);

    int lostEverything, lostAmmo, lostWeapons;
    
    if (IsZandronum)
    {
        lostEverything  = respawning &&                    GetCVar("sv_coop_loseinventory");
        lostAmmo        = respawning && (lostEverything || GetCVar("sv_coop_loseammo"));
        lostWeapons     = respawning && (lostEverything || GetCVar("sv_coop_loseweapons"));
    }
    else
    {
        lostEverything  = respawning &&                    GetCVar("sv_cooploseinventory");
        lostAmmo        = respawning && (lostEverything || GetCVar("sv_cooploseammo"));
        lostWeapons     = respawning && (lostEverything || GetCVar("sv_cooploseweapons"));
    }

    int pln       = PlayerNumber();
    int classNum  = Pickup_ClassNumber(0);

    Dakka_BackpackStart(freshStart, lostEverything);
    Dakka_StartMode_Weapons(classNum, freshStart, lostWeapons);
    Dakka_StartMode_Ammo(   classNum, freshStart, lostAmmo);
    Dakka_StartMode_Health( classNum, freshStart, respawning);

    if (freshStart)
    {
        // in acs/score_levelstart.h
        Score_Reset(pln);
        ClearAllRewards(pln);
        Dakka_VampireReset();
        
        TakeInventory("DakkaKillstreak",      0x7FFFFFFF);
        TakeInventory("DakkaKillstreakTimer", 0x7FFFFFFF);
        
        TakeInventory("DakkaUntouchableKills",  0x7FFFFFFF);
        TakeInventory("DakkaUntouchableHealth", 0x7FFFFFFF);
        TakeInventory("DakkaUntouchableStacks", 0x7FFFFFFF);
    }

    if (classNum == Cl_Dakkaguy)
    {
        ACS_NamedExecuteWithResult("Dakka_PistolReload");

        if (newHub)
        {
            int hasShotgun  = CheckInventory("DWep_Shotgun");

            if (hasShotgun) { GiveInventory("DakkaShotgunTracker", 1); }
            else            { TakeInventory("DakkaShotgunTracker", 0x7FFFFFFF); }

            // We don't handle S2C_D_SHOT2SSG here because the CVar controlling
            //  that could change mid-game. That's handled in the enter loop.
            //
            // The CVar might play oddly with sv_coop_loseinventory and
            //  sv_coop_loseweapons. But even then, you can still get the
            //  shotguns and chainguns through enemy drops, so I'm not exactly
            //  going to lose any sleep over it.
        }
    }
}


function void Dakka_DoDMSpawn(int entered)
{
    int pln      = PlayerNumber();
    int classNum = Pickup_ClassNumber(0);

    Score_Reset(pln);
    Dakka_VampireReset();

    Dakka_BackpackStart(entered, true);
    Dakka_StartMode_Weapons(classNum, true, true);
    Dakka_StartMode_Ammo(   classNum, true, true);
    Dakka_StartMode_Health( classNum, true, !entered);
}
