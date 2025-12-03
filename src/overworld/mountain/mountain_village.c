#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "recompconfig.h"

RECOMP_IMPORT("ProxyMM_ActorListIndex", s32 GetActorListIndex(Actor* actor));

RECOMP_CALLBACK("*", recomp_after_actor_init)
void Mountain_Village_AfterActorInit(PlayState* play, Actor* actor) {
    s32 actorListIndex = GetActorListIndex(actor);

    if(gSaveContext.gameMode != GAMEMODE_NORMAL)
        return;

    /*
        0 = All
        1 = Overworld
        2 = Temples
    */

    if ((play->sceneId != SCENE_10YUKIYAMANOMURA && play->sceneId != SCENE_10YUKIYAMANOMURA2) || recomp_get_config_u32("enemy_removal") == 2)
        return;

    /*
        ACTOR_EN_CROW = Guay
        ACTOR_EN_BEE = Giant Bee
    */

    switch (actor->id) {
        case ACTOR_EN_CROW:
        case ACTOR_EN_BEE:
            Actor_Kill(actor);
            break;
    }
}