#pragma once

#include "Vector3.h"
#include "PhysicsObjects.h"
#include "AABBCollisionDetection.h"
#include "circularCollisionDetection.h"

enum class ShapeType {
    AABB,
    CIRCLE
};


struct AosObject {
    uint32_t id;
    ShapeType shape;
    bool onScreen;
    
    PhysicObjAoS physics;
    AoSCollisionShape aabb;
    AoSSphere sphere;
    
}
