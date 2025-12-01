#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "recompconfig.h"
//#include "z64extern.h"

RECOMP_IMPORT("ProxyMM_ActorListIndex", s32 GetActorListIndex(Actor* actor));

RECOMP_CALLBACK("*", recomp_after_actor_init)
void Ikana_Graveyard_AfterActorInit(PlayState* play, Actor* actor) {
    s32 actorListIndex = GetActorListIndex(actor);

    if(gSaveContext.gameMode != GAMEMODE_NORMAL)
        return;

    /*
        0 = All
        1 = Overworld
        2 = Temples
    */

    if (play->sceneId != SCENE_BOTI || recomp_get_config_u32("enemy_removal") == 2)
        return;

    s32 id = actor->id;

    /*
        ACTOR_EN_BAT = Bad Bat
        ACTOR_EN_RAIL_SKB = Ikana Graveyard - Circle of Stalchildren
        ACTOR_BG_FIRE_WALL = Fire Wall
    */

    if (id == ACTOR_EN_BAT || id == ACTOR_EN_SKB || id == ACTOR_BG_FIRE_WALL) {
        Actor_Kill(actor);
    }

}

/*
RECOMP_HOOK("ObjSound_Init")
void MuteFireWallSfx(Actor* this, PlayState* play) {
    ObjSound* sound = (ObjSound*)this;

    if (play->sceneId != SCENE_BOTI || recomp_get_config_u32("enemy_removal") == 2)
        return;

    s32 soundId = this->params & OBJ_SOUND_ID_MASK;

    if (soundId == 16) {
        Actor_Kill(this);
    }
}
*/