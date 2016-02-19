function void ClearPoints(int pln, int bonustime)
{
    int i;
    for (i = 0; i < BONUSCOUNT; i++)
    {
        if (LastBonus[pln][i] == bonustime)
        {
            BonusValues[pln][i] = 0;
        }
    }
}


// Point multipliers:
//
// EFFICIENCY:
// - Spree: the more dudes you kill in quick succession, the more points you get.
// - One stone: kill dudes in the same shot, get even more points on top of spree
// - Infighter: cause an infight, and everyone gets points
//
// STYLE:
// - Switcharoo: switch up your weapons and fire modes when fighting? get more points!
// - Air: kill enemies mid-flight, get more points
// - Curveball: kill an enemy without them being able to see you? get points.
// - Scrapping: scrapper kill
//
// DARING:
// - Brawler: use your fists to get kills
// - Bone-dry: kill enemies with no more than 25 hp
// - Sore loser: kill enemies while dead (overrides bone-dry)
// - Point blank: get close, get points
//
//
// note: rain grenades kinda break with One Stone because of how long they linger,
//       since monsters only know WHO killed them, not with WHAT
//       I could do damage types but *fuck that*
//       I really wish I could be more granular, but >acs

int TmpBonuses[BONUSCOUNT];

script "Dakka_Score" (int pointValue)
{
    int myhp = GetActorProperty(0, APROP_SpawnHealth);
    int i;
    if (pointValue == -1) { pointValue = SMult_Base(); }

    int myX = GetActorX(0);
    int myY = GetActorY(0);
    int myZ = GetActorZ(0);

    SetActorPosition(0, GetActorX(0), GetActorY(0), myZ+41.0, 0);
    GiveInventory("DakkaCurveballChecker", 1);
    int curveCheck = CheckInventory("DakkaCurveballToken");
    SetActorPosition(0, GetActorX(0), GetActorY(0), myZ, 0);

    if (!SetActivatorToTarget(0)) { terminate; }

    int pln = PlayerNumber();

    if (pln == -1)
    {
        if ((ClassifyActor(0) & ACTOR_MONSTER) && (GetActorProperty(0, APROP_Friendly) == 0))
        {
            ACS_NamedExecuteWithResult("Dakka_Infighter", pointValue);
        }

        terminate;
    }

    int plX = GetActorX(0);
    int plY = GetActorY(0);
    int plZ = GetActorZ(0);

    int points_switcharoo   = round(pointValue * SMult_WeaponSwitch(pln, myhp));
    int points_killstreak   = round(pointValue * SMult_Killstreak(pln));
    int points_efficiency   = round(pointValue * SMult_Efficiency(pln));
    int points_bonedry      = round(pointValue * SMult_BoneDry());
    int points_soreloser    = round(pointValue * SMult_SoreLoser());
    int points_brawler      = round(pointValue * SMult_Brawler());
    int points_air          = round(pointValue * SMult_Air(pln));
    int points_curveball    = round(pointValue * SMult_Curveball(curveCheck));
    int points_scrapping    = round(pointValue * SMult_Scrapping(pln));
    int points_pointblank   = round(pointValue * SMult_PointBlank(myX, myY, myZ, plX, plY, plZ));

    PlayerMapScores[pln] += pointValue;
    PlayerMapScores[pln] += points_switcharoo;
    PlayerMapScores[pln] += points_killstreak;
    PlayerMapScores[pln] += points_efficiency;
    PlayerMapScores[pln] += points_bonedry;
    PlayerMapScores[pln] += points_soreloser;
    PlayerMapScores[pln] += points_brawler;
    PlayerMapScores[pln] += points_air;
    PlayerMapScores[pln] += points_curveball;
    PlayerMapScores[pln] += points_scrapping;
    PlayerMapScores[pln] += points_pointblank;

    int bonustime = Timer();

    TmpBonuses[BS_BASE]         = pointValue;
    TmpBonuses[BS_SPREE]        = points_killstreak;
    TmpBonuses[BS_EFFICIENT]    = points_efficiency;
    TmpBonuses[BS_INFIGHTER]    = 0;
    TmpBonuses[BS_SWITCHAROO]   = points_switcharoo;
    TmpBonuses[BS_BONEDRY]      = points_bonedry;
    TmpBonuses[BS_SORELOSER]    = points_soreloser;
    TmpBonuses[BS_BRAWLER]      = points_brawler;
    TmpBonuses[BS_AIR]          = points_air;
    TmpBonuses[BS_CURVEBALL]    = points_curveball;
    TmpBonuses[BS_SCRAPPING]    = points_scrapping;
    TmpBonuses[BS_POINTBLANK]   = points_pointblank;

    for (i = 0; i < BONUSCOUNT; i++)
    {
        if (TmpBonuses[i] > 0)
        {
            BonusValues[pln][i] += TmpBonuses[i];
            LastBonus[pln][i]    = bonustime;
        }
    }

    AddKillstreak(pln, myhp);
    Delay(35);

    ClearPoints(pln, bonustime);
}

// monster got the kill
script "Dakka_Infighter" (int pointValue)
{
    int points_base      = pointValue;
    int points_infighter = round(pointValue * SMult_Infighter());
    int bonustime = Timer();

    int i;    
    
    for (i = 0; i < PLAYERMAX; i++)
    {
        if (!PlayerInGame(i)) { continue; }

        PlayerMapScores[i] += points_base;
        PlayerMapScores[i] += points_infighter;

        BonusValues[i][BS_BASE]       += points_base;
        BonusValues[i][BS_INFIGHTER]  += points_infighter;

        LastBonus[i][BS_BASE]       = bonustime;
        LastBonus[i][BS_INFIGHTER]  = bonustime;
    }

    Delay(35);

    for (i = 0; i < PLAYERMAX; i++)
    {
        ClearPoints(i, bonustime);
    }
}
