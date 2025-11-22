#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "recompconfig.h"

RECOMP_IMPORT("ProxyMM_ActorListIndex", s32 GetActorListIndex(Actor* actor));

RECOMP_CALLBACK("*", recomp_after_actor_init)
void Before_Ikana_AfterActorInit(PlayState* play, Actor* actor) {
    s32 actorListIndex = GetActorListIndex(actor);

    /*
        0 = All
        1 = Overworld
        2 = Temples
    */

    if (play->sceneId != SCENE_IKANAMAE || recomp_get_config_u32("enemy_removal") == 2)
        return;

    s32 id = actor->id;

    /*
        0x016F = Real Bombchu
        0x003E = Blue Bubbles
    */

    if (id == 0x016F || id == 0x003E) {
        Actor_Kill(actor);
    }
}