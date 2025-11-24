#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "recompconfig.h"

RECOMP_IMPORT("ProxyMM_ActorListIndex", s32 GetActorListIndex(Actor* actor));

RECOMP_CALLBACK("*", recomp_after_actor_init)
void Path_To_Goron_Village_AfterActorInit(PlayState* play, Actor* actor) {
    s32 actorListIndex = GetActorListIndex(actor);

    /*
        0 = All
        1 = Overworld
        2 = Temples
    */

    if (play->sceneId != SCENE_17SETUGEN || play->sceneId != SCENE_17SETUGEN2 || recomp_get_config_u32("enemy_removal") == 2)
        return;

    s32 id = actor->id;

    /*
        ACTOR_EN_TITE = Tektite
        ACTOR_EN_WF = Wolfos
    */

    if (id == ACTOR_EN_TITE || id == ACTOR_EN_WF) {
        Actor_Kill(actor);
    }
}