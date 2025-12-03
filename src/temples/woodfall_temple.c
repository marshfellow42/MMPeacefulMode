#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "recompconfig.h"
#include "overlays/actors/ovl_Door_Shutter/z_door_shutter.h"
#include "overlays/actors/ovl_En_Box/z_en_box.h"

RECOMP_IMPORT("ProxyMM_ActorListIndex", s32 GetActorListIndex(Actor* actor));

RECOMP_CALLBACK("*", recomp_after_actor_init)
void Woodfall_Temple_AfterActorInit(PlayState* play, Actor* actor) {
    s32 actorListIndex = GetActorListIndex(actor);

    if(gSaveContext.gameMode != GAMEMODE_NORMAL)
        return;

    /*
        0 = All
        1 = Overworld
        2 = Temples
    */

    if (play->sceneId != SCENE_MITURIN || recomp_get_config_u32("enemy_removal") == 1)
        return;

    /*
        ACTOR_EN_GRASSHOPPER = Dragonfly
        ACTOR_EN_MKK = Boe (Black or White)
        ACTOR_EN_DEKUBABA = Deku Baba
        ACTOR_EN_KAREBABA = Wilted Deku Baba
        ACTOR_EN_ST = Skulltula
        ACTOR_EN_KAME = Snapper
        ACTOR_EN_DINOFOS = Dinolfos
        ACTOR_BOSS_01 = Odolwa
        ACTOR_EN_TANRON1 = Moth
    */

    switch (play->roomCtx.curRoom.num) {
        case 0:
            switch (actor->id) {
                case ACTOR_EN_GRASSHOPPER:
                case ACTOR_EN_ST:
                case ACTOR_EN_TANRON1:
                    Actor_Kill(actor);
                    break;
            }
            break;

        case 1:
            switch (actor->id) {
                case ACTOR_EN_DEKUBABA:
                case ACTOR_EN_KAREBABA:
                    Actor_Kill(actor);
                    break;
            }
            break;

        case 2:
            switch (actor->id) {
                case ACTOR_EN_ST:
                case ACTOR_EN_MKK:
                    Actor_Kill(actor);
                    break;
            }
            break;

        case 3:
            switch (actor->id) {
                case ACTOR_EN_DEKUBABA:
                case ACTOR_EN_KAREBABA:
                case ACTOR_EN_TANRON1:
                    Actor_Kill(actor);
                    break;
                case ACTOR_EN_ST: {
                    Vec3f pos = actor->world.pos;
                    Vec3s rot = actor->world.rot;
                    s16 params = 0x5E02;

                    Actor_Kill(actor);
                    Actor_Spawn(&play->actorCtx, play, ACTOR_EN_ELFORG, pos.x, pos.y, pos.z, rot.x, rot.y, rot.z, params);

                    return;
                }
            }
            break;

        case 4:
            switch (actor->id) {
                case ACTOR_EN_GRASSHOPPER:
                    Actor_Kill(actor);
                    break;
            }
            break;

        case 6:
            switch (actor->id) {
                case ACTOR_EN_KAME:
                    Actor_Kill(actor);
                    break;
            }
            break;

        case 7:
            switch (actor->id) {
                case ACTOR_EN_DINOFOS:
                    Actor_Kill(actor);
                    break;
            }
            break;

        case 9:
            switch (actor->id) {
                case ACTOR_EN_MKK:
                    Actor_Kill(actor);
                    break;
            }
            break;

        case 10:
            switch (actor->id) {
                case ACTOR_EN_GRASSHOPPER:
                    Actor_Kill(actor);
                    break;
            }
            break;
    }

    /*
    if (recomp_get_config_u32("kill_bosses") == 0) {
        if (id == ACTOR_BOSS_01) {
            Actor_Kill(actor);
        }
    }
    */
}

RECOMP_HOOK("DoorShutter_SetupDoor")
void Woodfall_Temple_DoorShutter_UnlockAllDoors(DoorShutter* this, PlayState* play) {
    if(gSaveContext.gameMode != GAMEMODE_NORMAL)
        return;

    if (play->sceneId != SCENE_MITURIN || recomp_get_config_u32("enemy_removal") == 1)
        return;

    Flags_SetClear(play, this->slidingDoor.dyna.actor.room);
    Flags_SetSwitch(play, DOORSHUTTER_GET_SWITCH_FLAG(&this->slidingDoor.dyna.actor));
}

RECOMP_HOOK("EnBox_Init")
void Woodfall_Temple_ForceChestRoomClear(EnBox* this, PlayState* play) {
    if (gSaveContext.gameMode != GAMEMODE_NORMAL)
        return;

    if (play->sceneId != SCENE_MITURIN || recomp_get_config_u32("enemy_removal") == 1)
        return;

    Flags_SetClear(play, this->dyna.actor.room);
}