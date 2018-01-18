#define TRACE_BULLET        0
#define TRACE_ARC_FIRER     2
#define TRACE_ARC_MASTER    3
#define TRACE_BFG           4
#define TRACE_BFG_INSTANT   5
#define TRACE_BFG_DELAYED   6


// DakkaTracer is the tracer actor
// DakkaTracerBright for lesseffects version

script "Dakka_Tracer" (int which, int yoff, int zoff)
{
    if (!IsServer) { terminate; }

    int shotX = GetActorX(0);
    int shotY = GetActorY(0);
    int shotZ = GetActorZ(0);

    switch (which)
    {
      default:
        SetActivatorToTarget(0);
        break;

      case TRACE_ARC_MASTER:
        SetActivator(0, AAPTR_MASTER);
        break;
    }

    if (ClassifyActor(0) & ACTOR_WORLD) { terminate; }

    int myTID = defaultTID(-1);

    int myX = GetActorX(0);
    int myY = GetActorY(0);
    int myZ = GetActorZ(0) + GetActorViewHeight(myTID);

    int myAngle = GetActorAngle(0);
    int myPitch = GetActorPitch(0);

    int pointX;

    switch (which)
    {
      default:
        pointX = 12.0;
        break;

      case TRACE_ARC_FIRER:
      case TRACE_BFG:
        pointX = 20.0;
        break;

      case TRACE_ARC_MASTER:
        pointX = 0;
        break;
    }

    // Negative y should mean left, not right, dammit
    int pointY = -itof(yoff);
    int pointZ =  itof(zoff);
    
    Rotate3D(pointX, pointY, pointZ, myAngle, myPitch);
    int spawnX = myX + Rotate3D_Ret[0];
    int spawnY = myY + Rotate3D_Ret[1];
    int spawnZ = myZ + Rotate3D_Ret[2];

    
    int tracerTID1 = UniqueTID();
    SpawnForced("TracerDummy", spawnX, spawnY, spawnZ, tracerTID1);

    int tracerTID2 = UniqueTID();
    SpawnForced("TracerDummy",  shotX,  shotY,  shotZ, tracerTID2);

    switch (which)
    {
      default:
        if (ConsolePlayerNumber() == -1)
        {
            ACS_NamedExecuteAlways("Dakka_Tracer_Client", 0, which, tracerTID1, tracerTID2);
        }
        else
        {
            ACS_NamedExecuteWithResult("Dakka_Tracer_Client", which, tracerTID1, tracerTID2);
        }
        break;

      case TRACE_BFG:
        // These will be in dakka_bfg.h
        ACS_NamedExecuteWithResult("Dakka_BFG_Server", tracerTID1, tracerTID2);
        
        if (ConsolePlayerNumber() == -1)
        {
            ACS_NamedExecuteWithResult("Dakka_BFG_Client", 0, tracerTID1, tracerTID2);
        }
        else
        {
            ACS_NamedExecuteWithResult("Dakka_BFG_Client", tracerTID1, tracerTID2);
        }
        break;

      case TRACE_ARC_FIRER:
      case TRACE_ARC_MASTER:
        if (ConsolePlayerNumber() == -1)
        {
            ACS_NamedExecuteAlways("Dakka_Lightning", 0, which, tracerTID1, tracerTID2);
        }
        else
        {
            ACS_NamedExecuteWithResult("Dakka_Lightning", which, tracerTID1, tracerTID2);
        }
        break;
    }
}


script "Dakka_Tracer_Client" (int which, int startTID, int endTID) clientside
{
    int waitTimer = 0;

    while (!(IsTIDUsed(startTID) && IsTIDUsed(endTID)))
    {
        waitTimer++;
        Delay(1);
        if (waitTimer > 36) { terminate; }
    }

    int startX = GetActorX(startTID);
    int startY = GetActorY(startTID);
    int startZ = GetActorZ(startTID);

    int endX   = GetActorX(endTID);
    int endY   = GetActorY(endTID);
    int endZ   = GetActorZ(endTID);

    int dX = endX - startX;
    int dY = endY - startY;
    int dZ = endZ - startZ;

    int dist = magnitudeThree_f(dX, dY, dZ);

    int nX = FixedDiv(dX, dist);
    int nY = FixedDiv(dY, dist);
    int nZ = FixedDiv(dZ, dist);

    int lesseffects = GetCVar("dakka_cl_lesseffects");

    int particleType = "";
    int density;
    int speed;

    switch (which)
    {
      case TRACE_BULLET:
        if (GetCVar("dakka_cl_notracers") > 0) { break; }

        speed = 512.0;

        if (lesseffects)
        {
            particleType = "DakkaTracerBright";
            density      = 36.0;
        }
        else
        {
            particleType = "DakkaTracer";
            density      = 12.0;
        }
        break;

      case TRACE_ARC_FIRER:
      case TRACE_ARC_MASTER:
        speed = 0;
        particleType = "LanceArcTrail";
        density      = cond(lesseffects, 32.0, 8.0);
    }

    if (stringBlank(particleType)) { terminate; }

    // miraculously, this works on both ints and fixed
    int startPoint = mod(dist, density) / 2;

    int step;
    int ticDistance = startPoint;

    for (step = startPoint; step < dist; step += density)
    {
        int spawnX = startX + FixedMul(step, nX);
        int spawnY = startY + FixedMul(step, nY);
        int spawnZ = startZ + FixedMul(step, nZ);

        SpawnForced(particleType, spawnX, spawnY, spawnZ);

        ticDistance += density;

        if (speed > 0)
        {
            int ticWait = ticDistance / speed;
            Delay(ticWait);
            ticDistance -= (ticWait * speed);
        }
    }
}

