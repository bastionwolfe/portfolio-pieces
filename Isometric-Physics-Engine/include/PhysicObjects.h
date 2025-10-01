//physobjs
#include <vector>
#include "Vector3.h"

class PhysicsObjAoS {
    public:
    AoS_Vec3 position;
    AoS_Vec3 velocity;
    AoS_Vec3 acceleration;
    AoS_Vec3 forceAccumulator;
    
    float mass;
    float inverseMass;
    float friction;
    float restitution;
    
    PhysicsObjAoS(AoS_Vec3 pos, float objMass) {
        position = pos;
        velocity = AoS_Vec3(0.00f, 0.00f, 0.00f);
        acceleration = AoS_Vec3(0.00f, 0.00f, 0.00f);
        forceAccumulator = AoS_Vec3(0.00f, 0.00f, 0.00f);
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
        mass = ObjAoS.mass;
        inverseMass = ObjAoS.inverseMass;
        friction = ObjAoS.friction;
        restitution = ObjAoS.restitution;
    }
    
    PhysicsObjAos& operator =(const PhysicsObjAoS& ObjAoS) {
        if (this != &ObjAoS) {
            position = ObjAoS.position;
            velocity = ObjAoS.velocity;
            acceleration = ObjAoS.acceleration;
            forceAccumulator = ObjAoS.forceAccumulator;
            mass = ObjAoS.mass;
            inverseMass = ObjAoS.inverseMass;
            friction = ObjAoS.friction;
            restitution = ObjAoS.restitution;
        }
        return *this;
    }
    
    void integrateVelocity(float dt) {
        velocity += acceleration * dt;
    }
    
    void integratePosition(float dt) {
        position += velocity * dt;
    }
    
    void clearForce() {
        forceAccumulator = AoS_Vec3(0.00f, 0.00f, 0.00f);
    }
    
    void applyForce(float xForce, float yForce, float zForce) {
        forceAccumulator.x = xForce;
        forceAccumulator.y = yForce;
        forceAccumulator.z = zForce;
    }
    
    void applyFriction() {
    }
    
    void setRestitution(float r) {
        if (r < 0 || r > 1) return;
        restitution = r;
    }
    
    void updateAcceleration() {
        if (mass == 0) return;
        accelerations[i] = forceAccumulator[i] * inverseMasses[i];
        clearForce[i];
    }
    
};

class PhysicsObjSoA {
    public:
    // include mass, inverse mass, friction, resitution, force accumilator
    std::vector<SoA_Vec3> positions;
    std::vector<SoA_Vec3> velocities;
    std::vector<SoA_Vec3> accelerations;
    std::vector<SoA_Vec3> forceAccumulator;
    
    std::vector<float> masses;
    std::vector<float> inverseMasses;
    std::vector<float> friction;
    std::vector<float> restitution;

    PhysicsObjSoA(int numObjects) {
        positions.resize(numObjects);
        velocities.resize(numObjects);
        accelerations.resize(numObjects);
        forceAccumulator.resize(numObjects);
        masses.resize(numObjects, 1.0f);
        inverseMasses.resize(numObjects, 1.0f);
        friction.resize(numObjects, 0.5f);
        restitution.resize(numObjects, 0.5f);
    }
    
    PhysicsObjSoA(const PhysicsObjSoA& ObjSoA) 
        : positions(ObjSoA.positions), velocities(ObjSoA.velocities), accelerations(ObjSoA.accelerations), forceAccumulator(ObjSoA.forceAccumulator),
         masses(ObjSoA.masses), inverseMasses(ObjSoA.inverseMasses), friction(ObjSoA.friction), restitution(ObjSoA.restitution) {}

    PhysicsObjSoA& operator=(const PhysicsObjSoA& ObjSoA) {
        if (this != &ObjSoA) {
            positions = ObjSoA.positions;
            velocities = ObjSoA.velocities;
            accelerations = ObjSoA.accelerations;
            forceAccumulator = ObjSoA.forceAccumulator;
            masses = ObjSoA.masses;
            inverseMasses = ObjSoA.inverseMasses;
            friction = ObjSoA.friction;
            restitution = ObjSoA.restitution;
        }
        return *this;
    }


    void integrateVelocities(float dt) {
        for (size_t i = 0; i < velocities.size(); ++i) {
            velocities[i] += accelerations[i] * dt;
        }
    }

    void integratePositions(float dt) {
        for (size_t i = 0; i < positions.size(); ++i) {
            positions[i] += velocities[i] * dt;
        }
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
    
    void applyFriction() {
        
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
                clearForce[i];
            }
        }
    }
};

class PhysicsObjSoAoS8 {
    public:
    SoAoS8 positions;
    SoAoS8 velocities;
    SoAoS8 accelerations;
    SoAoS8 forceAccumulators;
    
    std::vector<float> masses;
    std::vector<float> inverseMasses;
    std::vector<float> friction;
    std::vector<float> restitution;
    
    PhysicsObjSoAoS8(int numObjects)
    : positions(numObjects),
      velocities(numObjects),
      accelerations(numObjects),
      forceAccumulators(numObjects),
      masses(numObjects, 1.0f),
      inverseMasses(numObjects, 1.0f),
      friction(numObjects, 0.5f),
      restitution(numObjects, 0.5f) {}
    
    PhysicsObjSoAoS8(const PhysicsObjSoAoS8& ObjSoAoS8) {
        positions = ObjSoAoS8.positions;
        velocities = ObjSoAoS8.velocities;
        accelerations = ObjSoAoS8.accelerations;
        forceAccumulators = ObjSoAoS8.forceAccumulators;
        masses = ObjSoAoS8.masses;
        inverseMasses = ObjSoAoS8.inverseMasses;
        friction = ObjSoAoS8.friction;
        restitution = ObjSoAoS8.restitution;
    }
    
    PhysicsObjSoAoS8& operator =(const PhysicsObjSoAoS8& ObjSoAoS8) {
        if (this != ObjSoAoS8) {
            positions = ObjSoAoS8.positions;
            velocities = ObjSoAoS8.velocities;
            accelerations = ObjSoAoS8.accelerations;
            forceAccumulators = ObjSoAoS8.forceAccumulators;
            masses = ObjSoAoS8.masses;
            inverseMasses = ObjSoAoS8.inverseMasses;
            friction = ObjSoAoS8.friction;
            restitution = ObjSoAoS8.restitution;
        }
        return *this;
    }
    
    void integrateVelocities(float dt) {
        int objectCount = velocities.getSize();

        for (int i = 0; i < objectCount; ++i) {
            float vx = velocities.getX(i);
            float vy = velocities.getY(i);
            float vz = velocities.getZ(i);
            float ax = accelerations.getX(i);
            float ay = accelerations.getY(i);
            float az = accelerations.getZ(i);
            velocities.setX(i, vx + ax * dt);
            velocities.setY(i, vy + ay * dt);
            velocities.setZ(i, vz + az * dt);
        }
    }  
    
    void integratePositions(float dt) {
        int objectCount = positions.getSize();
        
        for (int i = 0; i < objectCount; ++i) {
            float px = positions.getX(i);
            float py = positions.getY(i);
            float pz = positions.getZ(i);
            float vx = velocities.getX(i);
            float vy = velocities.getY(i);
            float vz = velocities.getZ(i);
            positions.setX(i, px + vx * dt);
            positions.setY(i, py + vy * dt);
            positions.setZ(i, pz + vz * dt);
        }
       
        
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
            forceAccumulator.setX(i, 0);
            forceAccumulator.setY(i, 0);
            forceAccumulator.setZ(i, 0);
        }
    }
    
    void applyForce(int i, float xForce, float yForce, float zForce) {
        forceAccumulator.setX(i, xForce);
        forceAccumulator.setY(i, yForce);
        forceAccumulator.setZ(i, zForce);
    }
    
    void applyFriction() {
    }
    
    void setRestitutions(float r, int i) {
        if (r < 0 || r > 1) return;
        if (i < 0 || i >= restitution.size()) return;
        restitution[i] = r;
    }
    
    void updateAccelerations() {
        int posSize = positions.getSize();
        if (posSize == forceAccumulator.getSize() && posSize == masses.size()) {
            for (int i = 0; i < posSize; ++i) {
                if (masses[i] == 0.00f) continue;
                accelerations.setX(i, forceAccumulator.getX(i) * inverseMasses.getX(i));
                accelerations.setY(i, forceAccumulator.getY(i) * inverseMasses.getY(i));
                accelerations.setZ(i, forceAccumulator.getZ(i) * inverseMasses.getZ(i));
            }
            clearForce();
        }
    }
    
};
