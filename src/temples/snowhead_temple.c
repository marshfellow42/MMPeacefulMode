#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "recompconfig.h"

RECOMP_IMPORT("ProxyMM_ActorListIndex", s32 GetActorListIndex(Actor* actor));

RECOMP_CALLBACK("*", recomp_after_actor_init)
void Snowhead_Temple_AfterActorInit(PlayState* play, Actor* actor) {
    s32 actorListIndex = GetActorListIndex(actor);

    /*
        0 = All
        1 = Overworld
        2 = Temples
    */

    if (play->sceneId != SCENE_HAKUGIN || recomp_get_config_u32("enemy_removal") == 1)
        return;

    s32 id = actor->id;

    /*
        0x0216 = Leever
    */

    if (id == 0x0216) {
        Actor_Kill(actor);
    }
}