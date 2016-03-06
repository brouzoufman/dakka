#include "zcommon.acs"
#library "dakka"

#include "commonFuncs.h"




// Constant definitions that don't fit anywhere else.
#include "dakka_defs.h"

// Script numbers and nothing else.
#include "dakka_defs_scriptnums.h"

// Monster definitions. Mainly used for calculating the score needed to get
//  a full heal.
#include "dakka_defs_monsters.h"

// Messages for dakka_cl_moremessages.
#include "dakka_defs_moremessages.h"




// Pickup system.
#include "pickup/pickup.h"

// Score system.
#include "score/score.h"

// Arc system, used for the Channeler.
#include "arc/arc.h"


// Class weapons. I want to keep this separate from the pickup system itself,
//  since the pickup system doesn't actually need to know about this.
#include "dakka_defs_classweapons.h"


////////
// vv STUFF FOR DAKKA_SPAWN

// Temporary items. These are items that are given and taken every tic by the
//  spawn script (dakka_enter.h) and used to signal shit to DECORATE. There may,
//  however, be a one tic delay between when a condition related to a temporary
//  item changes and when you actually get the item, due to the nature of
//  scripts running in no particular order. So don't use this for stuff that
//  needs to be communicated instantly.
#include "dakka_tempitems.h"

// Used in dakka_enter.h. Stuff that runs once, when the player spawns for the
//  first time. Not sure how I'll handle competitive gamemodes just yet.
#include "dakka_levelstart.h"

// Handle IDFA and IDKFA here.
#include "dakka_idfa.h"

// Scrap processing. For the scrapper.
#include "dakka_scrap.h"

// Handle the CVars dakka_shotgun2ssg and dakka_chaingun2minigun.
#include "dakka_gunstoguns.h"

// Make sure we don't have guns belonging to other classes.
#include "dakka_translateguns.h"

// ^^ STUFF FOR DAKKA_ENTER
////////


// Tracers, for all sorts of things.
#include "dakka_tracers.h"

// Lightning tracer.
#include "dakka_lightning.h"

// Rotate sound slots so weapon firing sounds can overlap with each other.
#include "dakka_rotatesound.h"

// Auto-reload the SSG when it's in your pants. Also scripts called by the SSG,
//  to handle the triggers and whatnot
#include "dakka_ssg.h"


// If you don't have flamer fuel, throw in WRF_NOSECONDARY for the minigun's spindown.
#include "dakka_minigun.h"


// Rocket launcher alt-fire junk.
#include "dakka_rocketlauncher.h"


// Stuff for the Channeler that isn't handled by the arc code proper.
#include "dakka_channeler.h"


// BFG BEAM SON
#include "dakka_bfg.h"


// Gaussian distribution script, for spread that looks circular rather than a
//  rectangle.
#include "dakka_gaussian.h"


// Clientside recoil script. Does anyone actually use this?
#include "dakka_recoil.h"


// Clientside DECORATE slave script. There was a serverside one, but it got
//  converted to named scripts. Same will happen to this one, eventually.
#include "dakka_decorate_client.h"


// Each of these is for their respecting ACS script type.
#include "dakka_open.h"

// This also has the RESPAWN script.
#include "dakka_enter.h"
