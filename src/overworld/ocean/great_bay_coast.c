#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "recompconfig.h"

RECOMP_IMPORT("ProxyMM_ActorListIndex", s32 GetActorListIndex(Actor* actor));

RECOMP_CALLBACK("*", recomp_after_actor_init)
void Great_Bay_Coast_AfterActorInit(PlayState* play, Actor* actor) {
    s32 actorListIndex = GetActorListIndex(actor);

    if(gSaveContext.gameMode != GAMEMODE_NORMAL)
        return;

    /*
        0 = All
        1 = Overworld
        2 = Temples
    */

    if (play->sceneId != SCENE_30GYOSON || recomp_get_config_u32("enemy_removal") == 2)
        return;

    s32 id = actor->id;

    /*
        ACTOR_EN_NEO_REEBA = Leever
        ACTOR_EN_RR = Like Like
    */

    if (id == ACTOR_EN_NEO_REEBA || id == ACTOR_EN_RR) {
        Actor_Kill(actor);
    }
}