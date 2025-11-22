#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "recompconfig.h"

RECOMP_IMPORT("ProxyMM_ActorListIndex", s32 GetActorListIndex(Actor* actor));

RECOMP_CALLBACK("*", recomp_after_actor_init)
void Southern_Swamp_AfterActorInit(PlayState* play, Actor* actor) {
    s32 actorListIndex = GetActorListIndex(actor);

    /*
        0 = All
        1 = Overworld
        2 = Temples
    */

    if (play->sceneId != SCENE_20SICHITAI || recomp_get_config_u32("enemy_removal") == 2)
        return;

    s32 id = actor->id;

    /*
        0x01A8 = Big Octorock
        0x0033 = Deku Baba
        0x0066 = Wilted Deku Baba
    */

    if (id == 0x01A8 || id == 0x0033 || id == 0x0066) {
        Actor_Kill(actor);
    }
}