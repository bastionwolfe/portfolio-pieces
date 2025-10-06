//physobjs
#include <vector>
#include "Vector3.h"
#include "physMathUtils.h"

class PhysicsObjAoS {
    public:
    AoS_Vec3 position;
    AoS_Vec3 velocity;
    AoS_Vec3 acceleration;
    AoS_Vec3 forceAccumulator;
    AoS_Vec3 previousPosition;
    
    float mass;
    float inverseMass;
    float friction;
    float restitution;
    
    PhysicsObjAoS(AoS_Vec3 pos, float objMass) {
        position = pos;
        velocity = AoS_Vec3(0.00f, 0.00f, 0.00f);
        acceleration = AoS_Vec3(0.00f, 0.00f, 0.00f);
        forceAccumulator = AoS_Vec3(0.00f, 0.00f, 0.00f);
        previousPosition = position;
        mass = objMass;
        inverseMass = (mass != 0.0f) ? 1.0f / mass : 0.0f;
        friction = 0.50f;
        restitution = 0.50f;
    }
    
    PhysicsObjAoS(const PhysicsObjAoS& ObjAoS) {
        position = ObjAoS.position;
        velocity = ObjAoS.velocity;
        acceleration = ObjAoS.acceleration;
        forceAccumulator = ObjAoS.forceAccumulator;
        previousPosition = ObjAoS.previousPosition;
        mass = ObjAoS.mass;
        inverseMass = ObjAoS.inverseMass;
        friction = ObjAoS.friction;
        restitution = ObjAoS.restitution;
    }
    
    PhysicsObjAoS& operator =(const PhysicsObjAoS& ObjAoS) {
        if (this != &ObjAoS) {
            position = ObjAoS.position;
            velocity = ObjAoS.velocity;
            acceleration = ObjAoS.acceleration;
            forceAccumulator = ObjAoS.forceAccumulator;
            previousPosition = ObjAoS.previousPosition;
            mass = ObjAoS.mass;
            inverseMass = ObjAoS.inverseMass;
            friction = ObjAoS.friction;
            restitution = ObjAoS.restitution;
        }
        return *this;
    }
    
    void clearForce() {
        forceAccumulator = AoS_Vec3(0.00f, 0.00f, 0.00f);
    }
    
    void applyForce(float xForce, float yForce, float zForce) {
        forceAccumulator.x += xForce;
        forceAccumulator.y += yForce;
        forceAccumulator.z += zForce;
    }
    
    void applyFriction(float gravity = 9.81f) {
        float speed = velocity.magnitude();
        if (speed < 1e-5f) return;
        
        float frictionForceMag = friction * mass * gravity;
        AoS_Vec3 frictionForce = velocity.normalized() * (-frictionForceMage);
        applyForce(frictionForce.x, frictionForce.y, frictionForce.y);
    }
    
    void setRestitution(float r) {
        if (r < 0 || r > 1) return;
        restitution = r;
    }
    
    void updateAcceleration() {
        if (mass == 0.0f) return;
        acceleration = forceAccumulator * inverseMass;
        clearForce();
    }
    
};

class PhysicsObjSoA {
    public:
    // include mass, inverse mass, friction, resitution, force accumilator
    std::vector<SoA_Vec3> positions;
    std::vector<SoA_Vec3> velocities;
    std::vector<SoA_Vec3> accelerations;
    std::vector<SoA_Vec3> forceAccumulator;
    std::vector<SoA_Vec3> previousPositions;
    
    std::vector<float> masses;
    std::vector<float> inverseMasses;
    std::vector<float> friction;
    std::vector<float> restitution;

    PhysicsObjSoA(int numObjects) {
        positions.resize(numObjects);
        velocities.resize(numObjects);
        accelerations.resize(numObjects);
        forceAccumulator.resize(numObjects);
        previousPositions.resize(numObjects);
        for (int i = 0; i < numObjects; ++i) {
            previousPositions[i] = positions[i];
        }
        masses.resize(numObjects, 1.0f);
        inverseMasses.resize(numObjects, 1.0f);
        friction.resize(numObjects, 0.5f);
        restitution.resize(numObjects, 0.5f);
    }
    
    PhysicsObjSoA(const PhysicsObjSoA& ObjSoA) 
        : positions(ObjSoA.positions), velocities(ObjSoA.velocities), accelerations(ObjSoA.accelerations), forceAccumulator(ObjSoA.forceAccumulator),
         previousPositions(ObjSoA.previousPositions), masses(ObjSoA.masses), inverseMasses(ObjSoA.inverseMasses), friction(ObjSoA.friction), restitution(ObjSoA.restitution) {}

    PhysicsObjSoA& operator=(const PhysicsObjSoA& ObjSoA) {
        if (this != &ObjSoA) {
            positions = ObjSoA.positions;
            velocities = ObjSoA.velocities;
            accelerations = ObjSoA.accelerations;
            forceAccumulator = ObjSoA.forceAccumulator;
            previousPositions = ObjSoA.previousPositions;
            masses = ObjSoA.masses;
            inverseMasses = ObjSoA.inverseMasses;
            friction = ObjSoA.friction;
            restitution = ObjSoA.restitution;
        }
        return *this;
    }
    
    int getSize() const {
        return static_cast<int>(positions.size());
    }
    
    void inverseMassCalc() {
        for (int i = 0; i < masses.size(); ++i) {
            if (masses[i] == 0) {
                inverseMasses[i] = 0;
            }
            else {
                inverseMasses[i] = 1 / masses[i];
            }
        }
    }
    
    void clearForce(int i) {
        forceAccumulator[i].x = 0;
        forceAccumulator[i].y = 0;
        forceAccumulator[i].z = 0;
    }
    
    void applyForce(int i, float xForce, float yForce, float zForce) {
        forceAccumulator[i].x += xForce;
        forceAccumulator[i].y += yForce;
        forceAccumulator[i].z += zForce;
    }
    
    void applyFriction(float gravity = 9.81f) {
    for (int i = 0; i < velocities.size(); ++i) {
        float speed = velocities[i].magnitude();
        if (speed < 1e-5f) continue;
        float frictionForceMag = friction[i] * masses[i] * gravity;
        SoA_Vec3 frictionForce = velocities[i].normalized() * (-frictionForceMag);
        applyForce(i, frictionForce.x, frictionForce.y, frictionForce.z);
    }
}

    
    void setRestitutions(float r, int i) {
        if (r < 0 || r > 1) return;
        if (i < 0 || i >= restitutions.size()) return;
        restitutions[i] = r;
    }
    
    void updateAccelerations() {
        if (positions.size() == forceAccumulator.size() && forceAccumulator.size() == masses.size()) {
            for (int i = 0; i < positions.size(); ++i) {
                if (masses[i] == 0.00f) continue;
                accelerations[i] = forceAccumulator[i] * inverseMasses[i];
                clearForce(i);
            }
        }
    }
};

class PhysicsObjAoSoA8 {
    public:
    AoSoA8 positions;
    AoSoA8 velocities;
    AoSoA8 accelerations;
    AoSoA8 forceAccumulators;
    AoSoA8 previousPositions;
    
    std::vector<float> masses;
    std::vector<float> inverseMasses;
    std::vector<float> friction;
    std::vector<float> restitution;
    
    PhysicsObjAoSoA8(int numObjects)
    : positions(numObjects),
      velocities(numObjects),
      accelerations(numObjects),
      forceAccumulators(numObjects),
      previousPositions(numObjects),
      masses(numObjects, 1.0f),
      inverseMasses(numObjects, 1.0f),
      friction(numObjects, 0.5f),
      restitution(numObjects, 0.5f) {
          previousPositions = positions;
          }
    
    PhysicsObjAoSoA8(const PhysicsObjAoSoA8& ObjAoSoA8) {
        positions = ObjAoSoA8.positions;
        velocities = ObjAoSoA8.velocities;
        accelerations = ObjAoSoA8.accelerations;
        forceAccumulators = ObjAoSoA8.forceAccumulators;
        previousPositions = ObjAoSoA8.previousPositions;
        masses = ObjAoSoA8.masses;
        inverseMasses = ObjAoSoA8.inverseMasses;
        friction = ObjAoSoA8.friction;
        restitution = ObjAoSoA8.restitution;
    }
    
    PhysicsObjAoSoA8& operator =(const PhysicsObjAoSoA8& ObjAoSoA8) {
        if (this != &ObjAoSoA8) {
            positions = ObjAoSoA8.positions;
            velocities = ObjAoSoA8.velocities;
            accelerations = ObjAoSoA8.accelerations;
            forceAccumulators = ObjAoSoA8.forceAccumulators;
            previousPositions = ObjAoSoA8.previousPositions;
            masses = ObjAoSoA8.masses;
            inverseMasses = ObjAoSoA8.inverseMasses;
            friction = ObjAoSoA8.friction;
            restitution = ObjAoSoA8.restitution;
        }
        return *this;
    }
    
    void inverseMassCalc() {
        for (int i = 0; i < masses.size(); ++i) {
            if (masses[i] == 0) {
                inverseMasses[i] = 0;
            }
            else {
                inverseMasses[i] = 1 / masses[i];
            }
        }
    }
    
    void clearForce() {
        int forceSize = forceAccumulators.getSize();
        for (int i = 0; i < forceSize; ++i) {
            forceAccumulators.setX(i, 0);
            forceAccumulators.setY(i, 0);
            forceAccumulators.setZ(i, 0);
        }
    }
    
    void applyForce(int i, float xForce, float yForce, float zForce) { 
        forceAccumulators.setX(i, forceAccumulators.getX(i) + xForce);
        forceAccumulators.setY(i, forceAccumulators.getY(i) + yForce);
        forceAccumulators.setZ(i, forceAccumulators.getZ(i) + zForce);
    }
    
    void applyFriction(float gravity = 9.81f) {
    int count = velocities.getSize();

    for (int i = 0; i < count; ++i) {
        
        AoS_Vec3 vel(
            velocities.getX(i),
            velocities.getY(i),
            velocities.getZ(i)
        );

        float speed = vel.magnitude();
        if (speed < 1e-5f) continue;

        float frictionForceMag = friction[i] * masses[i] * gravity;
        AoS_Vec3 frictionForce = vel.normalized() * (-frictionForceMag);

        applyForce(i, frictionForce.x, frictionForce.y, frictionForce.z);
    }
}

    
    void setRestitutions(float r, int i) {
        if (r < 0 || r > 1) return;
        if (i < 0 || i >= restitution.size()) return;
        restitution[i] = r;
    }
    
    void updateAccelerations() {
        int posSize = positions.getSize();
        if (posSize == forceAccumulators.getSize() && posSize == masses.size()) {
            for (int i = 0; i < posSize; ++i) {
                if (masses[i] == 0.00f) continue;
                accelerations.setX(i, forceAccumulators.getX(i) * inverseMasses[i]);
                accelerations.setY(i, forceAccumulators.getY(i) * inverseMasses[i]);
                accelerations.setZ(i, forceAccumulators.getZ(i) * inverseMasses[i]);
            }
            clearForce();
        }
    }
    
};
