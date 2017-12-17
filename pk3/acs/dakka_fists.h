function void Dakka_FistTap(void)
{
    if (inputPressed(BT_ATTACK)) { SetInventory("DakkaFistTap_Main", 5); }
    else { TakeInventory("DakkaFistTap_Main", 1); }
    
    if (inputPressed(BT_ALTATTACK)) { SetInventory("DakkaFistTap_Alt", 5); }
    else { TakeInventory("DakkaFistTap_Alt", 1); }
}

script "Dakka_FistHit" (void)
{
    int myTID = defaultTID(0);
    
    SetActivator(0, AAPTR_TARGET);
    int firerTID      = defaultTID(0);
    int punchSpeed    = CheckInventory("DakkaFistSpeed");
    int isBerserked   = CheckInventory("PowerStrength");
    int primaryTapped = CheckInventory("DakkaFistTap_Main") > 0;
    int finisher      = primaryTapped && (punchSpeed >= 25);
    
    SetActivator(myTID, AAPTR_TRACER);
    if (ClassifyActor(0) & ACTOR_WORLD)
    {
        SetActivator(myTID);
        ACS_NamedExecuteWithResult("Dakka_FistMiss");
        terminate;
    }
    
    int hitTID_old   = ActivatorTID();
    int hitTID_new   = defaultTID(0);
    int hitShootable = CheckFlag(0, "SHOOTABLE");
    int hitInvuln    = CheckFlag(0, "NODAMAGE") || CheckFlag(0, "INVULNERABLE");
    int hitHealth    = GetActorProperty(0, APROP_Health);
    int hitHealthMax = GetActorProperty(0, APROP_SpawnHealth);
    
    if (!hitShootable)
    {
        Thing_ChangeTID(hitTID_new, hitTID_old);
        SetActivator(myTID);
        ACS_NamedExecuteWithResult("Dakka_FistMiss");
        terminate;
    }
    
    int hitDamage, hitThrust = 0, forcePain = false;
    
    if (finisher && !hitInvuln && (hitHealth <= 70))
    {
        hitDamage = 70;
        hitThrust = 10.0;
        forcePain = true;
        GiveActorInventory(firerTID, "DakkaFistFinisher", 1);
        GiveActorInventory(firerTID, "DakkaFistQuake2", 1);
        ThingSound(myTID, "dakka/explode", 127);
    }
    else
    {
        hitDamage = 7 + (min(15, punchSpeed) / 5);
        if (primaryTapped) { hitDamage += 1; }
        
        GiveActorInventory(firerTID, "DakkaFistSpeed", 1 + cond(primaryTapped, 4, 1));
        GiveActorInventory(firerTID, "DakkaFistQuake1", 1);
        ThingSound(myTID, "dakka/punch", 127);
    }
    
    if (isBerserked) { hitDamage *= 3; hitThrust *= 2; }
    
    SetActivator(myTID);
    ACS_NamedExecuteWithResult("Dakka_FistDamage", hitDamage, hitThrust);
    
    Thing_ChangeTID(hitTID_new, hitTID_old);
}

script "Dakka_FistDamage" (int damage, int thrust, int forcepain)
{
    int myTID = defaultTID(-1);

    SetActivator(0, AAPTR_TRACER);
    if (ClassifyActor(0) & ACTOR_WORLD) { terminate; }

    int hisTID     = ActivatorTID();
    int hisTID_new = defaultTID(-1);

    SetActivator(myTID, AAPTR_TARGET);
    
    if (forcePain && !(CheckFlag(hisTID_new, "INVULNERABLE") || CheckFlag(hisTID_new, "NOPAIN")))
    {
        SetActorState(hisTID_new, "Pain.Punch");
    }

    Thing_Damage2(hisTID_new, damage, "Punch");
    
    if (thrust > 0)
    {
        SetActorVelocity(hisTID_new, FixedMul(thrust, cos(GetActorAngle(0))),
                                     FixedMul(thrust, sin(GetActorAngle(0))),
                                     0, true, false);
    }
    
    int oldAng = GetActorAngle(0);
    int newAng = VectorAngle(GetActorX(hisTID_new) - GetActorX(0),
                             GetActorY(hisTID_new) - GetActorY(0));
    
    int angDiff = angleDifference(oldAng, newAng);
    
    if      (angDiff >  0.02) { angDiff =  0.02; }
    else if (angDiff < -0.02) { angDiff = -0.02; }
    
    ACS_NamedExecuteAlways("Dakka_FistLockon", 0, angDiff);
    Thing_ChangeTID(hisTID_new, hisTID);
}


script "Dakka_FistLockon" (int angDiff) clientside
{
    int left = angDiff;
    for (int i = 0; i < 3; i++)
    {
        int angDelta = angDiff / 3;
        ChangeActorAngle(0, GetActorAngle(0) + angDelta, true);
        left -= angDelta;
        Delay(1);
    }
    
    ChangeActorAngle(0, GetActorAngle(0) + left, true);
}


script "Dakka_FistBlock" (int reflectTime, int resistTime)
{
    GiveInventory("DakkaBlockResistance", 1);
    GiveInventory("DakkaBlockReflection", 1);
    
    int t = 0;
    int endTime = max(reflectTime, resistTime);
    
    for (t = 0; t <= endTime; t++)
    {
        if (t == reflectTime) { GiveInventory("DakkaUnblockReflection", 1);          }
        if (t == resistTime)  { TakeInventory("DakkaBlockResistance",   0x7FFFFFFF); }
        Delay(1);
    }
}