#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "recompconfig.h"

RECOMP_IMPORT("ProxyMM_ActorListIndex", s32 GetActorListIndex(Actor* actor));

RECOMP_CALLBACK("*", recomp_after_actor_init)
void Snowhead_Temple_AfterActorInit(PlayState* play, Actor* actor) {
    s32 actorListIndex = GetActorListIndex(actor);

    if(gSaveContext.gameMode != GAMEMODE_NORMAL)
        return;

    /*
        0 = All
        1 = Overworld
        2 = Temples
    */

    if (play->sceneId != SCENE_HAKUGIN || recomp_get_config_u32("enemy_removal") == 1)
        return;

    s32 id = actor->id;

    /*
        ACTOR_EN_WF = Wolfos
        ACTOR_EN_MKK = Boe (Black or White)
        ACTOR_EN_FZ = Freezard
        ACTOR_EN_RAT = Real Bombchu
        ACTOR_EN_FIREFLY = Keese (Normal, Ice or Fire)
        ACTOR_EN_BBFALL = Red Bubbles
        ACTOR_EN_SNOWMAN = Eeno
    */

    if (id == ACTOR_EN_WF || id == ACTOR_EN_MKK || id == ACTOR_EN_FZ || id == ACTOR_EN_RAT || id == ACTOR_EN_FIREFLY || id == ACTOR_EN_BBFALL || id == ACTOR_EN_SNOWMAN) {
        Actor_Kill(actor);
    }
}