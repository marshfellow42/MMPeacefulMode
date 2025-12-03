#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "recompconfig.h"
#include "overlays/actors/ovl_Door_Shutter/z_door_shutter.h"
#include "overlays/actors/ovl_En_Box/z_en_box.h"

RECOMP_IMPORT("ProxyMM_ActorListIndex", s32 GetActorListIndex(Actor* actor));

RECOMP_CALLBACK("*", recomp_after_actor_init)
void Stone_Tower_Temple_Inverted_AfterActorInit(PlayState* play, Actor* actor) {
    s32 actorListIndex = GetActorListIndex(actor);

    if(gSaveContext.gameMode != GAMEMODE_NORMAL)
        return;

    /*
        0 = All
        1 = Overworld
        2 = Temples
    */

    if (play->sceneId != SCENE_INISIE_R || recomp_get_config_u32("enemy_removal") == 1)
        return;

    s32 id = actor->id;

    /*
        ACTOR_EN_VM = Beamos
        ACTOR_EN_RAT = Real Bombchu
        ACTOR_EN_CROW = Guay
        ACTOR_EN_GRASSHOPPER = Dragonfly
        ACTOR_EN_AM = Armos
        ACTOR_EN_EGOL = Eyegore
        ACTOR_EN_WDHAND = Dexihand
        ACTOR_BOSS_05 = Bio Deku Baba
        ACTOR_EN_PR2 = Skullfish
        ACTOR_EN_FAMOS = Death Armos
        ACTOR_EN_BB = Blue Bubbles
        ACTOR_EN_PP = Hiploop
        ACTOR_EN_WIZ = Wizzrobe
        ACTOR_EN_POH = Poe
        ACTOR_BOSS_02 = Twinmold
        ACTOR_EN_MKK = Boe (Black or White)
        ACTOR_EN_BAGUO = Nejiron
        ACTOR_EN_DEATH = Gomess
        ACTOR_EN_MINIDEATH = Bats Surrounding Gomess
        ACTOR_EN_TUBO_TRAP = Pot - Trap
    */

    switch (play->roomCtx.curRoom.num) {
        case 0:
            switch (actor->id) {
                case ACTOR_EN_FAMOS:
                    Actor_Kill(actor);
                    break;
            }
            break;

        case 1:
            switch (actor->id) {
                case ACTOR_EN_WDHAND:
                case ACTOR_EN_EGOL:
                    Actor_Kill(actor);
                    break;
            }
            break;

        case 2:
            switch (actor->id) {
                case ACTOR_EN_POH:
                case ACTOR_EN_FAMOS:
                    Actor_Kill(actor);
                    break;
            }
            break;

        case 3:
            switch (actor->id) {
                case ACTOR_EN_BB:
                case ACTOR_EN_PP:
                    Actor_Kill(actor);
                    break;
            }
            break;

        case 4:
            switch (actor->id) {
                case ACTOR_EN_WIZ:
                    Actor_Kill(actor);
                    break;
            }
            break;

        case 8:
            switch (actor->id) {
                case ACTOR_EN_VM:
                case ACTOR_EN_TUBO_TRAP:
                    Actor_Kill(actor);
                    break;
            }
            break;

        case 11:
            switch (actor->id) {
                case ACTOR_EN_DEATH:
                case ACTOR_EN_MINIDEATH:
                    Actor_Kill(actor);
                    break;
            }
            break;
    }

    /*
    if (recomp_get_config_u32("kill_bosses") == 0) {
        if (id == ACTOR_BOSS_02) {
            Actor_Kill(actor);
        }
    }
    */
}

RECOMP_HOOK("DoorShutter_SetupDoor")
void Stone_Tower_Temple_Inverted_DoorShutter_UnlockAllDoors(DoorShutter* this, PlayState* play) {
    if(gSaveContext.gameMode != GAMEMODE_NORMAL)
        return;

    if (play->sceneId != SCENE_INISIE_R || recomp_get_config_u32("enemy_removal") == 1)
        return;

    Flags_SetClear(play, this->slidingDoor.dyna.actor.room);
    Flags_SetSwitch(play, DOORSHUTTER_GET_SWITCH_FLAG(&this->slidingDoor.dyna.actor));
}

RECOMP_HOOK("EnBox_Init")
void Stone_Tower_Temple_Inverted_ForceChestRoomClear(EnBox* this, PlayState* play) {
    if (gSaveContext.gameMode != GAMEMODE_NORMAL)
        return;

    if (play->sceneId != SCENE_INISIE_R || recomp_get_config_u32("enemy_removal") == 1)
        return;

    Flags_SetClear(play, this->dyna.actor.room);
}