#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "recompconfig.h"

RECOMP_IMPORT("ProxyMM_ActorListIndex", s32 GetActorListIndex(Actor* actor));

RECOMP_CALLBACK("*", recomp_after_actor_init)
void Milk_Road_AfterActorInit(PlayState* play, Actor* actor) {
    s32 actorListIndex = GetActorListIndex(actor);

    /*
        0 = All
        1 = Overworld
        2 = Temples
    */

    if (play->sceneId != SCENE_ROMANYMAE || recomp_get_config_u32("unlock_romani") == 1)
        return;

    s32 id = actor->id;

    /*
        0x016D = Boulder Blocking Romani Ranch
        0x026A = Milk Road - Carpenter Hacking at Boulder
    */

    if (id == ACTOR_OBJ_HUGEBOMBIWA) {
        Actor_Kill(actor);
    }

    // I need to alter the flag of the DAIKU2 since it won't dispawn, but it isn't in the state that I want it

    /*

    static bool spawnedDaiku = false;

    if (!spawnedDaiku) {
        spawnedDaiku = true;
        Actor_Spawn(&play->actorCtx, play, ACTOR_EN_CLEAR_TAG, -5578.76f, 69.00f, 1417.68f, 0x0000, 0x0000, 0x0000, 0x0001);
    }

    */

    /*

    DAIKU2 info
    [ActorInit] ListIndex=8 | ID=0x026A (ACTOR_EN_DAIKU2) | Scene=34 (SCENE_ROMANYMAE) | Room=0
    Position  = (X=-5583.00, Y=69.00, Z=1465.00)
    Rotation  = (X=0x0000, Y=0xFFFFB555, Z=0x0000)
    Params = 0x0201
    Enemy Removal Enum: 0
    [ActorInit] ListIndex=9 | ID=0x026A (ACTOR_EN_DAIKU2) | Scene=34 (SCENE_ROMANYMAE) | Room=0
    Position  = (X=-5601.00, Y=68.00, Z=1318.00)
    Rotation  = (X=0x0000, Y=0x0000, Z=0x0000)
    Params = 0xFFFF9FFF

    */

}