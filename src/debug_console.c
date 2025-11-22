#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "recompconfig.h"

RECOMP_IMPORT("ProxyMM_ActorListIndex", s32 GetActorListIndex(Actor* actor));

#define SCENE_NAME_ENTRY(zSeg, enumName, titleId, drawCfg, rest, flags) \
    [enumName] = #enumName,

#define SCENE_NAME_ENTRY_UNSET(enumName) \
    [enumName] = #enumName,

static const char* sceneNames[] = {
    #define DEFINE_SCENE            SCENE_NAME_ENTRY
    #define DEFINE_SCENE_UNSET      SCENE_NAME_ENTRY_UNSET
    #include "tables/scene_table.h"
    #undef DEFINE_SCENE
    #undef DEFINE_SCENE_UNSET
};

static const char* GetSceneName(int sceneId) {
    if (sceneId < 0 || sceneId >= ARRAY_COUNT(sceneNames)) {
        return "SCENE_INVALID";
    }
    return sceneNames[sceneId] ? sceneNames[sceneId] : "SCENE_UNKNOWN";
}

RECOMP_CALLBACK("*", recomp_after_actor_init)
void Debug_AfterActorInit(PlayState* play, Actor* actor) {
    s32 listIndex = GetActorListIndex(actor);
    s32 room      = play->roomCtx.curRoom.num;
    s32 scene     = play->sceneId;

    const char* sceneName = GetSceneName(scene);

    recomp_printf(
        "[ActorInit] ListIndex=%d | ID=0x%04X | Scene=%d (%s) | Room=%d\n",
        listIndex, actor->id, scene, sceneName, room
    );
}
