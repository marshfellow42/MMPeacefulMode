#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "recompconfig.h"

RECOMP_IMPORT("ProxyMM_ActorListIndex", s32 GetActorListIndex(Actor* actor));

RECOMP_CALLBACK("*", recomp_after_actor_init)
void Road_To_Southern_Swamp_AfterActorInit(PlayState* play, Actor* actor) {
    s32 actorListIndex = GetActorListIndex(actor);

    /*
        0 = All
        1 = Overworld
        2 = Temples
    */

    if (play->sceneId != SCENE_24KEMONOMITI || recomp_get_config_u32("enemy_removal") == 2)
        return;

    s32 id = actor->id;

    /*
        0x014A = Chuchu
        0x015B = Bad Bat
        0x0033 = Deku Baba
        0x00EC = Wolfos
    */

    if (id == 0x014A || id == 0x015B || id == 0x0033 || id == 0x00EC) {
        Actor_Kill(actor);
    }
}