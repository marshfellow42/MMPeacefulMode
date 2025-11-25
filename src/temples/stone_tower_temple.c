#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "recompconfig.h"

RECOMP_IMPORT("ProxyMM_ActorListIndex", s32 GetActorListIndex(Actor* actor));

RECOMP_CALLBACK("*", recomp_after_actor_init)
void Stone_Tower_Temple_AfterActorInit(PlayState* play, Actor* actor) {
    s32 actorListIndex = GetActorListIndex(actor);

    if(gSaveContext.gameMode != GAMEMODE_NORMAL)
        return;

    /*
        0 = All
        1 = Overworld
        2 = Temples
    */

    if (play->sceneId != SCENE_INISIE_N || recomp_get_config_u32("enemy_removal") == 1)
        return;

    s32 id = actor->id;

    /*
        ACTOR_EN_VM = Beamos
    */

    if (id == ACTOR_EN_VM) {
        Actor_Kill(actor);
    }
}