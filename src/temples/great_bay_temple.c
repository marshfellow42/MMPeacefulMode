#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "recompconfig.h"
#include "overlays/actors/ovl_Door_Shutter/z_door_shutter.h"
#include "overlays/actors/ovl_En_Box/z_en_box.h"

RECOMP_IMPORT("ProxyMM_ActorListIndex", s32 GetActorListIndex(Actor* actor));

RECOMP_CALLBACK("*", recomp_after_actor_init)
void Great_Bay_Temple_AfterActorInit(PlayState* play, Actor* actor) {
    s32 actorListIndex = GetActorListIndex(actor);

    if(gSaveContext.gameMode != GAMEMODE_NORMAL)
        return;

    /*
        0 = All
        1 = Overworld
        2 = Temples
    */

    if (play->sceneId != SCENE_SEA || recomp_get_config_u32("enemy_removal") == 1)
        return;

    s32 id = actor->id;

    /*
        ACTOR_BOSS_05 = Bio Deku Baba
        ACTOR_EN_PR2 = Skullfish
        ACTOR_EN_WDHAND = Dexihand
        ACTOR_EN_RAT = Real Bombchu
        ACTOR_EN_SB = Shellblade
        ACTOR_EN_TITE = Tektite
        ACTOR_EN_SLIME = Chuchu
        ACTOR_EN_ST = Skulltula
    */


    switch (play->roomCtx.curRoom.num) {
        case 1:
            switch (actor->id) {
                case ACTOR_EN_PR2:
                case ACTOR_EN_WDHAND:
                    Actor_Kill(actor);
                    break;
            }
            break;

        case 2:
            switch (actor->id) {
                case ACTOR_EN_RAT:
                    Actor_Kill(actor);
                    break;
            }
            break;

        case 3:
            switch (actor->id) {
                case ACTOR_BOSS_05:
                    Actor_Kill(actor);
                    break;
            }
            break;

        case 4:
            switch (actor->id) {
                case ACTOR_EN_WDHAND:
                case ACTOR_EN_RAT:
                case ACTOR_BOSS_05:
                    Actor_Kill(actor);
                    break;
            }
            break;

        case 6:
            switch (actor->id) {
                case ACTOR_EN_RAT:
                case ACTOR_EN_PR2:
                case ACTOR_EN_SB:
                    Actor_Kill(actor);
                    break;
            }
            break;

        case 8:
            switch (actor->id) {
                case ACTOR_EN_ST:
                    Actor_Kill(actor);
                    break;
            }

            switch (actorListIndex) {
                case 6: {
                    Vec3f pos = actor->world.pos;
                    Vec3s rot = actor->world.rot;
                    s16 params = 0x6400;

                    Actor_Kill(actor);
                    Actor_Spawn(&play->actorCtx, play, ACTOR_EN_ELFORG, pos.x, pos.y, pos.z, rot.x, rot.y, rot.z, params);

                    return;
                }
            }
            break;

        case 10:
            switch (actor->id) {
                case ACTOR_EN_RAT:
                case ACTOR_EN_SLIME:
                    Actor_Kill(actor);
                    break;
            }
            break;

        case 12:
            switch (actor->id) {
                case ACTOR_EN_TITE:
                    Actor_Kill(actor);
                    break;
            }
            break;
    }
}

RECOMP_HOOK("DoorShutter_SetupDoor")
void Great_Bay_Temple_DoorShutter_UnlockAllDoors(DoorShutter* this, PlayState* play) {
    if(gSaveContext.gameMode != GAMEMODE_NORMAL)
        return;

    if (play->sceneId != SCENE_SEA || recomp_get_config_u32("enemy_removal") == 1)
        return;

    switch (this->slidingDoor.dyna.actor.room) {
        // Don't clear the flags for a few specific rooms that require enemies existing for progressing
        case 2:
        case 6:
        case 14:
            break;

        default:
            Flags_SetClear(play, this->slidingDoor.dyna.actor.room);
            Flags_SetSwitch(play, DOORSHUTTER_GET_SWITCH_FLAG(&this->slidingDoor.dyna.actor));
            break;
    }
}

RECOMP_HOOK("EnBox_Init")
void Great_Bay_Temple_ForceChestRoomClear(EnBox* this, PlayState* play) {
    if (gSaveContext.gameMode != GAMEMODE_NORMAL)
        return;

    if (play->sceneId != SCENE_SEA || recomp_get_config_u32("enemy_removal") == 1)
        return;

    switch (this->dyna.actor.room) {
        default:
            Flags_SetClear(play, this->dyna.actor.room);
            break;
    }
}