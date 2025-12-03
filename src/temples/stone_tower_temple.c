#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "recompconfig.h"
#include "overlays/actors/ovl_Door_Shutter/z_door_shutter.h"
#include "overlays/actors/ovl_En_Box/z_en_box.h"

RECOMP_IMPORT("ProxyMM_ActorListIndex", s32 GetActorListIndex(Actor* actor));

RECOMP_CALLBACK("*", recomp_after_actor_init)
void Stone_Tower_Temple_AfterActorInit(PlayState* play, Actor* actor) {
    s32 actorListIndex = GetActorListIndex(actor);

    if(gSaveContext.gameMode != GAMEMODE_NORMAL)
        return;

    /*
        0 = All
        1 = Overworld
        2 = Temples
    */

    if (play->sceneId != SCENE_INISIE_N || recomp_get_config_u32("enemy_removal") == 1)
        return;

    /*
        ACTOR_EN_GRASSHOPPER = Dragonfly
        ACTOR_EN_RAT = Real Bombchu
        ACTOR_EN_EGOL = Eyegore
        ACTOR_EN_VM = Beamos
        ACTOR_EN_WDHAND = Dexihand
        ACTOR_EN_CROW = Guay
        ACTOR_BOSS_05 = Bio Deku Baba
        ACTOR_EN_PR2 = Skullfish
        ACTOR_EN_AM = Armos
        ACTOR_EN_MKK = Boe (Black or White)
        ACTOR_EN_BAGUO = Nejiron
        ACTOR_EN_PP = Hiploop
        ACTOR_EN_JSO2 = Garo Master
    */

    switch (play->roomCtx.curRoom.num) {
        case 0:
            switch (actor->id) {
                case ACTOR_EN_GRASSHOPPER:
                case ACTOR_EN_RAT:
                    Actor_Kill(actor);
                    break;
            }
            break;

        case 1:
            switch (actor->id) {
                case ACTOR_EN_EGOL:
                case ACTOR_EN_VM:
                case ACTOR_EN_WDHAND:
                    Actor_Kill(actor);
                    break;
            }
            break;

        case 2:
            switch (actor->id) {
                case ACTOR_EN_GRASSHOPPER:
                case ACTOR_EN_RAT:
                case ACTOR_EN_CROW:
                    Actor_Kill(actor);
                    break;
            }
            break;

        case 3:
            switch (actor->id) {
                case ACTOR_BOSS_05:
                case ACTOR_EN_PR2:
                case ACTOR_EN_RAT:
                    Actor_Kill(actor);
                    break;
            }
            break;

        case 4:
            switch (actor->id) {
                case ACTOR_EN_AM:
                    Actor_Kill(actor);
                    break;
            }
            break;

        case 7:
            switch (actor->id) {
                case ACTOR_EN_MKK:
                case ACTOR_EN_BAGUO:
                    Actor_Kill(actor);
                    break;
            }
            break;

        case 8:
            switch (actor->id) {
                case ACTOR_EN_PP:
                    Actor_Kill(actor);
                    break;
            }
            break;

        case 10:
            switch (actor->id) {
                case ACTOR_EN_JSO2:
                    Actor_Kill(actor);
                    break;
            }
            break;

    }
}

RECOMP_HOOK("DoorShutter_SetupDoor")
void Stone_Tower_Temple_DoorShutter_UnlockAllDoors(DoorShutter* this, PlayState* play) {
    if(gSaveContext.gameMode != GAMEMODE_NORMAL)
        return;

    if (play->sceneId != SCENE_INISIE_N || recomp_get_config_u32("enemy_removal") == 1)
        return;

    Flags_SetClear(play, this->slidingDoor.dyna.actor.room);
    Flags_SetSwitch(play, DOORSHUTTER_GET_SWITCH_FLAG(&this->slidingDoor.dyna.actor));
}

RECOMP_HOOK("EnBox_Init")
void Stone_Tower_Temple_ForceChestRoomClear(EnBox* this, PlayState* play) {
    if (gSaveContext.gameMode != GAMEMODE_NORMAL)
        return;

    if (play->sceneId != SCENE_INISIE_N || recomp_get_config_u32("enemy_removal") == 1)
        return;

    Flags_SetClear(play, this->dyna.actor.room);
}