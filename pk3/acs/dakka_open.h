script DAKKA_OPEN open
{
    // Absorbed this from the PICKUP_OPEN script.

    Pickup_IsZandronum(); // side effect sets IsZandronum
    IsServer = true;

    Score_CalcMapPoints();

    while (true)
    {
        // Update CVars for everyone
        
        int i;

        for (i = 0; i < PLAYERMAX; i++)
        {
            // Update CVars for players
            Sender_SetData(i, S2C_D_BUNDLEPLASMA, GetCVar("dakka_bundleplasma") == 1);
        }

        // Absorbed from PICKUP_OPEN
        Sender_UpdateClients();
        Sender_ActuallySend();
        Delay(1);
    }
}


script DAKKA_OPEN_CLIENT open clientside
{
    int cpln = ConsolePlayerNumber();

    while (true)
    {
        // In score/score_display.h
        // TODO: Move this to clientside display,
        //       using the pickup client->server system
        Score_Update(cpln);
        Delay(1);
    }
}
