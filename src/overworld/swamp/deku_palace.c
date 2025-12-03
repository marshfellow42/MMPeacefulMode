#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "recompconfig.h"

RECOMP_IMPORT("ProxyMM_ActorListIndex", s32 GetActorListIndex(Actor* actor));

RECOMP_CALLBACK("*", recomp_after_actor_init)
void Deku_Palace_AfterActorInit(PlayState* play, Actor* actor) {
    s32 actorListIndex = GetActorListIndex(actor);

    if(gSaveContext.gameMode != GAMEMODE_NORMAL)
        return;

    /*
        0 = All
        1 = Overworld
        2 = Temples
    */

    if (play->sceneId != SCENE_22DEKUCITY || recomp_get_config_u32("enemy_removal") == 2)
        return;

    /*
        ACTOR_EN_LOOK_NUTS = Deku Palace - Patrolling Deku Guard
        ACTOR_EN_DEKUNUTS = Mad Scrub
    */

    switch (actor->id) {
        case ACTOR_EN_LOOK_NUTS:
            Actor_Kill(actor);
            break;
        case ACTOR_EN_DEKUNUTS: {
            Vec3f pos = actor->world.pos;
            Vec3s rot = actor->world.rot;
            s16 params = 0x0080;

            Actor_Kill(actor);
            Actor_Spawn(&play->actorCtx, play, ACTOR_OBJ_ETCETERA, pos.x, pos.y, pos.z, rot.x, rot.y, rot.z, params);

            return;
        }
    }
}