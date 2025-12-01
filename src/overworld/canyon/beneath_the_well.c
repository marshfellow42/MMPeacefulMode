#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "recompconfig.h"
#include "overlays/actors/ovl_Door_Shutter/z_door_shutter.h"

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

    if (play->sceneId != SCENE_REDEAD || recomp_get_config_u32("enemy_removal") == 2)
        return;

    s32 id = actor->id;

    /*
        ACTOR_EN_TALK_GIBUD = Gibdo Requesting an Item
        ACTOR_EN_FIREFLY = Keese (Normal, Ice or Fire)
        ACTOR_EN_FZ = Freezard
        ACTOR_EN_ELFORG = Stray Fairy (somehow a stray fairy summoned here, again, why?!)
        ACTOR_EN_BIGPO = Big Poe
        ACTOR_EN_HONOTRAP = Flaming Eye Switch thingy
        ACTOR_EN_DEKUBABA = Deku Baba
        ACTOR_EN_KAREBABA = Wilted Deku Baba
        ACTOR_EN_WALLMAS = Wallmaster
        ACTOR_EN_ST = Skulltula
        ACTOR_EN_WDHAND = Dexihand
    */

    if (id == ACTOR_EN_TALK_GIBUD || id == ACTOR_EN_FIREFLY || id == ACTOR_EN_FZ || id == ACTOR_EN_ELFORG || id == ACTOR_EN_BIGPO || id == ACTOR_EN_HONOTRAP || id == ACTOR_EN_DEKUBABA || id == ACTOR_EN_KAREBABA || id == ACTOR_EN_WALLMAS || id == ACTOR_EN_ST || id == ACTOR_EN_WDHAND) {
        Actor_Kill(actor);
    }

}

RECOMP_HOOK("DoorShutter_SetupDoor")
void Beneath_The_Well_DoorShutter_UnlockAllDoors(DoorShutter* this, PlayState* play) {

    if(gSaveContext.gameMode != GAMEMODE_NORMAL)
        return;

    if (play->sceneId != SCENE_REDEAD || recomp_get_config_u32("enemy_removal") == 2)
        return;

    Flags_SetClear(play, this->slidingDoor.dyna.actor.room);
    Flags_SetSwitch(play, DOORSHUTTER_GET_SWITCH_FLAG(&this->slidingDoor.dyna.actor));
}