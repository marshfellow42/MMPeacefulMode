#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "recompconfig.h"

RECOMP_IMPORT("ProxyMM_ActorListIndex", s32 GetActorListIndex(Actor* actor));

RECOMP_CALLBACK("*", recomp_after_actor_init)
void Beneath_The_Well_AfterActorInit(PlayState* play, Actor* actor) {
    s32 actorListIndex = GetActorListIndex(actor);

    if(gSaveContext.gameMode != GAMEMODE_NORMAL)
        return;

    /*
        0 = All
        1 = Overworld
        2 = Temples
    */

    // For now this scene will be disabled until I discover how to open doors

    if (play->sceneId == SCENE_REDEAD || recomp_get_config_u32("enemy_removal") == 2)
        return;

    s32 id = actor->id;

    /*
        ACTOR_EN_TALK_GIBUD = Gibdo Requesting an Item
        ACTOR_EN_FIREFLY = Keese (Normal, Ice or Fire)
    */

    if (id == ACTOR_EN_TALK_GIBUD || id == ACTOR_EN_FIREFLY) {
        Actor_Kill(actor);
    }

    if (id == ACTOR_DOOR_SHUTTER) {
        // Need to call this function for the door to open, but how?
        // func_808A1784(ds, play);
    }

}