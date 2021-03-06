function void Pistols_SpreadRecovery(void)
{
    if (CheckInventory("DakkaPistolSpread"))
    {
        TakeInventory("DakkaPistolSpread", 1);
    }
}

function int Pistols_BulletsLeft(void)
{
    if (GetCVar("dakka_infinitepistol") || HasInfiniteAmmo())
    {
        return GetAmmoCapacity("DakkaBullet_50AE");
    }
    
    return CheckInventory("DakkaBullet_50AE");
}


function void Pistols_CapBulletsLeft(void)
{
    int bullets_raw = CheckInventory("DakkaBullet_50AE");
    int bullets     = Pistols_BulletsLeft();
    
    int capped = min(CheckInventory("DakkaPistol_ShotsLeft"), bullets);
    SetInventory("DakkaPistol_ShotsLeft", capped);
    
    // This is so that if dakka_infinitepistol is true, you won't ever have 0 ammo
    //  (and therefore trigger the empty switch when you try to fire)
    SetInventory("DakkaBullet_50AE", max(bullets_raw, capped));
}


script "Dakka_PistolSpread" (int axis, int mult)
{
    int ret;
    int spreadMod = CheckInventory("DakkaPistolSpread");
    mult = cond(mult > 0, itofDiv(mult, 100), 1.0);
    
    if (axis == 1) // vertical spread
    {
        ret = 0.09 * spreadMod;
    }
    else // horizontal spread
    {
        ret = 0.11 * spreadMod;
    }
    
    //Log(s:cond(axis == 1, "Y", "X"), s:" spread: ", f:ret);
    SetResultValue(FixedMul(ret, mult));
}


script "Dakka_PistolReload" (void)
{
    int maxBullets = min(GetAmmoCapacity("DakkaPistol_ShotsLeft"), Pistols_BulletsLeft());
    SetInventory("DakkaPistol_ShotsLeft", maxBullets);
}


script "Dakka_PistolFull" (void)
{
    int bullets    = CheckInventory("DakkaPistol_ShotsLeft");
    int maxBullets = min(GetAmmoCapacity("DakkaPistol_ShotsLeft"), Pistols_BulletsLeft());
    SetResultValue(bullets >= maxBullets);
}


script "Dakka_CanPistolReload" (int noflag)
{
    int shotsCurrent = CheckInventory("DakkaPistol_ShotsLeft");
    int shotsAfter   = min(GetAmmoCapacity("DakkaPistol_ShotsLeft"), Pistols_BulletsLeft());
    
    if (noflag)
    {
        SetResultValue(shotsAfter > shotsCurrent);
    }
    else
    {
        // WRF_ALLOWRELOAD == 16
        SetResultValue(cond(shotsAfter > shotsCurrent, 16, 0));
    }
}


#define PUAC_SHELL      0x01
#define PUAC_GRENADE    0x02
#define PUAC_5MM        0x04
#define PUAC_FLAMER     0x08
#define PUAC_ROCKET     0x10
#define PUAC_CELL       0x20

script "Dakka_PickedUpAClip" (int count, int check)
{
    if (GetCVar("sv_unlimited_pickup"))
    {
        GiveInventory("DakkaBullet_50AE", count);
        SetResultValue(true);
        terminate;
    }
        
    if (CheckInventory("DakkaBullet_50AE") >= GetAmmoCapacity("DakkaBullet_50AE"))
    {
        SetResultValue(false);
        terminate;
    }   
    
    if (check)
    {
        int full = true;
        
        if (check & PUAC_SHELL)   { full &= CheckInventory("DakkaShells")       >= GetAmmoCapacity("DakkaShells"); }
        if (check & PUAC_GRENADE) { full &= CheckInventory("DakkaGrenades")     >= GetAmmoCapacity("DakkaGrenades"); }
        if (check & PUAC_5MM)     { full &= CheckInventory("DakkaBullet_5mm")   >= GetAmmoCapacity("DakkaBullet_5mm"); }
        if (check & PUAC_FLAMER)  { full &= CheckInventory("DakkaFlamerFuel")   >= GetAmmoCapacity("DakkaFlamerFuel"); }
        if (check & PUAC_ROCKET)  { full &= CheckInventory("DakkaRockets")      >= GetAmmoCapacity("DakkaRockets"); }
        if (check & PUAC_CELL)    { full &= CheckInventory("DakkaCells")        >= GetAmmoCapacity("DakkaCells"); }
        
        if (full)
        {
            SetResultValue(false);
            terminate;
        }
    }
    
    GiveInventory("DakkaBullet_50AE", count);
    SetResultValue(true);
}