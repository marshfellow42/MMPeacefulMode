#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "recompconfig.h"

RECOMP_IMPORT("ProxyMM_ActorListIndex", s32 GetActorListIndex(Actor* actor));

RECOMP_CALLBACK("*", recomp_after_actor_init)
void Termina_Field_AfterActorInit(PlayState* play, Actor* actor) {
    s32 actorListIndex = GetActorListIndex(actor);

    /*
        0 = All
        1 = Overworld
        2 = Temples
    */

    if (play->sceneId != SCENE_00KEIKOKU || recomp_get_config_u32("enemy_removal") == 2)
        return;

    s32 id = actor->id;

    /*
        0x003E = Blue Bubbles
        0x014A = Chuchu
        0x0033 = Deku Baba
        0x015B = Bad Bat
        0x0291 = Takkuri
        0x0216 = Leever
        0x000B = Dodongo
        0x00F1 = Guay
        0x016F = Real Bombchu
        0x0266 = Guay Circling Clock Town
    */

    if (id == 0x003E || id == 0x014A || id == 0x0033 || id == 0x015B || id == 0x0291 || id == 0x0216 || id == 0x000B || id == 0x00F1 || id == 0x016F || id == 0x0266) {
        Actor_Kill(actor);
    }
}