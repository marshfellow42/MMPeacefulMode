#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "recompconfig.h"

RECOMP_IMPORT("ProxyMM_ActorListIndex", s32 GetActorListIndex(Actor* actor));

RECOMP_CALLBACK("*", recomp_after_actor_init)
void Odolwa_Lair_AfterActorInit(PlayState* play, Actor* actor) {
    s32 actorListIndex = GetActorListIndex(actor);

    if(gSaveContext.gameMode != GAMEMODE_NORMAL)
        return;

    /*
        0 = All
        1 = Overworld
        2 = Temples
    */

    if (play->sceneId != SCENE_MITURIN_BS || recomp_get_config_u32("kill_bosses") == 1)
        return;

    /*
        ACTOR_BOSS_01 = Odolwa
    */

    switch (actor->id) {
        case ACTOR_BOSS_01:
            Actor_Kill(actor);

            Actor_Spawn(&play->actorCtx, play, ACTOR_ITEM_B_HEART, 250.0f, 0.0f, 350.0f, 0, 0, 0, 0x0000);
            Actor_Spawn(&play->actorCtx, play, ACTOR_DOOR_WARP1, 350.0f, 0.0f, 350.0f, 0, 0, 0, 0x0001);

            break;
    }
}