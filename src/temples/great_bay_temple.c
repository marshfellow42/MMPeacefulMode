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
    */


    switch (play->roomCtx.curRoom.num) {
        case 8:
            if (actorListIndex == 7) {
                // Kill the Skulltula and replace his actor with the Stray Fairy
                Vec3f pos = actor->world.pos;
                Vec3s rot = actor->world.rot;
                s16 params = 0x6002;

                Actor_Kill(actor);
                Actor_Spawn(&play->actorCtx, play, ACTOR_EN_ELFORG, pos.x, pos.y, pos.z, rot.x, rot.y, rot.z, params);

                return;
            }

        case 10:
            switch (actor->id) {
                case ACTOR_EN_RAT:
                case ACTOR_EN_SLIME:
                    Actor_Kill(actor);
                    break;
            }
            break;

        default:
            if (id == ACTOR_BOSS_05 || id == ACTOR_EN_PR2 || id == ACTOR_EN_WDHAND || id == ACTOR_EN_RAT || id == ACTOR_EN_SB || id == ACTOR_EN_TITE || id == ACTOR_EN_SLIME) {
                Actor_Kill(actor);
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

    Flags_SetClear(play, this->slidingDoor.dyna.actor.room);
    Flags_SetSwitch(play, DOORSHUTTER_GET_SWITCH_FLAG(&this->slidingDoor.dyna.actor));
}

RECOMP_HOOK("EnBox_Init")
void Great_Bay_Temple_ForceChestRoomClear(EnBox* this, PlayState* play) {
    if (gSaveContext.gameMode != GAMEMODE_NORMAL)
        return;

    if (play->sceneId != SCENE_SEA || recomp_get_config_u32("enemy_removal") == 1)
        return;

    Flags_SetClear(play, this->dyna.actor.room);
}