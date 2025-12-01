#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "recompconfig.h"

RECOMP_IMPORT("ProxyMM_ActorListIndex", s32 GetActorListIndex(Actor* actor));

RECOMP_CALLBACK("*", recomp_after_actor_init)
void Road_To_Ikana_AfterActorInit(PlayState* play, Actor* actor) {
    s32 actorListIndex = GetActorListIndex(actor);

    if(gSaveContext.gameMode != GAMEMODE_NORMAL)
        return;

    /*
        0 = All
        1 = Overworld
        2 = Temples
    */

    if (play->sceneId != SCENE_IKANAMAE || recomp_get_config_u32("enemy_removal") == 2)
        return;

    s32 id = actor->id;

    /*
        ACTOR_EN_RAT = Real Bombchu
        ACTOR_EN_BB = Blue Bubbles
        ACTOR_EN_BAGUO = Nejiron
    */

    if (id == ACTOR_EN_RAT || id == ACTOR_EN_BB || id == ACTOR_EN_BAGUO) {
        Actor_Kill(actor);
    }
}