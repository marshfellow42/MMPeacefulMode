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

    switch (play->roomCtx.curRoom.num) {
        case 1:
            switch (actor->id) {
                case ACTOR_EN_FZ:
                case ACTOR_EN_FIREFLY:
                case ACTOR_EN_KAREBABA:
                    Actor_Kill(actor);
                    break;
            }

        case 3:
            switch (actor->id) {
                case ACTOR_EN_FIREFLY:
                case ACTOR_EN_HONOTRAP:
                    Actor_Kill(actor);
                    break;
            }

        case 4:
            switch (actor->id) {
                case ACTOR_EN_WDHAND:
                case ACTOR_EN_HONOTRAP:
                    Actor_Kill(actor);
                    break;
            }

        case 6:
            switch (actor->id) {
                case ACTOR_EN_DEKUBABA:
                case ACTOR_EN_KAREBABA:
                    Actor_Kill(actor);
                    break;
            }

        case 7:
            switch (actor->id) {
                case ACTOR_EN_ST:
                    Actor_Kill(actor);
                    break;
            }

        case 8:
            switch (actor->id) {
                case ACTOR_EN_ST:
                    Actor_Kill(actor);
                    break;
            }

        case 10:
            switch (actor->id) {
                case ACTOR_EN_FIREFLY:
                    Actor_Kill(actor);
                    break;
            }

        case 12:
            switch (actor->id) {
                case ACTOR_EN_BIGPO:
                    Actor_Kill(actor);
                    break;
            }

        default:
            switch (actor->id) {
                case ACTOR_EN_WALLMAS:
                case ACTOR_EN_TALK_GIBUD:
                    Actor_Kill(actor);
                    break;
            }
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