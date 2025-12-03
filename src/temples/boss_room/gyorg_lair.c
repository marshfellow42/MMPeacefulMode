#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "recompconfig.h"

RECOMP_IMPORT("ProxyMM_ActorListIndex", s32 GetActorListIndex(Actor* actor));

RECOMP_CALLBACK("*", recomp_after_actor_init)
void Gyorg_Lair_AfterActorInit(PlayState* play, Actor* actor) {
    s32 actorListIndex = GetActorListIndex(actor);

    if(gSaveContext.gameMode != GAMEMODE_NORMAL)
        return;

    /*
        0 = All
        1 = Overworld
        2 = Temples
    */

    if (play->sceneId != SCENE_SEA_BS || recomp_get_config_u32("kill_bosses") == 1)
        return;

    /*
        ACTOR_BOSS_03 = Gyorg
    */

    switch (actor->id) {
        case ACTOR_BOSS_03: {
            Actor_Kill(actor);

            Actor_Spawn(&play->actorCtx, play, ACTOR_DOOR_WARP1, 0.0f, 440.0f, 200.0f, 0, 0, 0, 0x0001);

            static bool heartPieceSpawned = false;

            if (!heartPieceSpawned) {
                Actor_Spawn(&play->actorCtx, play, ACTOR_ITEM_B_HEART, 0.0f, 460.0f, 0.0f, 0, 0, 0, 0x0000);

                heartPieceSpawned = true;
            }

            break;
        }
    }
}