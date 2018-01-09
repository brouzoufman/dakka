#define WRF_NOSECONDARY     8

script "Dakka_MinigunReady" (void)
{
    if (CheckInventory("DakkaFlamerFuel"))
    {
        SetResultValue(0);
    }
    else
    {
        SetResultValue(WRF_NOSECONDARY);
    }
}

script "Dakka_InheritVelocity" (int ptr, int percentForward, int percentSide, int percentBackward)
{
    percentForward  = itof(cond(percentForward  == 0, 100, percentForward))  / 100;
    percentSide     = itof(cond(percentSide     == 0, 100, percentSide))     / 100;
    percentBackward = itof(cond(percentBackward == 0, 100, percentBackward)) / 100;
    
    int myTID_old = ActivatorTID();
    int myTID_new = UniqueTID();
    Thing_ChangeTID(0, myTID_new);

    SetActivator(0, ptr);
    if (ClassifyActor(0) & ACTOR_WORLD)
    {
        Thing_ChangeTID(myTID_new, myTID_old);
        terminate;
    }
    
    int ptrVelX   = GetActorVelX(0);
    int ptrVelY   = GetActorVelY(0);
    
    int ptrAng     = GetActorAngle(0);
    int ptrAngX    = cos(ptrAng);
    int ptrAngY    = sin(ptrAng);
    
    int velForward = dot2(ptrVelX, ptrVelY, ptrAngX, ptrAngY);
    int velForX    = FixedMul(ptrAngX, velForward);
    int velForY    = FixedMul(ptrAngY, velForward);
    int velSideX   = ptrVelX - velForX;
    int velSideY   = ptrVelY - velForY;
    
    int velForwardPercent = cond(velForward > 0, percentForward, percentBackward);
    
    int modVelX = FixedMul(velForX, velForwardPercent) + FixedMul(velSideX, percentSide);
    int modVelY = FixedMul(velForY, velForwardPercent) + FixedMul(velSideY, percentSide);
    
    SetActivator(myTID_new);
    SetActorVelocity(0, modVelX, modVelY, 0, true, false);
    Thing_ChangeTID(myTID_new, myTID_old);
}

#define MB_FIRERTID     0
#define MB_FIRERTID_OLD 1
#define MB_FIRERPLN     2
#define MB_FIRERTEAM    3
#define MB_FRIENDLY     4
#define MB_BURNERX      5
#define MB_BURNERY      6
#define MB_BURNERZ      7
#define MB_BURNDIST     8
#define MB_BURNINITIAL  9
#define MB_BURNTIME     10

int MinigunBurnInfo[11];

script "Dakka_SetupMinigunBurn" (int dist, int initial, int duration)
{
    MinigunBurnInfo[MB_BURNERX]     = GetActorX(0);
    MinigunBurnInfo[MB_BURNERY]     = GetActorY(0);
    MinigunBurnInfo[MB_BURNERZ]     = GetActorZ(0);
    MinigunBurnInfo[MB_BURNDIST]    = itof(dist);
    MinigunBurnInfo[MB_BURNINITIAL] = initial;
    MinigunBurnInfo[MB_BURNTIME]    = duration;
    
    SetActivator(0, AAPTR_TARGET);
    int firerTID_old = ActivatorTID();
    int firerTID_new = UniqueTID();
    Thing_ChangeTID(0, firerTID_new);
    
    MinigunBurnInfo[MB_FIRERTID]     = firerTID_new;
    MinigunBurnInfo[MB_FIRERTID_OLD] = firerTID_old;
    MinigunBurnInfo[MB_FIRERPLN]     = PlayerNumber();
    MinigunBurnInfo[MB_FIRERTEAM]    = GetPlayerInfo(PlayerNumber(), PLAYERINFO_TEAM);
    MinigunBurnInfo[MB_FRIENDLY]     = GetActorProperty(0, APROP_Friendly);
}

script "Dakka_UnsetupMinigunBurn" (void)
{
    Thing_ChangeTID(MinigunBurnInfo[MB_FIRERTID], MinigunBurnInfo[MB_FIRERTID_OLD]);
}



// Ripped these checks out of Arc_CheckTarget for the most part

script "Dakka_MinigunBurn" (void)
{
    int firerTID  = MinigunBurnInfo[MB_FIRERTID];
    int myTID_old = ActivatorTID();
    int myTID_new = UniqueTID();
    Thing_ChangeTID(0, myTID_new);
    
    // First check: did we target the firer?
    int testnum = random(1, 0x7FFFFFFF);
    
    SetInventory("SameThingChecker", testnum);
    SetActivator(firerTID);
    
    int sameDude = (testnum == CheckInventory("SameThingChecker"));
    
    SetActivator(myTID_new);
    TakeInventory("SameThingChecker", 0x7FFFFFFF);
    
    if (sameDude)
    {
        Thing_ChangeTID(myTID_new, myTID_old);
        terminate;
    }
    
    // Second check: are they allied to each other?
    int myPln    = PlayerNumber();
    int firerPln = MinigunBurnInfo[MB_FIRERPLN];
    
    if (myPln >= 0 && firerPln >= 0)
    {
        int allied = false;
    
        if (GameType() == GAME_NET_DEATHMATCH)
        {
            int myTeam    = GetPlayerInfo(myPln, PLAYERINFO_TEAM);
            int firerTeam = MinigunBurnInfo[MB_FIRERTEAM];
            int noTeamIndex = cond(IsZandronum, 4, 255);
            
            allied = ((myTeam == firerTeam) && (myTeam != noTeamIndex) && (firerTeam != noTeamIndex));
        }
        else
        {
            // If your friends can be hurt, they *will* be hurt
            allied = (GetCVar("teamdamage") <= 0);
        }
        
        if (allied)
        {
            Thing_ChangeTID(myTID_new, myTID_old);
            terminate;
        }
    }
    
    // Third check: are we actually in range?
    int myX = GetActorX(0);
    int myY = GetActorY(0);
    int myZ = GetActorZ(0);
    int myRadius = GetActorProperty(0, APROP_Radius);
    int myHeight = GetActorProperty(0, APROP_Height);
    
    int burnX = MinigunBurnInfo[MB_BURNERX];
    int burnY = MinigunBurnInfo[MB_BURNERY];
    int burnZ = MinigunBurnInfo[MB_BURNERZ];

    int myX_closest = middle(burnX, safeAdd(myX, myRadius), safeAdd(myX, -myRadius));
    int myY_closest = middle(burnY, safeAdd(myY, myRadius), safeAdd(myY, -myRadius));
    int myZ_closest = middle(burnZ, safeAdd(myZ, myHeight), myZ);
    
    int dx   = myX_closest - burnX;
    int dy   = myY_closest - burnY;
    int dz   = myZ_closest - burnZ;
    
    int dist = VectorLength(VectorLength(dx, dy), dz);
    
    if (dist > MinigunBurnInfo[MB_BURNDIST])
    {
        Thing_ChangeTID(myTID_new, myTID_old);
        terminate;
    }
    
    ACS_NamedExecuteWithResult("Dakka_MinigunAfterburn", firerTID, myTID_new);
    Thing_ChangeTID(myTID_new, myTID_old);
}

#define AFTERBURNDAMAGE     15

script "Dakka_MinigunAfterburn" (int firerTID, int myTID)
{
    SetActivator(myTID);
    
    int initialBurn = CheckInventory("MinigunNewBurn");
    int burnTimer   = CheckInventory("MinigunBurnTimer");
    
    SetInventory("MinigunNewBurn",   max(initialBurn,   MinigunBurnInfo[MB_BURNINITIAL]));
    SetInventory("MinigunBurnTimer", max(burnTimer,     MinigunBurnInfo[MB_BURNTIME]));
    
    if (burnTimer > 0) { terminate; }
    
    // since TIDs change, keep track of firer and target through actor pointers
    int pointerTID = UniqueTID();
    int myX = GetActorX(0);
    int myY = GetActorY(0);
    int myZ = GetActorZ(0);
    
    SpawnForced("MinigunPointerDummy", myX,myY,myZ, pointerTID);
    SetActivator(pointerTID);
    SetPointer(AAPTR_TARGET, firerTID);
    SetPointer(AAPTR_TRACER, myTID);
    
    // we need to track total burn time to deal accurate afterburn damage
    int timeBurning    = 0;
    int flameTimer     = 0;
    int directBurnTime = 0;
    
    while (true)
    {
        SetActivator(pointerTID, AAPTR_TRACER);
        if (ClassifyActor(0) & ACTOR_WORLD) { break; }
        
        // Handle this here or else this CVar will do jack shit
        int powerlevel      = middle(0, GetCVar("dakka_powerlevel") + POWERLEVEL_CENTER,   POWERLEVEL_COUNT  -1);
        int powermult       = DakkaPowerMults[powerlevel];
        
        int burnDamage = 0;
        
        initialBurn = CheckInventory("MinigunNewBurn");
        
        if (initialBurn > 0)
        {
            initialBurn += min((directBurnTime++) / 10, 7);
        }
        else
        {
            directBurnTime = max(0, directBurnTime - 3);
        }
        
        burnDamage += FixedMul(initialBurn, powermult);
        TakeInventory("MinigunNewBurn", 0x7FFFFFFF);
        
        burnTimer   = CheckInventory("MinigunBurnTimer");
        
        if (burnTimer > 0)
        {
            int adjustedBurnDmg = FixedMul(AFTERBURNDAMAGE, powermult);
            
            // split the calculation by seconds and by tics to delay overflows
            int afterburn_prev = (( timeBurning    / 35) * adjustedBurnDmg) + (( (timeBurning    % 35) * adjustedBurnDmg) / 35);
            int afterburn_next = (((timeBurning+1) / 35) * adjustedBurnDmg) + ((((timeBurning+1) % 35) * adjustedBurnDmg) / 35);
            burnDamage += afterburn_next - afterburn_prev;
            TakeInventory("MinigunBurnTimer", 1);
        }
        
        //Log(s:"(", n:0, s:"\c-) Burn damage: ", d:burnDamage, s:" (", d:initialBurn, s:", ", d:burnTimer, s:")");
        
        myX = GetActorX(0);
        myY = GetActorY(0);
        myZ = GetActorZ(0) + (GetActorProperty(0, APROP_Height) / 2);
        
        // Do this for sound purposes
        SetActivator(pointerTID);
        Warp(0, myX, myY, myZ, 0, WARPF_ABSOLUTEPOSITION | WARPF_NOCHECKPOSITION | WARPF_INTERPOLATE);
        SetActivator(pointerTID, AAPTR_TRACER);
        
        if (burnDamage > 0 && !isDead(0))
        {
            SetActivator(pointerTID, AAPTR_TARGET);
            
            int fireTID = UniqueTID();
            SpawnForced("MinigunBurner", myX,myY,myZ, fireTID);
            SetUserVariable(fireTID, "user_damage",     burnDamage);
            SetUserVariable(fireTID, "user_painfactor", cond(initialBurn, 3, 15));
            
            if (!(ClassifyActor(0) & ACTOR_WORLD))
            {
                int firerTID_old = ActivatorTID();
                int firerTID_new = UniqueTID();
                Thing_ChangeTID(0, firerTID_new);
                
                SetActivator(fireTID);
                SetPointer(AAPTR_TARGET, firerTID_new);
                Thing_ChangeTID(firerTID_new, firerTID_old);
            }
            
            SetActorState(fireTID, "Burn");
        }
        
        if (flameTimer == 0)
        {
            SetActivator(pointerTID, AAPTR_TRACER);
            
            int myXYRadius = GetActorProperty(0, APROP_Radius);
            int myZRadius  = GetActorProperty(0, APROP_Height) / 2;
            
            int randX = random( 0.1, 0.6) * randSign();
            int randY = random( 0.1, 0.6) * randSign();
            int randZ = random(-0.8, 0.4);
            
            SpawnForced("MinigunAfterburnFlame", myX + FixedMul(myXYRadius, randX),
                                                 myY + FixedMul(myXYRadius, randY),
                                                 myZ + FixedMul(myZRadius,  randZ));
            flameTimer = random(3, 7);
        }
        
        if (burnTimer == 1) { break; }
        timeBurning++;
        flameTimer--;
        Delay(1);
    }
    
    for (int i = 0; i < 48; i++)
    {
        int vol = 0.3 - (i + 1) * 0.00625;
        SoundVolume(pointerTID, CHAN_BODY, vol);
        Delay(1);
    }
    Thing_Remove(pointerTID);
}