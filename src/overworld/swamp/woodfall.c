#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "recompconfig.h"

RECOMP_IMPORT("ProxyMM_ActorListIndex", s32 GetActorListIndex(Actor* actor));

RECOMP_CALLBACK("*", recomp_after_actor_init)
void Woodfall_AfterActorInit(PlayState* play, Actor* actor) {
    s32 actorListIndex = GetActorListIndex(actor);

    /*
        0 = All
        1 = Overworld
        2 = Temples
    */

    if (play->sceneId != SCENE_21MITURINMAE || recomp_get_config_u32("enemy_removal") == 2)
        return;

    s32 id = actor->id;

    /*
        ACTOR_EN_DEKUNUTS = Mad Scrub
        ACTOR_EN_GRASSHOPPER = Dragonfly
        ACTOR_EN_PP = Hiploop
    */

    if (id == ACTOR_EN_DEKUNUTS) {
        float posX = actor->world.pos.x;
        float posY = actor->world.pos.y;
        float posZ = actor->world.pos.z;

        s16 rotX = actor->world.rot.x;
        s16 rotY = actor->world.rot.y;
        s16 rotZ = actor->world.rot.z;

        s16 params = 0x0080;

        Actor_Kill(actor);

        Actor_Spawn(&play->actorCtx, play, ACTOR_OBJ_ETCETERA, posX, posY, posZ, rotX, rotY, rotZ, params);

        return;
    }

    if (id == ACTOR_EN_GRASSHOPPER || id == ACTOR_EN_PP) {
        Actor_Kill(actor);
        return;
    }
}