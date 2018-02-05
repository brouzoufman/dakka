// Yes I just copypasted DAKKA_TRACER_CLIENT. Fuckin' sue me, I'm not cramming
//  all of the BFG's stuff into that function.

function void BFG_AutoReload(void)
{
    int pln = PlayerNumber();

    // Don't tick down auto reload timer if it's in our hands
    if (CheckWeapon("DWep_BFG9000")) { return; }

    int time = max(0, AutoReloadCooldowns[pln][1] - 1);
    if (time == 0) { SetInventory("BFGNeedsReload", 0); }

    AutoReloadCooldowns[pln][1] = time;
}

script "Dakka_BFGAltfired" (int t)
{
    int pln = PlayerNumber();
    AutoReloadCooldowns[pln][1] = t;
    GiveInventory("BFGNeedsReload", 1);
}



#define BFGPICKFLAGS_THINGS (MF_SHOOTABLE)
#define BFGPICKFLAGS_LINES  (ML_BLOCKING | ML_BLOCKEVERYTHING | ML_BLOCKPROJECTILE)

function int Dakka_GetNewTarget(int ptrTID)
{
    int myTID_old = ActivatorTID();
    int myTID_new = UniqueTID();
    Thing_ChangeTID(0, myTID_new);

    if (ptrTID == 0)
    {
        ptrTID = UniqueTID();
        SpawnForced("BFGPointerDummy", GetActorX(0), GetActorY(0), GetActorZ(0), ptrTID);

        SetActivator(ptrTID);
        SetPointer(AAPTR_TARGET, myTID_new);
        SetActivator(myTID_new);
    }

    int myAngle = GetActorAngle(0);
    int myPitch = GetActorPitch(0);

    int targetTID_old = PickActor(0, myAngle, myPitch, 0x7FFFFFFF, 0, BFGPICKFLAGS_THINGS, BFGPICKFLAGS_LINES, PICKAF_RETURNTID);
    int targetTID_new = UniqueTID();

    int t = Timer();

    if (PickActor(0, myAngle, myPitch, 0x7FFFFFFF, targetTID_new, BFGPICKFLAGS_THINGS, BFGPICKFLAGS_LINES, PICKAF_FORCETID))
    {
        SetActivator(ptrTID);
        SetPointer(AAPTR_TRACER, targetTID_new);
        SetUserVariable(0, "user_timeout", t + 36);

        SetActivator(myTID_new);
        Thing_ChangeTID(targetTID_new, targetTID_old);
    }
    else
    {
        SetActivator(ptrTID, AAPTR_TRACER);
        int targetDead = (ClassifyActor(0) & ACTOR_WORLD) || isDead(0);
        int timedOut   = GetUserVariable(ptrTID, "user_timeout") <= t;
        SetActivator(myTID_new);

        if (targetDead || timedOut)
        {
            LineAttack(0, myAngle, myPitch, 0, "BFGCrosshairTarget_Puff", "None", 0x7FFFFFFF, FHF_NOIMPACTDECAL | FHF_NORANDOMPUFFZ, targetTID_new);

            if (!IsTIDUsed(targetTID_new))
            {
                // I feel like this shouldn't work because this starts right on top of us
                //   and yet it does work
                SpawnForced("BFGCrosshairTarget", GetActorX(0), GetActorY(0), GetActorZ(0) + GetActorViewHeight(0), targetTID_new);
                SetActorVelocity(targetTID_new, 32767 * FixedMul(cos(myAngle), cos(myPitch)),
                                                32767 * FixedMul(sin(myAngle), cos(myPitch)),
                                                32767 * -sin(myPitch), false, false);
            }

            SetActivator(ptrTID);
            SetPointer(AAPTR_TRACER, targetTID_new);
            Thing_ChangeTID(targetTID_new, 0);

            SetActivator(myTID_new);
        }
    }

    SetActorState(ptrTID, "KeepAlive");
    SetInventory("BFGPointerTID", ptrTID);
    Thing_ChangeTID(myTID_new, myTID_old);
    return ptrTID;
}



script "Dakka_SetupBFGStage2" (int facetracer, int changestate)
{
    if (!IsServer) { terminate; }

    int myTID_old = ActivatorTID();
    int myTID_new = UniqueTID();
    Thing_ChangeTID(0, myTID_new);

    SetActivator(0, AAPTR_TARGET);
    if (ClassifyActor(0) & ACTOR_WORLD)
    {
        if (changestate) { SetActorState(0, "Stage2_Fail"); }
        Thing_ChangeTID(myTID_new, myTID_old);
        SetResultValue(false);
        terminate;
    }

    SetActivator(CheckInventory("BFGPointerTID"), AAPTR_TRACER);
    if (ClassifyActor(0) & ACTOR_WORLD)
    {
        if (changestate) { SetActorState(0, "Stage2_Fail"); }
        Thing_ChangeTID(myTID_new, myTID_old);
        SetResultValue(false);
        terminate;
    }

    int targetTID_old = ActivatorTID();
    int targetTID_new = UniqueTID();
    Thing_ChangeTID(0, targetTID_new);

    SetActivator(myTID_new);
    SetPointer(AAPTR_TRACER, targetTID_new);

    int dx,dy,dz;

    if (facetracer)
    {
        dx = GetActorX(targetTID_new) - GetActorX(0);
        dy = GetActorY(targetTID_new) - GetActorY(0);
        dz = GetActorZ(targetTID_new) - GetActorZ(0) + (GetActorProperty(targetTID_new, APROP_Height) / 2);
    }
    else
    {
        dx = GetActorVelX(0);
        dy = GetActorVelY(0);
        dz = GetActorVelZ(0);
    }

    SetActorAngle(0,  VectorAngle(dx, dy));
    SetActorPitch(0, -VectorAngle(VectorLength(dx, dy), dz));

    Thing_ChangeTID(myTID_new,     myTID_old);
    Thing_ChangeTID(targetTID_new, targetTID_old);

    if (changestate) { SetActorState(0, "Stage2_Success"); }
    SetResultValue(true);
}



script "Dakka_BFGHomeIn" (int speedadd, int speedmax, int evenIfBehind)
{
    if (!IsServer) { terminate; }

    speedadd = itof(speedadd);
    speedmax = itof(speedmax);

    int myTID_old = ActivatorTID();
    int myTID_new = UniqueTID();
    Thing_ChangeTID(0, myTID_new);

    int x = GetActorX(0);
    int y = GetActorY(0);
    int z = GetActorZ(0);

    int angle = GetActorAngle(0);
    int pitch = GetActorPitch(0);

    int aimX = FixedMul(cos(angle), cos(pitch));
    int aimY = FixedMul(sin(angle), cos(pitch));
    int aimZ = -sin(pitch);

    int tx,ty,tz;

    SetActivator(0, AAPTR_TRACER);

    if ((ClassifyActor(0) & ACTOR_WORLD) || isDead(0))
    {
        if (GetUserVariable(myTID_new, "user_hadtarget"))
        {
            tx = GetUserVariable(myTID_new, "user_targetx");
            ty = GetUserVariable(myTID_new, "user_targety");
            tz = GetUserVariable(myTID_new, "user_targetz");
        }
        else // I guess just keep going then?
        {
            tx = x + FixedMul(speedmax, aimX);
            ty = y + FixedMul(speedmax, aimY);
            tz = z + FixedMul(speedmax, aimZ);
        }
    }
    else
    {
        tx = GetActorX(0);
        ty = GetActorY(0);
        tz = GetActorZ(0) + (GetActorProperty(0, APROP_Height) / 2);

        SetUserVariable(myTID_new, "user_hadtarget", true);
        SetUserVariable(myTID_new, "user_targetx", tx);
        SetUserVariable(myTID_new, "user_targety", ty);
        SetUserVariable(myTID_new, "user_targetz", tz);
    }

    int dx = tx - x;
    int dy = ty - y;
    int dz = tz - z;

    SetActivator(myTID_new);

    if (!evenIfBehind)
    {
        int distInFront = dot3(dx,dy,dz, aimX,aimY,aimZ);

        if (distInFront < 0)
        {
            SetResultValue(false);
            Thing_ChangeTID(myTID_new, myTID_old);
            terminate;
        }
    }

    int dmag = VectorLength(VectorLength(dx, dy), dz);
    int ndx = 0, ndy = 0, ndz = 0;

    if (dmag > 0)
    {
        ndx = FixedDiv(dx, dmag);
        ndy = FixedDiv(dy, dmag);
        ndz = FixedDiv(dz, dmag);
    }

    int vx  = GetActorVelX(0) + FixedMul(ndx, speedadd);
    int vy  = GetActorVelY(0) + FixedMul(ndy, speedadd);
    int vz  = GetActorVelZ(0) + FixedMul(ndz, speedadd);
    int vel = VectorLength(VectorLength(vx, vy), vz);

    if (speedmax > 0 && vel > speedmax)
    {
        int vdiff = FixedDiv(speedmax, vel);
        vx = FixedMul(vx, vdiff);
        vy = FixedMul(vy, vdiff);
        vz = FixedMul(vz, vdiff);
    }

    SetActorVelocity(0, vx,vy,vz, false,false);
    SetActorAngle(0,  VectorAngle(vx,vy));
    SetActorPitch(0, -VectorAngle(VectorLength(vx,vy), vz));

    SetResultValue(true);
}