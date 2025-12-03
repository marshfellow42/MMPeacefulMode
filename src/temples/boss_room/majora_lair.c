#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "recompconfig.h"

RECOMP_IMPORT("ProxyMM_ActorListIndex", s32 GetActorListIndex(Actor* actor));

RECOMP_CALLBACK("*", recomp_after_actor_init)
void Majora_Lair_AfterActorInit(PlayState* play, Actor* actor) {
    s32 actorListIndex = GetActorListIndex(actor);

    if(gSaveContext.gameMode != GAMEMODE_NORMAL)
        return;

    /*
        0 = All
        1 = Overworld
        2 = Temples
    */

    if (play->sceneId != SCENE_LAST_BS || recomp_get_config_u32("kill_bosses") == 1)
        return;

    /*
        ACTOR_BOSS_07 = Majora
    */

    switch (actor->id) {
        case ACTOR_BOSS_07:
            Actor_Kill(actor);

            play->nextEntrance = 0x5400;
            gSaveContext.nextCutsceneIndex = 0xFFF7;
            play->transitionTrigger = 0x14;
            break;
    }
}