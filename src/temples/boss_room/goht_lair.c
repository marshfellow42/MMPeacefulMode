#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "recompconfig.h"

RECOMP_IMPORT("ProxyMM_ActorListIndex", s32 GetActorListIndex(Actor* actor));

RECOMP_CALLBACK("*", recomp_after_actor_init)
void Goht_Lair_AfterActorInit(PlayState* play, Actor* actor) {
    s32 actorListIndex = GetActorListIndex(actor);

    if(gSaveContext.gameMode != GAMEMODE_NORMAL)
        return;

    /*
        0 = All
        1 = Overworld
        2 = Temples
    */

    if (play->sceneId != SCENE_HAKUGIN_BS || recomp_get_config_u32("kill_bosses") == 1)
        return;

    /*
        ACTOR_BOSS_HAKUGIN = Goht
        ACTOR_EN_HAKUROCK = Rocks Kicked Up by Goht
    */

    switch (actor->id) {
        case ACTOR_BOSS_HAKUGIN:
            Actor_Kill(actor);

            Actor_Spawn(&play->actorCtx, play, ACTOR_ITEM_B_HEART, -1100.0f, 20.0f, -1300.0f, 0, 0, 0, 0x0000);
            Actor_Spawn(&play->actorCtx, play, ACTOR_DOOR_WARP1, -1400.0f, 0.0f, -1400.0f, 0, 0, 0, 0x0001);

            break;
        case ACTOR_EN_HAKUROCK:
            Actor_Kill(actor);
            break;
    }
}