#library "dakka_titlemap"

#include "zcommon.acs"
#include "dakka_commonFuncs.h"


#define MUSICCOUNT  3

int TitleMusic[MUSICCOUNT] =
{
    "DKTITLE1",
    "DKTITLE2",
    "DKTITLE3",
};


script "dakka_titlemap" open
{
    if (GameType() != GAME_TITLE_MAP) { terminate; }
    if (stricmp(StrParam(n:PRINTNAME_LEVELNAME), "DAKKA")) { terminate; }
    
    SetHudSize(320, 200, true);
    FadeRange(0,0,0, 1.0, 0,0,0, 1.0, 10.0);
    
    SetFont("TITLEPIC");
    HudMessage(s:"A"; HUDMSG_FADEOUT, 1, CR_UNTRANSLATED, 160.4, 100.0, 2.0, 1.0);

    Delay(105);
    
    // dakka title stuff here
    
    AmbientSound("dakka/hammerwall", 127);
    
    SetFont("DKLOGOF1");
    HudMessage(s:"A"; HUDMSG_PLAIN, 2, CR_UNTRANSLATED, 160.4, 10.1, 1.0);
    Delay(2);
    SetFont("DKLOGON1");
    HudMessage(s:"A"; HUDMSG_PLAIN, 2, CR_UNTRANSLATED, 160.4, 10.1, 1.0);
    
    Delay(10);
    
    AmbientSound("dakka/hammerwall", 127);
    
    SetFont("DKLOGOF2");
    HudMessage(s:"A"; HUDMSG_PLAIN, 2, CR_UNTRANSLATED, 160.4, 10.1, 1.0);
    Delay(2);
    SetFont("DKLOGON2");
    HudMessage(s:"A"; HUDMSG_PLAIN, 2, CR_UNTRANSLATED, 160.4, 10.1, -1);
    
    Delay(10);
    
    AmbientSound("dakka/hammerwall", 127);
    
    SetFont("DKLOGOF3");
    HudMessage(s:"A"; HUDMSG_PLAIN, 2, CR_UNTRANSLATED, 160.4, 10.1, 1.0);
    Delay(2);
    SetFont("DKLOGON3");
    HudMessage(s:"A"; HUDMSG_PLAIN, 2, CR_UNTRANSLATED, 160.4, 10.1, -1);
    
    Delay(10);
    
    AmbientSound("dakka/hammerwall", 127);
    
    SetFont("DKLOGOF4");
    HudMessage(s:"A"; HUDMSG_PLAIN, 2, CR_UNTRANSLATED, 160.4, 10.1, 1.0);
    Delay(2);
    SetFont("DKLOGON4");
    HudMessage(s:"A"; HUDMSG_PLAIN, 2, CR_UNTRANSLATED, 160.4, 10.1, -1);
    
    Delay(10);
    
    ACS_NamedExecuteWithResult("titlemap_showtips");
    
    AmbientSound("dakka/hammerwall", 127);
    
    SetFont("DKLOGOF5");
    HudMessage(s:"A"; HUDMSG_PLAIN, 2, CR_UNTRANSLATED, 160.4, 10.1, 1.0);
    Delay(2);
    SetFont("DKLOGON5");
    HudMessage(s:"A"; HUDMSG_PLAIN, 2, CR_UNTRANSLATED, 160.4, 10.1, -1);
    
    ACS_NamedExecuteWithResult("titlemap_logoflash");
    
    Delay(35);
    
    SetMusic(TitleMusic[random(0, MUSICCOUNT-1)]);
    
    Delay(35);
    
    ACS_NamedExecuteWithResult("titlemap_playblink");
    
    // 140 + (4 * (10 + 2)) 2 + 35 + x = 350
    Delay(90);
    
    FadeRange(0,0,0, 1.0, 0,0,0, 0.0, 2.0);
    
    ACS_NamedExecuteWithResult("titlemap_camera");
    ACS_NamedExecuteWithResult("titlemap_spinny");
}


#define PIVOTANGLE_MIDDLE   0.875
#define PIVOTANGLE_SWAY     0.125
#define PIVOT_DISTANCE      2048.0
#define PIVOT_PERIOD        1050

script "titlemap_camera" (void)
{
    ChangeCamera(2, false, false);
    
    int pivotX = GetActorX(1);
    int pivotY = GetActorY(1);
    int pivotZ = GetActorZ(1);
    
    int ranOnce = false;
    
    while (true)
    {
        int pivotStep  = sin((Timer() * 1.0) / PIVOT_PERIOD);
        int pivotAngle = PIVOTANGLE_MIDDLE + FixedMul(pivotStep, PIVOTANGLE_SWAY);
        
        int fromX = GetActorX(2);
        int fromY = GetActorY(2);
        int fromZ = GetActorZ(2);
        
        int toX = pivotX + FixedMul(PIVOT_DISTANCE, cos(pivotAngle));
        int toY = pivotY + FixedMul(PIVOT_DISTANCE, sin(pivotAngle));
        int toZ = GetActorZ(1);
        
        SetActorAngle(2, pivotAngle - 0.5);
        
        if (!ranOnce)
        {
            SetActorPosition(2, toX, toY, toZ, false);
            ranOnce = true;
        }
        else
        {
            SetActorVelocity(2, toX - fromX, toY - fromY, toZ - fromZ, false, false);
        }
        
        Delay(1);
    }
}

script "titlemap_spinny" (void)
{
    while (true)
    {
        SetActorAngle(3, GetActorAngle(3) + 0.05);
        
        int fun = random(1.5, 2.5);
        
        int velX = FixedMul(fun, cos(GetActorAngle(3)));
        int velY = FixedMul(fun, sin(GetActorAngle(3)));
        
        SetActorVelocity(3, velX, velY, 0, true, true);
        
        Delay(1);
    }
}



#define DLOGO_FRAMECOUNT 21

int DakkaLogo_Frames[DLOGO_FRAMECOUNT] = 
{
    "DLOGOS01",
    "DLOGOS02",
    "DLOGOS03",
    "DLOGOS04",
    "DLOGOS05",
    "DLOGOS06",
    "DLOGOS07",
    "DLOGOS08",
    "DLOGOS09",
    "DLOGOS10",
    "DLOGOS11",
    "DLOGOS12",
    "DLOGOS13",
    "DLOGOS14",
    "DLOGOS15",
    "DLOGOS16",
    "DLOGOS17",
    "DLOGOS18",
    "DLOGOS19",
    "DLOGOS20",
    "DLOGOS21",
};

script "titlemap_logoflash" (void)
{
    Delay(random(70, 105));
    
    while (true)
    {
        int i;
        
        for (i = 0; i < DLOGO_FRAMECOUNT; i++)
        {
            SetFont(DakkaLogo_Frames[i]);
            SetHudSize(320, 200, true);
            HudMessage(s:"A"; HUDMSG_PLAIN, 2, CR_UNTRANSLATED, 160.4, 10.1, -1);
            Delay(1);
        }
        
        SetHudSize(320, 200, true);
        SetFont("DKLOGON5");
        HudMessage(s:"A"; HUDMSG_PLAIN, 2, CR_UNTRANSLATED, 160.4, 10.1, -1);
            
        Delay(random(140, 280));
    }
}

script "titlemap_playblink" (void)
{
    SetFont("DKPLAY");
    SetHudSize(320, 200, true);
    
    while (true)
    {
        HudMessage(s:"A"; HUDMSG_PLAIN, 3, CR_UNTRANSLATED, 160.4, 195.2, -1);
        Delay(24);
        
        HudMessage(s:""; HUDMSG_PLAIN, 3, CR_UNTRANSLATED, 160.4, 195.2, -1);
        Delay(24);
    }
}


script "titlemap_showtips" (void)
{
    Delay(12);
    ACS_NamedExecuteWithResult("titlemap_weptips", true, 10.0 + (1.0/3));
    
    Delay(24);
    ACS_NamedExecuteWithResult("titlemap_scoretips", true, 10.0);
    
    Delay(385);
    
    while (true)
    {
        int i;
        
        for (i = 0; i < 3; i++)
        {
            int msgDelay;
            
            if (random(0, 4) == 0)
            {
                msgDelay = ACS_NamedExecuteWithResult("titlemap_gametips");
            }
            else
            {
                msgDelay = ACS_NamedExecuteWithResult("titlemap_dumbtips");
            }
            
            Delay(70 + msgDelay);
        }
        
        ACS_NamedExecuteWithResult("titlemap_weptips",   false, 4.0);
        ACS_NamedExecuteWithResult("titlemap_scoretips", false, 4.0);
    
        Delay(210);
    }
}


function void ShowWeaponTips(int doFade, int forceColor, int overrideColor, int duration)
{
    int msgMode = HUDMSG_FADEOUT;
    if (doFade) { msgMode = HUDMSG_FADEINOUT; }
    
    int fistColor       = "DTitle_Fists";
    int scrapperColor   = "DTitle_Scrappers";
    int pistolColor     = "DTitle_Pistol";
    int pistolsColor    = "DTitle_Pistols";
    int shotgunColor    = "DTitle_Shotgun";
    int ssgColor        = "DTitle_SuperShotgun";
    int chaingunColor   = "DTitle_Chaingun";
    int minigunColor    = "DTitle_Minigun";
    int impalerColor    = "Red";
    int plasmaColor     = "DTitle_PlasmaLance";
    int bfgColor        = "Green";
    
    if (forceColor)
    {
        fistColor       = overrideColor;
        scrapperColor   = overrideColor;
        pistolColor     = overrideColor;
        pistolsColor    = overrideColor;
        shotgunColor    = overrideColor;
        ssgColor        = overrideColor;
        chaingunColor   = overrideColor;
        minigunColor    = overrideColor;
        impalerColor    = overrideColor;
        plasmaColor     = overrideColor;
        bfgColor        = overrideColor;
    }
    
    SetHudSize(320, 200, 0);
    SetFont("ARCFONT");
    
    HudMessage(s:"Fists";         msgMode | HUDMSG_COLORSTRING, 21, fistColor,        40.4,  80.0, duration, 1.0, 1.0);
    HudMessage(s:"Scrappers";     msgMode | HUDMSG_COLORSTRING, 22, scrapperColor,    40.4,  88.0, duration, 1.0, 1.0);
                                  
    HudMessage(s:"Pistol";        msgMode | HUDMSG_COLORSTRING, 23, pistolColor,     115.4,  80.0, duration, 1.0, 1.0);
    HudMessage(s:"Two pistols";   msgMode | HUDMSG_COLORSTRING, 24, pistolsColor,    115.4,  88.0, duration, 1.0, 1.0);
                                  
    HudMessage(s:"Shotgun";       msgMode | HUDMSG_COLORSTRING, 25, shotgunColor,    205.4,  80.0, duration, 1.0, 1.0);
    HudMessage(s:"Super Shotgun"; msgMode | HUDMSG_COLORSTRING, 26, ssgColor,        205.4,  88.0, duration, 1.0, 1.0);
                                  
    HudMessage(s:"Chaingun";      msgMode | HUDMSG_COLORSTRING, 27, chaingunColor,   280.4,  80.0, duration, 1.0, 1.0);
    HudMessage(s:"Minigun";       msgMode | HUDMSG_COLORSTRING, 28, minigunColor,    280.4,  88.0, duration, 1.0, 1.0);
                                  
    HudMessage(s:"Impaler";       msgMode | HUDMSG_COLORSTRING, 29, impalerColor,    80.4,  104.0, duration, 1.0, 1.0);
                                  
    HudMessage(s:"Lancer";        msgMode | HUDMSG_COLORSTRING, 30, plasmaColor,     160.4, 104.0, duration, 1.0, 1.0);
                                  
    HudMessage(s:"BFG9000";       msgMode | HUDMSG_COLORSTRING, 31, bfgColor,        240.4, 104.0, duration, 1.0, 1.0);
}

script "titlemap_weptips" (int flash, int duration)
{
    SetHudSize(320, 200, 0);
    SetFont("ARCFONT");
    
    if (flash)
    {
        AmbientSound("dakka/hammerwall", 127);
        HudMessage(s:"Weapons:"; HUDMSG_PLAIN | HUDMSG_COLORSTRING, 11, "DTitle_AllWhite", 160.4, 70.0, 0);
        Delay(2);
        HudMessage(s:"Weapons:"; HUDMSG_PLAIN, 11, CR_WHITE, 160.4, 70.0, 0);
        
        Delay(10);
        
        AmbientSound("dakka/hammerwall", 127);
        ShowWeaponTips(false, true, "DTitle_AllWhite", duration);
        Delay(2);
        
        // do this here to sync them up
        HudMessage(s:"Weapons:"; HUDMSG_FADEOUT, 11, CR_WHITE, 160.4, 70.0, duration, 1.0);
        ShowWeaponTips(false, false, "", duration);
    }
    else
    {
        HudMessage(s:"Weapons:"; HUDMSG_FADEINOUT, 11, CR_WHITE, 160.4, 70.0, duration, 1.0, 1.0);
        ShowWeaponTips(true, false, "", duration);
    }
}

int ScoreMessage = "\
First point reward\n\
\ckAmmo regen\n\
\n\
Second point reward\n\
\ckExtra life";

script "titlemap_scoretips" (int flash, int duration)
{
    SetHudSize(320, 200, 0);
    SetFont("ARCFONT");
    
    if (flash)
    {
        AmbientSound("dakka/hammerwall", 127);
        HudMessage(s:ScoreMessage; HUDMSG_PLAIN | HUDMSG_COLORSTRING, 41, "DTitle_AllWhite",     160.4, 145.0, 0);
        Delay(2);
        HudMessage(s:ScoreMessage; HUDMSG_FADEOUT | HUDMSG_COLORSTRING, 41, "White",             160.4, 145.0, duration, 1.0);
    }
    else
    {
        HudMessage(s:ScoreMessage; HUDMSG_FADEINOUT | HUDMSG_COLORSTRING, 41, "White",           160.4, 145.0, duration, 1.0, 1.0);
    }
}


#define GAMETIPCOUNT    14

int GameTips[GAMETIPCOUNT] =
{
    "The super shotgun has no refire delay, so hitting both mouse buttons in quick succession will fire whichever button you hit first, twice. Bring the pain!",
    "The impaler's alt-fire impales demons, surprisingly enough. Use it to bring stragglers close to their friends and blow them all up!",
    "Plasma nails pierce through enemies, similarly to the impaler primary fire. They don't penetrate nearly as far, but it's still extra damage, right?",
    "Dakkaguy can reload the super shotgun with his buttcheeks. Take advantage of that, and fill the downtime with more dakka!",
    "Dakkaguy takes reduced damage from his own explosions, but \canot\c- reduced thrust. This means exactly what you think it means.",
    "Shotgun grenades: they might not actually be rockets, but who cares?",
    "Rain grenades are best employed in multiples. Anything that manages to survive won't be able to retaliate under the storm of explosions.",
    "Your fists are silent, which is perfect for breaking those maps that force you to shoot a switch at the start.\n\nOr you could just shoot the switch anyway, since it lets you kill more demons.",
    "Spent ammo of all kinds refuels your scrappers. Respect the environment; scrap some demons before that meter tops off.",
    "The fatter the enemy, the better the minigun roasts them.\n\nThis is not a social commentary.\nNo, not even now. Shut up.",
    "Scrappers + small places = very dead demons.",
    "You can reload-cancel the SSG, as long as it didn't start the reload empty. This applies both to idle reloads and manual reloads.",
    "Minigun flames pierce invulnerability.\nBecause why not?",
    "Your weapons can still be swapped out while in a firing animation, so take advantage of it!",
};


#define GAMEHEADERCOUNT 5

int GameHeaders[GAMEHEADERCOUNT] =
{
    "Quick Tip:",
    "Tip in a Can:",
    "I bet you knew this already:",
    "Loading, please wait...",
    "PRO DAKKA STRATS",
};


#define DUMBTIPCOUNT 91

int DumbTips[DUMBTIPCOUNT] = 
{
    "When all you have is a minigun, everything starts looking like something that miniguns are good for. Which is everything.",
    "Balance is for chumps.",
    "ru \caDKAKGUY\c- n u mstu \caFGITH THE DMOENS\c- whi \caPOWEFRL WEAPONS\c- leki the \caSHTONGY OF SUEPR\c- to averge \caTHE WLROD\n\ngo now \caDAKAKGYU\c- and svu \caHRMUINTY\c-",
    "Shoot demons! Get points! Get ammo with those points! Shoot demons with that ammo!",
    "My immersion is ruined forever.",
    "What was the benchmark for quality before sliced bread?",
    "I'd buy this for a dollar.",
    "It's always goddamn skeletons.",
    "It is a mystery.",
    "One of these days, I am going to get a time machine, travel back to the Ion Storm offices of 1998, and punch John Romero in the face.",
    "Your opinion, my choice.",
    "Ford, you're turning into a penguin. Stop it.",
    "How was I supposed to know the big red glowing button labeled \"SELF DESTRUCT, DO NOT PUSH\" was going to do something?",
    "You know how the Doomguy has a pet rabbit? Well, Dakkaguy has a pet rocket. It's a friendly rocket. Never made a mess in the house, never barked at anyone - it was a well behaved rocket. Well, one day, as Hell was invading, some imp picked up the innocent rocket and slashed it. The rocket exploded in his face.\n\nDeserved it, too. Fucking fascist.",
    "Would it be considered sporting to update Samsara just to break the addons? No? Too bad.",
    "No wang for you.",
    "Roll to fondle yourself.",
    "What are you gonna do, stab me?",
    "To defeat the Cyberdemon, shoot at it until it dies.",
    "protip: git gud",
    "Hey, chaingun! The hell with respect!",
    "Dakka's guns work by one rule: would it be cool if they worked like that? If no, then they don't work like that.",
    "If a tree falls in the woods and no one is around to hear it, it should've had LifeAlert.",
    "You are huge! That means you're worth a lot of points!",
    "If you are reading this message, that means you are reading this message.",
    "Now with 100% more percentages!",
    "Perhaps the same could be said of all religions.",
    "Only you can prevent the world from being plunged balls-deep into an asspocalypse! Do your part today! Join the Buttpain Army!",
    "\cfDID YOU KNOW:\c- Silicon Knights bought some rights from Epic to use Unreal Engine 3 in one of their games, \cdToo Human\c-, for the Xbox 360. Epic then used UE3 to make \cdGears of War\c-, also for the Xbox 360. Silicon Knights sued Epic for working on Gears of War - again, made in UE3 - instead of making UE3 usable. Then it was discovered Too Human had parts of the UE3 engine in it \caanyway\c-.\n\nSilicon Knights did not think this through.",
    "RIP Cyberrunner 2013-2013 - it was too fast for Doom",
    "In the beginning were the words, and the words were \"fucking hacker il report u\".",
    "The year is 2047. The cybernetic revolution is full force. Cyborgs walk the street, and while some still give them trouble, the majority simply regard it as everyday life. Man and machine have conjoined inseparably, and even as transcendence nears us, The Space Pirate has still not seen an update.",
    "That one marine spinning forever is both the solution to our energy troubles, and the reason the demons invaded. It's canon now.",
    "\"All you had to do was not punch an astronaut.\"\n\n\"Sometimes it's hard not to punch an astronaut...\"",
    "Soylent pink is made of demons! \caDEMONS!",
    "Do not pet the cacodemon.",
    "The UAC should build a wall to keep the demons out!\nAnd then make Hell pay for it!",
    "Insert coin to continue.",
    "Welcome to die!",
    "Those demon bastards are gonna pay for screwing up my vacation.",
    "Just because you can't cram four shells into a double-barreled shotgun and have it actually work doesn't mean I won't try anyway.",
    "ayy lmao",
    "Stay awhile and listen!",
    "Greetings, mortal. Are you ready to die?",
    "Eat the path. Literally eat this dirt path. Here's some ketchup and a knife. Get to it.",
    "It's not workplace violence if you don't work there.",
    "So where's the revenants with jetpacks? I was promised revenants with jetpacks.",
    "\cd<\casystem error \cf0xfded\cd>\c-",
    "Welcome to the world of a minute from now!",
    "What's that? I can't hear you over this minigun!",
    "The leg bone is connected to the cash bone!",
    "You know what's the worst? Maps that texture hurtfloors inconsistently. Why does this slime hurt and this slime not? Come on!",
    "Samsara? What a piece of shit.",
    "omg this mod rips off everything so much",
    "On one hand, Dakkaguy probably shouldn't have a weapon for pretty much every situation under the sun.\n\nOn the other hand, nah.",
    "Why are you letting some dumb text on the title screen of an unbalanced weapon mod distract you? Go shoot some demons already!",
    "\caWIZARDS!\c- NO SENSE OF RIGHT OR WRONG!",
    "whoops you fucked up and now you're dead + stupid\n\n\nidiot",
    "Sweet christmas! Big-mouthed floating thingies! It's always something!",
    "Once we figure out how to make sustainable, stable nuclear fusion reactions, how long until someone uses a fusion reactor to cook their pizza bagels? My guess is \"ten minutes\".",
    "Man, it's actually pretty difficult to think of new messages for this. Oh wait, that's a message right there! How convenient!",
    "You'd think this was a title map for some adventure game or something! But nope, it's a weapon mod. Damn.",
    "Guns don't kill people. Lag kills people.",
    "I love the power glove. It's so bad.",
    "Y'know, in all likelihood, you probably couldn't have prevented this.",
    "To rocket jump, fire a rocket and jump.",
    "Is anyone reading this messages? Anyone? Get me out of here! I need to use the bathroom!",
    "Alright, chums, let's do this.",
    "Whenever you're feeling down in the dumps, remember this: Magneto was defeated by a fake wooden gun. Would you be defeated by a fake wooden gun?\n\nIf the answer is 'yes', make sure you aren't secretly Magneto.",
    "Why aren't you lifting \cgRIGHT NOW?\c-",
    "Mom, get off the phone! I'm downloading something!",
    "\cgSWORN TO AVENGE\n\cgCONDEMN TO HELL\n\cgTEMPT NOT THE BLADE\n\crALL FEAR THE SENTINEL",
    "Strange I was chosen, the fool divine\nTo challenge the master of riddle and rhyme\nAnother mountain for me to climb\nI must find the answer\nBefore I run out of time",
    "The stairway to heaven is currently out of order. Please use the ladder instead.",
    "You gain Brouzouf\nYour leg is broken\nYou gain Brouzouf\nYou gain Brouzouf\nYou gain Brouzouf\nMy legs are OK\nYou gain Brouzouf",
    "Are you lost? Or have you already been lost since the very beginning?",
    "The only accident I fear will be your head falling into a vat of acid with me wearing your fucking moron face as a party mask.",
    "When will rocket jumping be included at the Olympics? It's a valid sport!",
    "\caHOW TO SURVIVE A NUCLEAR APOCALYPSE:\nStep 1 - Don't get hit.\nStep 2 - don't get blown up.\nStep 3 - make sure to get plenty of water.",
    "Oh, right. The murders.",
    "The sign lied! This ride isn't wild at all! I want off!",
    "It don't mean a thing if it ain't got that SSG.",
    "Do a flip!",
    "Stop! Or I'll say stop again!",
    "Somebody stop the damn match! Enough's enough!",
    "Crush your enemies. Drive them before you. Hear the lamentations of their women. That is what's best in life.",
    "Sometimes, it's not about the destination or the journey. Sometimes it's just about killing things. Those are the better times.",
    "I'm sorry, this line has been disconnected.",
    "I just called to say... I love you.",
    "Sometimes things get a little ugly. Sometimes things get real ugly. Sometimes things just don't work out at all like how you'd expect them to.\n\nSo anyway, officer, about the dead guy...",
    "Maybe... maybe I'm the chump.\n\n\n\n\n... nah.",
};


#define DUMBHEADERCOUNT 11

int DumbHeaders[DUMBHEADERCOUNT] =
{
    "TOP SECRET:",
    "FWD: FWD: FWD: RE: RE: RE: FWD: LOL!!!!",
    "Message of the Second:",
    "Words of the Wiseass:",
    "Dakka sez:",
    "The Magic 8-Ball sez:",
    "Message for you:",
    "?????????",
    "(play some dakka already)",
    "On another note:",
    "Breaking news!",
};

int LastDumbTip = -1;

script "titlemap_dumbtips" (void)
{
    int dumbIndex;
    
    if (LastDumbTip == -1)
    {
        dumbIndex = random(0, DUMBTIPCOUNT - 1);
    }
    else
    {
        dumbIndex = random(0, DUMBTIPCOUNT - 2);
        if (dumbIndex >= LastDumbTip) { dumbIndex += 1; }
    }
    
    LastDumbTip = dumbIndex;
    
    int dumbMessage = DumbTips[dumbIndex];
    int dumbLength  = StrLen(cleanString(dumbMessage));
    
    int dumbDelay    = 105 + FixedMul(dumbLength, 1.5);
    int dumbDuration = max(0, (dumbDelay * 1.0) / 35);
    
    int dumbColor = "\c[White]";
    
    int dumbReplaced = strsub(dumbMessage, "\c-", dumbColor);
    
    int dumbHeader = DumbHeaders[random(0, DUMBHEADERCOUNT-1)];
    
    SetHudSize(320, 200, true);
    SetFont("ARCFONT");
    
    HudMessage(s:dumbHeader;   HUDMSG_FADEINOUT | HUDMSG_COLORSTRING, 51, "Gold",  160.4, 70.1, dumbDuration, 1.0, 1.0);
    HudMessage(s:dumbReplaced; HUDMSG_FADEINOUT | HUDMSG_COLORSTRING, 52, "White", 160.4, 85.1, dumbDuration, 1.0, 1.0);
    SetResultValue(dumbDelay);
}

// I totally did not copypaste this.
int LastGameTip = -1;

script "titlemap_gametips" (void)
{
    int dumbIndex;
    
    if (LastGameTip == -1)
    {
        dumbIndex = random(0, GAMETIPCOUNT - 1);
    }
    else
    {
        dumbIndex = random(0, GAMETIPCOUNT - 2);
        if (dumbIndex >= LastGameTip) { dumbIndex += 1; }
    }
    
    LastGameTip = dumbIndex;
    
    int dumbMessage = GameTips[dumbIndex];
    int dumbLength  = StrLen(cleanString(dumbMessage));
    
    int dumbDelay    = 105 + FixedMul(dumbLength, 1.5);
    int dumbDuration = max(0, (dumbDelay * 1.0) / 35);
    
    int dumbColor = "\c[White]";
    
    int dumbReplaced = strsub(dumbMessage, "\c-", dumbColor);
    
    int dumbHeader = GameHeaders[random(0, GAMEHEADERCOUNT-1)];
    
    SetHudSize(320, 200, true);
    SetFont("ARCFONT");
    
    HudMessage(s:dumbHeader;   HUDMSG_FADEINOUT | HUDMSG_COLORSTRING, 51, "Green", 160.4, 70.1, dumbDuration, 1.0, 1.0);
    HudMessage(s:dumbReplaced; HUDMSG_FADEINOUT | HUDMSG_COLORSTRING, 52, "White", 160.4, 85.1, dumbDuration, 1.0, 1.0);
    SetResultValue(dumbDelay);
}