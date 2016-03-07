// Weapon start modes:
//  - 0: do nothing special
//  - Anything above 0: Any weapon with a power rating at or below the value of
//      dakka_startmode_weapons is given to you; anything else is taken away
//  
//      2 is the same as 1 effectively, so that you always have fists and pistols
//
// Note that this and dakka_startmode_ammo can only work with weapons defined in
//  the pickup system.
//
// Start mode weapon and ammo data is stored in pickup/pickup_items_weapons.h
//  and pickup_items_ammo.h to keep stuff like that together (unlike samsara)



// We look up ammo types the weapon uses in Pickup_KnownGuns
//  - in pickup/pickup_items_weapons.h
//
// If dakka_startmode_weapons > 0 and above, ammo types for any given weapons
//  are kept, while all other ammo types are cleared out.
//
// ex. If you have dakka_startmode_weapons at 4 and you leave with 17 rockets,
//  you enter the next map with no rockets, since you wouldn't get the rocket
//  launcher.
//
// This can be further modified by dakka_startmode_ammo.
//
// AMMOCOUNT is in 'pickup/pickup_items_ammo.h'.
int Start_AmmoToKeep[AMMOCOUNT];



function void Dakka_StartMode_Weapons(int classNum, int entered, int lostWeapons)
{
    // Do nothing on normal coop respawn
    if (!(entered || lostWeapons)) { return; }

    int startMode = GetCVar("dakka_startmode_weapons");
    if (startMode <= 0) { return; }

    int i, j;

    for (i = 0; i < AMMOCOUNT; i++)
    {
        Start_AmmoToKeep[i] = false;
    }

    for (i = 0; i < CLASSWEAPONS; i++)
    {
        // We use this to ignore fist/pistol weapons, as well as the Scrappers.
        int ignore = Dakka_ClassWep_StartModeIgnore[i][classNum+1];
        if (ignore) { continue; }

        int wepName  = Dakka_ClassWeapons[i][classNum+1];
        int wepPower = Dakka_ClassWeaponPowers[i][classNum+1];
        int wepIndex = Weapon_WeaponIndex(wepName);

        // Weapon power rating too high
        if (startMode < wepPower)
        {
            TakeInventory(wepName, 0x7FFFFFFF);
            continue;
        }

        // If it's not a weapon we recognize, just give it once
        //  and be done with it
        if (wepIndex == -1)
        {
            GiveInventory(wepName, 1);
            continue;
        }

        int ammo1Name = PKP_KnownGuns[wepIndex][WEP_AMMO1];
        int ammo2Name = PKP_KnownGuns[wepIndex][WEP_AMMO2];

        int gotAmmo1 = !stringBlank(ammo1Name);
        int gotAmmo2 = !stringBlank(ammo2Name);

        if (gotAmmo1)
        {
            int ammo1Index = Ammo_AmmoIndex(ammo1Name);
            int ammo1Count = CheckInventory(ammo1Name);

            if (ammo1Index > -1) { Start_AmmoToKeep[ammo1Index] = true; }
        }

        if (gotAmmo2)
        {
            int ammo2Index = Ammo_AmmoIndex(ammo2Name);
            int ammo2Count = CheckInventory(ammo2Name);

            if (ammo2Index > -1) { Start_AmmoToKeep[ammo2Index] = true; }
        }

        GiveInventory(wepName, 1);

        // Keep ammo constant
        
        if (gotAmmo1) { TakeInventory(ammo1Name, CheckInventory(ammo1Name) - ammo1Count); }
        if (gotAmmo2) { TakeInventory(ammo2Name, CheckInventory(ammo2Name) - ammo2Count); }
    }


    // Take away all ammo that we're not set to keep
    for (i = 0; i < AMMOCOUNT; i++)
    {
        if (!Start_AmmoToKeep[i])
        {
            TakeInventory(PKP_KnownAmmo[i], 0x7FFFFFFF);
        }
    }
}



// Ammo start modes:
//  - 0: Do nothing with ammo.
//
//  - 1: Start every weapon you have with a small amount of default ammo,
//          defined in 'pickup/pickup_items_ammo.h'.
//
//  - 2: Start every weapon you have with max ammo.
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

    // Exit early because fuck it
    if (startMode <= 0 || startMode > 3) { return; }

    // These all basically use the same logic except for how much ammo you get,
    //  and whether only pistol-class or lower weapons should get ammo.
    for (i = 0; i < AMMOCOUNT; i++)
    {
        Start_AmmoToKeep[i] = false;
    }

    int giveMaxAmmo = (startMode == 2) || (startMode == 4);
    int onlyPistols = (startMode == 3) || (startMode == 4);

    // Determine which ammo should be given
    for (i = 0; i < WEAPONCOUNT; i++)
    {
        int wepName   = PKP_KnownGuns[i][WEP_NAME];

        // If we're only grabbing pistol start weapons, check power rating
        if (onlyPistols)
        {
            int j;
            int isPistol = false;

            // Also we only give a crap about pistol start weapons
            //  for *our* class
            for (j = 0; j < CLASSWEAPONS; j++)
            {
                int startWep    = Dakka_ClassWeapons[j][classNum+1];
                int startRating = Dakka_ClassWeaponPowers[j][classNum+1];

                if (startRating > 2) { continue; }

                if (stricmp(wepName, startWep))
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

            if (CheckInventory(wepName))
            {
                Start_AmmoToKeep[ammo1Index] = true;
            }
        }

        if (!stringBlank(ammo2Name))
        {
            int ammo2Index = Ammo_AmmoIndex(ammo2Name);

            if (CheckInventory(wepName))
            {
                Start_AmmoToKeep[ammo2Index] = true;
            }
        }
    }

    // Now distribute the ammo that should be given, and take the ammo
    //  that shouldn't be given
    for (i = 0; i < AMMOCOUNT; i++)
    {
        int ammoName = PKP_KnownAmmo[i];
        TakeInventory(ammoName, 0x7FFFFFFF);

        if (Start_AmmoToKeep[i])
        {
            if (giveMaxAmmo)
            {
                GiveInventory(ammoName, GetAmmoCapacity(ammoName));
            }
            else
            {
                GiveInventory(ammoName, PKP_DefaultAmmoCount[i]);
            }
        }
    }
}



// Health start modes (includes armor):
//
//  - 0: Do nothing.
//
//  - 1 (default): Enter the map with full health and no armor.
//
//  - 2: Enter the map with full health, and a set of green armor.
//
//  - 3: Enter the map with a soulsphere and a set of blue armor.
//
//  - 4: Enter the map with a megasphere.

function void Dakka_StartMode_Health(int classNum, int entered)
{
    if (!entered) { return; }

    int startmode = GetCVar("dakka_startmode_health");

    if (startmode == 0) { return; }

    int maxHP = getMaxHealth();

    SetActorProperty(0, APROP_Health, maxHP);
    TakeInventory("BasicArmor", 0x7FFFFFFF);

    switch (startmode)
    {
      default:
        break;

      case 2:
        Pickup_DoPickup(It_GreenArmor, classNum, false);
        break;

      case 3:
        Pickup_DoPickup(It_Soulsphere, classNum, false);
        Pickup_DoPickup(It_BlueArmor,  classNum, false);
        break;

      case 4:
        Pickup_DoPickup(It_Megasphere, classNum, false);
        break;
    }
}



// Corresponds to dakka_scrapperstart. Should only be called for Dakkaguy.
function void Dakka_ScrapperStart(int extraScrap)
{
    if (CheckInventory("DWep_Scrappers") || GetCVar("dakka_scrapperstart") <= 0)
    {
        return;
    }

    int scrapBefore = CheckInventory("DakkaScrap");
    GiveInventory("DWep_Scrappers", 1);
    int scrapAfter = CheckInventory("DakkaScrap");

    int targetScrap = (scrapBefore + extraScrap) - scrapAfter;

    if (targetScrap < 0)
    {
        TakeInventory("DakkaScrap", -targetScrap);
    }
    else
    {
        GiveAmmo("DakkaScrap", targetScrap);
    }
}


// Corresponds to dakka_backpackstart. 0 means "do nothing", 1 means "give backpack",
//  -1 means "take all backpacks".
//
// Dakka_Backpacks is in dakka_const.h.
int Backpack_AmmoBefore[AMMOCOUNT];

function void Dakka_BackpackStart(void)
{
    int backpackStart = GetCVar("dakka_backpackstart");
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


function void Dakka_DoLevelSpawn(int entered)
{
    // Detect if we're moving around in the same hug
    int hasHubTracker = CheckInventory("HubTracker");

    // Handle respawns normally
    int intraHubEnter = hasHubTracker && entered;

    GiveInventory("HubTracker", 1);

    int lostEverything  = !entered &&                    GetCVar("sv_coop_loseinventory");
    int lostAmmo        = !entered && (lostEverything || GetCVar("sv_coop_loseammo"));
    int lostWeapons     = !entered && (lostEverything || GetCVar("sv_coop_loseweapons"));

    int pln       = PlayerNumber();
    int classNum  = Pickup_ClassNumber(0);

    if (!intraHubEnter)
    {
        Dakka_BackpackStart();

        Dakka_StartMode_Weapons(classNum, entered, lostWeapons);
        Dakka_StartMode_Ammo(   classNum, entered, lostAmmo);
        Dakka_StartMode_Health( classNum, entered);

        if (entered)
        {
            // in acs/score_levelstart.h
            Score_Reset(pln);
        }
    }

    if (classNum == Cl_Dakkaguy)
    {
        if (!intraHubEnter)
        {
            Dakka_ScrapperStart(0);
        }

        if (entered)
        {
            int hasShotgun  = CheckInventory("DWep_Shotgun");
            int hasChaingun = CheckInventory("DWep_Chaingun");
            int hasPlasma   = CheckInventory("DWep_PlasmaRifle");
            int hasBFG      = CheckInventory("DWep_BFG9000");

            Sender_SetData(pln, S2C_D_PLASMASTART, hasPlasma);
            Sender_SetData(pln, S2C_D_BFGSTART,    hasBFG);

            if (!intraHubEnter)
            {
                if (hasShotgun) { GiveInventory("DakkaShotgunTracker", 1); }
                else            { TakeInventory("DakkaShotgunTracker", 0x7FFFFFFF); }

                if (hasChaingun) { GiveInventory("DakkaChaingunTracker", 1); }
                else             { TakeInventory("DakkaChaingunTracker", 0x7FFFFFFF); }
            }

            // We don't handle S2C_D_SHOT2SSG or S2C_CHAIN2MINI here because
            //  the CVar controlling them could change mid-game. That's handled
            //  in the enter loop.
            //
            // We don't need to worry about dakka_bundleplasma and dakka_bundlebfg.
            //  Those are handled in pickup/dakka_wepdisplay.h.
            //
            // The CVars might also play oddly with sv_coop_loseinventory and
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

    Dakka_BackpackStart();

    if (classNum == Cl_Dakkaguy)
    {
        Dakka_ScrapperStart(60);
    }
}
