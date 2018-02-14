![DAKKA](/README_logo.png "necessary")

**For Zandronum and GZDoom**

```text
IT IS 2162. THE LAST HUMAN OUTPOST HAS FALLEN TO THE MINIONS OF HELL. EVERYTHING
IS LOST, AND THE REMNANTS OF HUMANITY FLEE TO THE DEEPEST REACHES OF SPACE, TO
HIDE. BUT EVEN NOW, THE FIGHT IS NOT OVER.

YOU WERE A MARINE ON THE "USS LIBERTY". AS YOUR SHIP SPED AWAY FROM THE BROKEN
REMAINS OF EARTH, A GREAT HATRED WAS BUILT IN YOUR HEART, STRONGER THAN ANY
HATRED BEFORE. WITH THE HELP OF SCIENTISTS ON BOARD, YOU TRAINED YOUR BODY AND
MIND TO BECOME THE MOST POWERFUL SOLDIER HUMANITY HAS EVER HAD.

YEARS LATER, YOUR CREW RETURNS TO EARTH AND LOOKS UPON THE TWISTED REMAINS OF
HUMANITY. YOU DON'T KNOW WHAT'S IN STORE FOR YOU ON THE SURFACE, BUT THAT WON'T
STOP YOU. YOU TELEPORT DOWN AND DRAW YOUR PISTOLS.

TIME FOR SOME DAKKA.
```

It's a mod with guns. The guns make everything easy - not Russian Overkill levels
of easy, but still pretty damn easy. Eventually, I'll change up the monsters to
fix this. Today's not that day.

Any version at and before 0.06-alpha6-2 were made in the days of Zandronum 1.3.
They might use an old, deprecated method to set console variables, so be wary.
Zandronum 3 should run them perfectly well.

Early OpenAL implementations in GZDoom will play stereo sounds incorrectly - if
the pistols and super shotgun sound quiet and muffled compared to the impaler,
that's the bug. Update to the latest GZDoom if this is happening.

**DOWNLOAD:** http://jinotra.in/downloads/mods/doom/dakka/



## HOW TO GET A GIT BUILD

**[Visual instructions](http://jinotra.in/static/downloads/dakkaVids/how2dakkaGit.webm)**

Above the latest-commit bar, on the very right, there's a download icon.

Click that, choose ".ZIP", then unzip the ZIP file into its own directory.

Go into the pk3/ directory, select everything in there, and zip it all up.
Change the extension of the new ZIP file to ".pk3", and you should be good to go.

If, in the ZIP you created, everything's still in the "pk3/" folder, you zipped
the folder, not its contents. Don't do that.



## WHAT'S CHANGED SINCE 0.06?

The `CHANGELOG.txt` file will tell you in greater detail what's changed, but the
most important things:

- Dakkaguy's limp-wrist punching days are over. Instead, you can pummel your foes
    with an utterly ridiculous barrage of jabs, or cave their face in with a hook
    to the face that'd leave anyone reeling in pain, if not splattered all over the
    walls. Or give them a one-two-**THREE** to bust the skulls of both the poor sap
    in front of your fist, and all his buddies next to him.
    
- The pistols have gotten a complete overhaul! No longer the weird, odd looking
    Berettas you've been looking at since 1994, but instead sleek, sexy chrome-
    black hand cannons that do a far better job convincing you to use them! You
    gotta reload them every now and then now, but the shots hit harder, the guns
    sound cooler, you can mash the trigger to fire faster, and overall it's just
    much more fun to use. Who knows, you might actually run out of pistol rounds
    for a change!

- The minigun's flamethrower now properly sets things on fire! Focus it on a
    demon to cleanse his sinful presence, or sweep a crowd and wipe out all those
    pesky hitscanners within it!

- The rocket launcher has been dropped and replaced with the **IMPALER.**
    Originally in the BFG slot before I decided that was stupid, it's a triple
    barreled, fully automatic deliverer of explosive death. The primary fire is
    a 300RPM torrent of missiles, while the alt-fire... well, it impales enemies
    and carries them away. Then they explode. Because why shouldn't you be able
    to weaponize the demons themselves?

- The plasma rifle and channeler have been dropped in favor of the **LANCER.**
    Taking the best of both guns and combining it into one, you have a double-barreled
    demon busting machine that anyone can appreciate. Do you want to pepper your
    enemies with plasma nails, or do you want to charge up a lightning storm to
    roast everyone in front of you? Either way, the lancer has you covered.

- The berserk pickup, now vacant due to the minigun changing spots, is now occupied
    by the **VAMPIRE SPHERE.** Every kill you make grants you health, with more
    health being granted for tougher enemies and being low on health yourself.
    Good encouragement to stay in the fight and keep killing demons, don't you think?

- Dakka no longer replaces enemies! DEHACKED patches no longer break, and if you're
    using GZDoom, you no longer need monster mod compatibility patches. Zandronum
    still needs them for the score system to work optimally, due to its lack of
    `RGF_NOSIGHT` parameter for `A_RadiusGive`. But monsters will always give you
    points when they die, in either port!

- [The HUD isn't ugly anymore!](https://imgur.com/a/VLIrg) Seriously, what was I
    *thinking* with those rounded corners and that awful alignment?



## ADD-ONS

Right now, there's three compatibility patches, and they all get used the same way.

- **Ancient Aliens (`dakka_aaliens.wad`):** This adds the gibbed marine and dead
    lost soul to the score system since Ancient Aliens replaces them with custom
    enemies, and adjusts their score values upwards to match their increased danger.

- **Scythe 2 (`dakka_scythe2.wad`):** This boosts the score values of the Nazi
    and Commander Keen actors dramatically, as they're replaced with evil marines
    and afrits respectively, and are much more dangerous than their replacements.

- **Colourful Hell (`dakka_colorfulhell.wad`):** This adds the Colourful Hell
    enemies to the score system, so that loading Dakka and Colourful Hell together
    doesn't result in every map giving you score rewards every 5000 points.

    This compatibility patch is completely unnecessary in GZDoom.

To use any of these addons, download them from the `addons/` directory (use the
"Raw" button), and load the mods in this order:

- The other maps/monsters in question
- **DAKKA**
- The compatibility patch



## Are you *ever* going to release this?

I'm trying man :(