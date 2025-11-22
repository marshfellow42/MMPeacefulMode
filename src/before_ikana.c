#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "recompconfig.h"

RECOMP_IMPORT("ProxyMM_ActorListIndex", s32 GetActorListIndex(Actor* actor));

RECOMP_CALLBACK("*", recomp_after_actor_init)
void Before_Ikana_AfterActorInit(PlayState* play, Actor* actor) {
    s32 actorListIndex = GetActorListIndex(actor);

    if (play->sceneId != SCENE_IKANAMAE)
        return;

    s32 id = actor->id;

    if (id == 0x016F) {
        Actor_Kill(actor);
    }
}
