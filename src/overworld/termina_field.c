#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "recompconfig.h"

RECOMP_IMPORT("ProxyMM_ActorListIndex", s32 GetActorListIndex(Actor* actor));

RECOMP_CALLBACK("*", recomp_after_actor_init)
void Termina_Field_AfterActorInit(PlayState* play, Actor* actor) {
    s32 actorListIndex = GetActorListIndex(actor);

    if(gSaveContext.gameMode != GAMEMODE_NORMAL)
        return;

    /*
        0 = All
        1 = Overworld
        2 = Temples
    */

    if (play->sceneId != SCENE_00KEIKOKU || recomp_get_config_u32("enemy_removal") == 2)
        return;

    s32 id = actor->id;

    /*
        ACTOR_EN_BB = Blue Bubbles
        ACTOR_EN_SLIME = Chuchu
        ACTOR_EN_DEKUBABA = Deku Baba
        ACTOR_EN_BAT = Bad Bat
        ACTOR_EN_THIEFBIRD = Takkuri
        ACTOR_EN_NEO_REEBA = Leever
        ACTOR_EN_DODONGO = Dodongo
        ACTOR_EN_CROW = Guay
        ACTOR_EN_RAT = Real Bombchu
        ACTOR_EN_RUPPECROW = Guay Circling Clock Town
    */

    if (id == ACTOR_EN_BB || id == ACTOR_EN_SLIME || id == ACTOR_EN_DEKUBABA || id == ACTOR_EN_BAT || id == ACTOR_EN_THIEFBIRD || id == ACTOR_EN_NEO_REEBA || id == ACTOR_EN_DODONGO || id == ACTOR_EN_CROW || id == ACTOR_EN_RAT || id == ACTOR_EN_RUPPECROW) {
        Actor_Kill(actor);
    }
}