#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "recompconfig.h"

RECOMP_IMPORT("ProxyMM_ActorListIndex", s32 GetActorListIndex(Actor* actor));

RECOMP_CALLBACK("*", recomp_after_actor_init)
void Termina_Field_AfterActorInit(PlayState* play, Actor* actor) {
    s32 actorListIndex = GetActorListIndex(actor);

    if (play->sceneId != SCENE_00KEIKOKU)
        return;

    s32 id = actor->id;

    if (id == 0x003E || id == 0x014A || id == 0x0033 || id == 0x015B || id == 0x0291 || id == 0x0216 || id == 0x000B || id == 0x00F1 || id == 0x016F || id == 0x0266) {
        Actor_Kill(actor);
    }
}
