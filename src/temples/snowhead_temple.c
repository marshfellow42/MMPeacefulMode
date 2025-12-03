#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "recompconfig.h"
#include "overlays/actors/ovl_Door_Shutter/z_door_shutter.h"
#include "overlays/actors/ovl_En_Box/z_en_box.h"

RECOMP_IMPORT("ProxyMM_ActorListIndex", s32 GetActorListIndex(Actor* actor));

RECOMP_CALLBACK("*", recomp_after_actor_init)
void Snowhead_Temple_AfterActorInit(PlayState* play, Actor* actor) {
    s32 actorListIndex = GetActorListIndex(actor);

    if(gSaveContext.gameMode != GAMEMODE_NORMAL)
        return;

    /*
        0 = All
        1 = Overworld
        2 = Temples
    */

    if (play->sceneId != SCENE_HAKUGIN || recomp_get_config_u32("enemy_removal") == 1)
        return;

    /*
        ACTOR_EN_WF = Wolfos
        ACTOR_EN_MKK = Boe (Black or White)
        ACTOR_EN_FZ = Freezard
        ACTOR_EN_RAT = Real Bombchu
        ACTOR_EN_FIREFLY = Keese (Normal, Ice or Fire)
        ACTOR_EN_BBFALL = Red Bubbles
        ACTOR_EN_SNOWMAN = Eeno
        ACTOR_EN_WIZ = Wizzrobe
        ACTOR_EN_TUBO_TRAP = Pot - Trap
        ACTOR_EN_DINOFOS = Dinolfos
    */

    switch (play->roomCtx.curRoom.num) {
        case 0:
            switch (actor->id) {
                case ACTOR_EN_WF:
                case ACTOR_EN_MKK:
                    Actor_Kill(actor);
                    break;
            }
            break;

        case 1:
            switch (actor->id) {
                case ACTOR_EN_WF:
                    Actor_Kill(actor);
                    break;
            }
            break;

        case 2:
            switch (actor->id) {
                case ACTOR_EN_FZ:
                    Actor_Kill(actor);
                    break;
            }
            break;

        case 3:
            switch (actor->id) {
                case ACTOR_EN_TUBO_TRAP:
                    Actor_Kill(actor);
                    break;
            }
            break;

        case 4:
            switch (actor->id) {
                case ACTOR_EN_BBFALL:
                    Actor_Kill(actor);
                    break;
            }
            break;

        case 5:
            switch (actor->id) {
                case ACTOR_EN_FZ:
                    Actor_Kill(actor);
                    break;
            }
            break;

        case 6:
            switch (actor->id) {
                case ACTOR_EN_WIZ:
                    Actor_Kill(actor);
                    break;
            }
            break;

        case 8:
            switch (actor->id) {
                case ACTOR_EN_MKK:
                    Actor_Kill(actor);
                    break;
            }
            break;

        case 9:
            switch (actor->id) {
                case ACTOR_EN_RAT:
                case ACTOR_EN_FZ:
                    Actor_Kill(actor);
                    break;
            }
            break;

        case 10:
            switch (actor->id) {
                case ACTOR_EN_SNOWMAN:
                    Actor_Kill(actor);
                    break;
            }
            break;

        case 11:
            switch (actor->id) {
                case ACTOR_EN_DINOFOS:
                    Actor_Kill(actor);
                    break;
            }

            switch (actorListIndex) {
                case 0:
                case 1: {
                    Vec3f pos = actor->world.pos;
                    Vec3s rot = actor->world.rot;
                    s16 params = 0x3000;

                    Actor_Kill(actor);
                    Actor_Spawn(&play->actorCtx, play, ACTOR_EN_ELFORG, pos.x, pos.y, pos.z, rot.x, rot.y, rot.z, params);
                    return;
                }
            }
            break;

        case 12:
            switch (actor->id) {
                case ACTOR_EN_WIZ:
                    Actor_Kill(actor);
                    break;
            }
            break;

    }
}

RECOMP_HOOK("DoorShutter_SetupDoor")
void Snowhead_Temple_DoorShutter_UnlockAllDoors(DoorShutter* this, PlayState* play) {
    if(gSaveContext.gameMode != GAMEMODE_NORMAL)
        return;

    if (play->sceneId != SCENE_HAKUGIN || recomp_get_config_u32("enemy_removal") == 1)
        return;

    Flags_SetClear(play, this->slidingDoor.dyna.actor.room);
    Flags_SetSwitch(play, DOORSHUTTER_GET_SWITCH_FLAG(&this->slidingDoor.dyna.actor));
}

RECOMP_HOOK("EnBox_Init")
void Snowhead_Temple_ForceChestRoomClear(EnBox* this, PlayState* play) {
    if (gSaveContext.gameMode != GAMEMODE_NORMAL)
        return;

    if (play->sceneId != SCENE_HAKUGIN || recomp_get_config_u32("enemy_removal") == 1)
        return;

    Flags_SetClear(play, this->dyna.actor.room);
}