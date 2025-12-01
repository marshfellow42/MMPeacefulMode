#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "recompconfig.h"
#include "overlays/actors/ovl_Door_Shutter/z_door_shutter.h"

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

    s32 id = actor->id;

    /*
        ACTOR_EN_GRASSHOPPER = Dragonfly
        ACTOR_EN_MKK = Boe (Black or White)
        ACTOR_EN_DEKUBABA = Deku Baba
        ACTOR_EN_KAREBABA = Wilted Deku Baba
        ACTOR_EN_ST = Skulltula
        ACTOR_EN_KAME = Snapper
        ACTOR_EN_DINOFOS = Dinolfos
        ACTOR_EN_BIGPAMET = Gekko & Snapper Miniboss - Snapper
        ACTOR_EN_PAMETFROG = Gekko & Snapper Miniboss - Gekko
        ACTOR_BOSS_01 = Odolwa
    */

    if (play->roomCtx.curRoom.num == 3 && actorListIndex == 3) {
        // Kill the Skulltula and replace his actor with the Stray Fairy
        float posX = actor->world.pos.x;
        float posY = actor->world.pos.y;
        float posZ = actor->world.pos.z;

        s16 rotX = actor->world.rot.x;
        s16 rotY = actor->world.rot.y;
        s16 rotZ = actor->world.rot.z;

        s16 params = 0x5E02;

        Actor_Kill(actor);

        Actor_Spawn(&play->actorCtx, play, ACTOR_EN_ELFORG, posX, posY, posZ, rotX, rotY, rotZ, params);

        return;
    }

    if (id == ACTOR_EN_GRASSHOPPER || id == ACTOR_EN_MKK || id == ACTOR_EN_DEKUBABA || id == ACTOR_EN_KAREBABA || id == ACTOR_EN_ST || id == ACTOR_EN_KAME || id == ACTOR_EN_DINOFOS || id == ACTOR_EN_BIGPAMET || id == ACTOR_EN_PAMETFROG) {
        Actor_Kill(actor);
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