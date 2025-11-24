#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "recompconfig.h"

RECOMP_IMPORT("ProxyMM_ActorListIndex", s32 GetActorListIndex(Actor* actor));

RECOMP_CALLBACK("*", recomp_after_actor_init)
void Ikana_Graveyard_AfterActorInit(PlayState* play, Actor* actor) {
    s32 actorListIndex = GetActorListIndex(actor);

    /*
        0 = All
        1 = Overworld
        2 = Temples
    */

    if (play->sceneId != SCENE_BOTI || recomp_get_config_u32("enemy_removal") == 2)
        return;

    s32 id = actor->id;

    /*
        ACTOR_EN_BAT = Bad Bat
        ACTOR_BG_BOTIHASIRA = Captain Keeta Race - Gatepost
        ACTOR_EN_RAIL_SKB = Ikana Graveyard - Circle of Stalchildren
        ACTOR_EN_SKB = Stalchild
    */

    if (id == ACTOR_EN_BAT || id == ACTOR_BG_BOTIHASIRA || id == ACTOR_EN_RAIL_SKB || id == ACTOR_EN_SKB) {
        Actor_Kill(actor);
    }
}