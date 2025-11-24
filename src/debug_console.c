#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "recompconfig.h"

RECOMP_IMPORT("ProxyMM_ActorListIndex", s32 GetActorListIndex(Actor* actor));

#define SCENE_NAME_ENTRY(zSeg, enumName, titleId, drawCfg, rest, flags) \
    [enumName] = #enumName,

#define SCENE_NAME_ENTRY_UNSET(enumName) \
    [enumName] = #enumName,

#define ACTOR_NAME_ENTRY(actor, enumName, alloctype, actor_name) \
    [enumName] = #enumName,

#define ACTOR_NAME_ENTRY_UNSET(enumName) \
    [enumName] = #enumName,

static const char* sceneNames[] = {
    #define DEFINE_SCENE            SCENE_NAME_ENTRY
    #define DEFINE_SCENE_UNSET      SCENE_NAME_ENTRY_UNSET
    #include "tables/scene_table.h"
    #undef DEFINE_SCENE
    #undef DEFINE_SCENE_UNSET
};

static const char* actorNames[] = {
    #define DEFINE_ACTOR            ACTOR_NAME_ENTRY
    #define DEFINE_ACTOR_UNSET      ACTOR_NAME_ENTRY_UNSET
    #define DEFINE_ACTOR_INTERNAL   ACTOR_NAME_ENTRY
    #include "tables/actor_table.h"
    #undef DEFINE_ACTOR
    #undef DEFINE_ACTOR_UNSET
    #undef DEFINE_ACTOR_INTERNAL
};

static const char* GetSceneName(int sceneId) {
    if (sceneId < 0 || sceneId >= ARRAY_COUNT(sceneNames)) {
        return "SCENE_INVALID";
    }
    return sceneNames[sceneId] ? sceneNames[sceneId] : "SCENE_UNKNOWN";
}

static const char* GetActorName(int actorId) {
    if (actorId < 0 || actorId >= ARRAY_COUNT(actorNames)) {
        return "ACTOR_INVALID";
    }
    return actorNames[actorId] ? actorNames[actorId] : "ACTOR_UNKNOWN";
}

RECOMP_CALLBACK("*", recomp_after_actor_init)
void Debug_AfterActorInit(PlayState* play, Actor* actor) {

    if (recomp_get_config_u32("debug_console") == 1)
        return;

    s32 listIndex = GetActorListIndex(actor);
    s32 actor_id  = actor->id;
    s32 room      = play->roomCtx.curRoom.num;
    s32 scene     = play->sceneId;

    const char* sceneName = GetSceneName(scene);
    const char* actorName = GetActorName(actor_id);

    recomp_printf("Enemy Removal Enum: %d\n", recomp_get_config_u32("enemy_removal"));

    recomp_printf(
        "[ActorInit] ListIndex=%d | ID=0x%04X (%s) | Scene=%d (%s) | Room=%d\n"
        "  Position  = (X=%.2f, Y=%.2f, Z=%.2f)\n"
        "  Rotation  = (X=0x%04X, Y=0x%04X, Z=0x%04X)\n"
        "  Params = 0x%04X\n",
        listIndex, actor_id, actorName, scene, sceneName, room,
        actor->world.pos.x, actor->world.pos.y, actor->world.pos.z,
        actor->world.rot.x, actor->world.rot.y, actor->world.rot.z,
        actor->params
    );
}
