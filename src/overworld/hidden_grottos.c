#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "recompconfig.h"

//#define CUR_ROOM(play) ((play)->roomCtx.curRoom.num)

RECOMP_IMPORT("ProxyMM_ActorListIndex", s32 GetActorListIndex(Actor* actor));

RECOMP_CALLBACK("*", recomp_after_actor_init)
void Hidden_Grottos_AfterActorInit(PlayState* play, Actor* actor) {
    s32 actorListIndex = GetActorListIndex(actor);

    if(gSaveContext.gameMode != GAMEMODE_NORMAL)
        return;

    /*
        0 = All
        1 = Overworld
        2 = Temples
    */

    if (play->sceneId != SCENE_KAKUSIANA || recomp_get_config_u32("enemy_removal") == 2)
        return;

    s32 id = actor->id;

    /*
        ACTOR_EN_PEEHAT = Peahat
        ACTOR_EN_DEKUBABA = Deku Baba
        ACTOR_EN_DODONGO = Dodongo
        ACTOR_EN_KAREBABA = Wilted Deku Baba
    */

    if (id == ACTOR_EN_PEEHAT || id == ACTOR_EN_DEKUBABA || id == ACTOR_EN_DODONGO || id == ACTOR_EN_KAREBABA) {
        Actor_Kill(actor);
    }
}