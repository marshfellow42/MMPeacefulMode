#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "recompconfig.h"

RECOMP_IMPORT("ProxyMM_ActorListIndex", s32 GetActorListIndex(Actor* actor));

RECOMP_CALLBACK("*", recomp_after_actor_init)
void Road_To_Southern_Swamp_AfterActorInit(PlayState* play, Actor* actor) {
    s32 actorListIndex = GetActorListIndex(actor);

    if(gSaveContext.gameMode != GAMEMODE_NORMAL)
        return;

    /*
        0 = All
        1 = Overworld
        2 = Temples
    */

    if (play->sceneId != SCENE_24KEMONOMITI || recomp_get_config_u32("enemy_removal") == 2)
        return;

    /*
        ACTOR_EN_SLIME = Chuchu
        ACTOR_EN_BAT = Bad Bat
        ACTOR_EN_DEKUBABA = Deku Baba
        ACTOR_EN_WF = Wolfos
    */

    switch (actor->id) {
        case ACTOR_EN_SLIME:
        case ACTOR_EN_BAT:
        case ACTOR_EN_DEKUBABA:
        case ACTOR_EN_WF:
            Actor_Kill(actor);
            break;
    }
}