#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "recompconfig.h"

RECOMP_IMPORT("ProxyMM_ActorListIndex", s32 GetActorListIndex(Actor* actor));

RECOMP_CALLBACK("*", recomp_after_actor_init)
void Milk_Road_AfterActorInit(PlayState* play, Actor* actor) {
    s32 actorListIndex = GetActorListIndex(actor);

    if(gSaveContext.gameMode != GAMEMODE_NORMAL)
        return;

    /*
        0 = All
        1 = Overworld
        2 = Temples
    */

    if (play->sceneId != SCENE_ROMANYMAE || recomp_get_config_u32("unlock_romani") == 1)
        return;

    s32 id = actor->id;

    /*
        ACTOR_OBJ_HUGEBOMBIWA = Boulder Blocking Romani Ranch
        ACTOR_EN_DAIKU2 = Milk Road - Carpenter Hacking at Boulder
    */

    if (id == ACTOR_OBJ_HUGEBOMBIWA || id == ACTOR_EN_DAIKU2) {
        Actor_Kill(actor);
    }

    // I'm gonna go with the reasoning that the Carpenter was there because of the boulder, and without a boulder in the first place, there's no reason for the Carpenter being there

}