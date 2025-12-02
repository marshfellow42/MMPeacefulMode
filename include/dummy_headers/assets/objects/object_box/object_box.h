#ifndef OBJECT_BOX_H
#define OBJECT_BOX_H

#include "ultra64.h"
#include "global.h"

// Limb identifiers for gBoxChestSkel
typedef enum ObjectBoxChestLimb {
    OBJECT_BOX_CHEST_LIMB_NONE,
    OBJECT_BOX_CHEST_LIMB_01,
    OBJECT_BOX_CHEST_LIMB_02,
    OBJECT_BOX_CHEST_LIMB_03,
    OBJECT_BOX_CHEST_LIMB_MAX
} ObjectBoxChestLimb;

// Skeleton
extern SkeletonHeader gBoxChestSkel;

// Animations
extern AnimationHeader gBoxChestOpenAnim;
extern AnimationHeader gBoxBigChestOpenAdultAnim;
extern AnimationHeader gBoxBigChestOpenGoronAnim;
extern AnimationHeader gBoxBigChestOpenZoraAnim;
extern AnimationHeader gBoxBigChestOpenDekuAnim;
extern AnimationHeader gBoxBigChestOpenChildAnim;

// Display Lists – base and lid variations
extern Gfx gBoxChestBaseDL[];
extern Gfx gBoxChestBaseGildedDL[];
extern Gfx gBoxChestBaseOrnateDL[];

extern Gfx gBoxChestLidDL[];
extern Gfx gBoxChestLidGildedDL[];
extern Gfx gBoxChestLidOrnateDL[];

// Collision
extern CollisionHeader gBoxChestCol;

#endif
