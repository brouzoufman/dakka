int TMP_Messages[MMSG_COUNT];


script "Dakka_MoreMessages" (int index)
{
    int pln = PlayerNumber();

    int classNum = CMSG_MessageData[pln][MDATA_CLASSNUM];
    int itemNum  = CMSG_MessageData[pln][MDATA_ITEMNUM];
    int dropped  = CMSG_MessageData[pln][MDATA_DROPPED];

    int moremessages = GetCVar("dakka_cl_moremessages");

    if (dropped || !moremessages)
    {
        SetResultValue(PKP_Messages[itemNum][classNum+1]);
        terminate;
    }

    int i;
    int msgcount = 0;

    for (i = 0; i < MMSG_COUNT; i++)
    {
        str msg = StrParam(s:MMSG_ExtraMessages[index][i]);
        
        if (GetChar(msg, 0) == '\\' && GetChar(msg, 1) == '$')
        {
            msg = sliceString(msg, 1, StrLen(msg));
        }
        else if (GetChar(msg, 0) == '$')
        {
            msg = StrParam(l:sliceString(msg, 1, StrLen(msg)));
        }

        if (!stringBlank(msg))
        {
            TMP_Messages[msgcount++] = msg;
        }
    }

    if (msgcount == 0)
    {
        SetResultValue(PKP_Messages[itemNum][classNum+1]);
        terminate;
    }

    SetResultValue(TMP_Messages[random(0, msgcount-1)]);
}
