#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "recompconfig.h"

//#define CUR_ROOM(play) ((play)->roomCtx.curRoom.num)

RECOMP_IMPORT("ProxyMM_ActorListIndex", s32 GetActorListIndex(Actor* actor));

RECOMP_CALLBACK("*", recomp_after_actor_init)
void Hidden_Grottos_AfterActorInit(PlayState* play, Actor* actor) {
    s32 actorListIndex = GetActorListIndex(actor);

    /*
        0 = All
        1 = Overworld
        2 = Temples
    */

    if (play->sceneId != SCENE_KAKUSIANA || recomp_get_config_u32("enemy_removal") == 2)
        return;

    s32 id = actor->id;

    /*
        0x0014 = Peahat
        0x0033 = Deku Baba
        0x000B = Dodongo
        0x0066 = Wilted Deku Baba
    */

    if (id == 0x0014 || id == 0x0033 || id == 0x000B || id == 0x0066) {
        Actor_Kill(actor);
    }
}