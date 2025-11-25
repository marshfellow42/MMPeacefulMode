#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "recompconfig.h"

RECOMP_IMPORT("ProxyMM_ActorListIndex", s32 GetActorListIndex(Actor* actor));

RECOMP_CALLBACK("*", recomp_after_actor_init)
void Ikana_Canyon_AfterActorInit(PlayState* play, Actor* actor) {
    s32 actorListIndex = GetActorListIndex(actor);

    if(gSaveContext.gameMode != GAMEMODE_NORMAL)
        return;

    /*
        0 = All
        1 = Overworld
        2 = Temples
    */

    if (play->sceneId != SCENE_IKANA || recomp_get_config_u32("enemy_removal") == 2)
        return;

    s32 id = actor->id;

    /*
        ACTOR_EN_BB = Blue Bubbles
        ACTOR_EN_RAILGIBUD = Music Box House - Patrolling Gibdos
        ACTOR_EN_OKUTA = Octorok
        ACTOR_EN_CROW = Guay
    */

    if (id == ACTOR_EN_BB || id == ACTOR_EN_RAILGIBUD || id == ACTOR_EN_OKUTA || id == ACTOR_EN_CROW) {
        Actor_Kill(actor);
    }
}