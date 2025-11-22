#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "recompconfig.h"

#define CUR_ROOM(play) ((play)->roomCtx.curRoom.num)

RECOMP_IMPORT("ProxyMM_ActorListIndex", s32 GetActorListIndex(Actor* actor));

RECOMP_CALLBACK("*", recomp_after_actor_init)
void Great_Bay_Coast_AfterActorInit(PlayState* play, Actor* actor) {
    s32 actorListIndex = GetActorListIndex(actor);

    if (play->sceneId != SCENE_30GYOSON)
        return;

    
}


