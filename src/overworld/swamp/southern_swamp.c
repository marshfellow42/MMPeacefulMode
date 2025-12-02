#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "recompconfig.h"

RECOMP_IMPORT("ProxyMM_ActorListIndex", s32 GetActorListIndex(Actor* actor));

RECOMP_CALLBACK("*", recomp_after_actor_init)
void Southern_Swamp_AfterActorInit(PlayState* play, Actor* actor) {
    s32 actorListIndex = GetActorListIndex(actor);

    if(gSaveContext.gameMode != GAMEMODE_NORMAL)
        return;

    /*
        0 = All
        1 = Overworld
        2 = Temples
    */

    if (play->sceneId != SCENE_20SICHITAI || recomp_get_config_u32("enemy_removal") == 2)
        return;

    /*
        ACTOR_EN_BIGOKUTA = Big Octorock
        ACTOR_EN_DEKUBABA = Deku Baba
        ACTOR_EN_KAREBABA = Wilted Deku Baba
        ACTOR_EN_GRASSHOPPER = Dragonfly
    */

    switch (actor->id) {
        case ACTOR_EN_BIGOKUTA:
        case ACTOR_EN_DEKUBABA:
        case ACTOR_EN_KAREBABA:
        case ACTOR_EN_GRASSHOPPER:
            Actor_Kill(actor);
            break;
    }
}