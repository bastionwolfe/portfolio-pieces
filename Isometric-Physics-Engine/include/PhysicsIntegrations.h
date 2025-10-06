  //PhysicsIntegration
  #include "PhysicObject.h"
  
  
  //AoS integrations
    void AoSIntegrateVelocity(PhysicsObjAoS& AoSObj, float dt) {
        AoSObj.velocity += AoSObj.acceleration * dt;
    }

    void AoSIntegratePosition(PhysicsObjAoS& AoSObj, float dt) {
        AoSObj.position += AoSObj.velocity * dt;
    }
    
    void AoSIntegrateEuler(PhysicsObjAoS& AoSObj, float dt, float damping) {
        AoSObj.velocity *= damping;
        AoSIntegrateVelocity(AoSObj, dt);
        AoSIntegratePosition(AoSObj, dt);
    }

    void AoSIntegrateVerlet(PhysicsObjAoS& AoSObj, float dt, float damping) {
        AoS_Vec3 temp = AoSObj.position;
        AoSObj.position = AoSObj.position * 2.0f - AoSObj.previousPosition + AoSObj.acceleration * (dt * dt);
        AoSObj.previousPosition = temp + (AoSObj.previousPosition - temp) * damping;
    }
    
    
    //SoA integrations
    
    void SoAIntegrateVelocities(PhysicsObjSoA& SoAObj, float dt, float damping) {
        for (size_t i = 0; i < SoAObj.velocities.size(); ++i) {
            SoAObj.velocities[i] *= damping;
            SoAObj.velocities[i] += SoAObj.accelerations[i] * dt;
        }
    }

    void SoAIntegratePositions(PhysicsObjSoA& SoAObj, float dt) {
        for (size_t i = 0; i < SoAObj.positions.size(); ++i) {
            SoAObj.positions[i] += SoAObj.velocities[i] * dt;
        }
    }
    
    void SoAIntegrateEuler(PhysicsObjSoA& SoAObj, float dt, float damping) {
        SoAIntegrateVelocities(SoAObj, dt, damping);
        SoAIntegratePositions(SoAObj, dt);
    }
    
    void SoAIntegrateVerlets(PhysicsObjSoA& SoAObj, float dt, float damping) {
         for (size_t i = 0; i < SoAObj.positions.size(); ++i) {
            SoA_Vec3 temp = SoAObj.positions[i];
            SoAObj.positions[i] = SoAObj.positions[i] * 2.0f - SoAObj.previousPositions[i] + SoAObj.accelerations[i] * (dt * dt);
            SoAObj.previousPositions[i] = temp + (SoAObj.previousPositions[i] - temp) * damping;
        }
    }
    
    
    //AoSoA8 integrations
    
    void AoSoA8IntegrateVelocities(PhysicsObjAoSoA8& ObjAoSoA8, float dt, float damping) {
        int objectCount = ObjAoSoA8.velocities.getSize();

        for (int i = 0; i < objectCount; ++i) {
            float vx = ObjAoSoA8.velocities.getX(i) * damping;
            float vy = ObjAoSoA8.velocities.getY(i) * damping;
            float vz = ObjAoSoA8.velocities.getZ(i) * damping;
            float ax = ObjAoSoA8.accelerations.getX(i);
            float ay = ObjAoSoA8.accelerations.getY(i);
            float az = ObjAoSoA8.accelerations.getZ(i);
            ObjAoSoA8.velocities.setX(i, vx + ax * dt);
            ObjAoSoA8.velocities.setY(i, vy + ay * dt);
            ObjAoSoA8.velocities.setZ(i, vz + az * dt);
        }
    }  
    
    void AoSoA8IntegratePositions(PhysicsObjAoSoA8& ObjAoSoA8, float dt) {
        int objectCount = ObjAoSoA8.positions.getSize();
        
        for (int i = 0; i < objectCount; ++i) {
            float px = ObjAoSoA8.positions.getX(i);
            float py = ObjAoSoA8.positions.getY(i);
            float pz = ObjAoSoA8.positions.getZ(i);
            float vx = ObjAoSoA8.velocities.getX(i);
            float vy = ObjAoSoA8.velocities.getY(i);
            float vz = ObjAoSoA8.velocities.getZ(i);
            ObjAoSoA8.positions.setX(i, px + vx * dt);
            ObjAoSoA8.positions.setY(i, py + vy * dt);
            ObjAoSoA8.positions.setZ(i, pz + vz * dt);
        }
       
        
    }
    
    void AoSoA8IntegrateEuler(PhysicsObjAoSoA8& ObjAoSoA8, float dt, float damping) {
        AoSoA8IntegrateVelocities(ObjAoSoA8, dt, damping)
        AoSoA8IntegratePositions(ObjAoSoA8, dt)
    }
    
    void AoSoA8IntegrateVerlets(PhysicsObjAoSoA8& ObjAoSoA8, float dt, float damping) {
    int objectCount = ObjAoSoA8.positions.getSize();

    for (int i = 0; i < objectCount; ++i) {
        float px = ObjAoSoA8.positions.getX(i);
        float py = ObjAoSoA8.positions.getY(i);
        float pz = ObjAoSoA8.positions.getZ(i);

        float ppx = ObjAoSoA8.previousPositions.getX(i);
        float ppy = ObjAoSoA8.previousPositions.getY(i);
        float ppz = ObjAoSoA8.previousPositions.getZ(i);

        float ax = ObjAoSoA8.accelerations.getX(i);
        float ay = ObjAoSoA8.accelerations.getY(i);
        float az = ObjAoSoA8.accelerations.getZ(i);
        float dtSq = dt * dt;

        float newX = 2.0f * px - ppx + ax * dtSq;
        float newY = 2.0f * py - ppy + ay * dtSq;
        float newZ = 2.0f * pz - ppz + az * dtSq;

        ObjAoSoA8.previousPositions.setX(i, px + (ppx - px) * damping);
        ObjAoSoA8.previousPositions.setY(i, py + (ppy - py) * damping);
        ObjAoSoA8.previousPositions.setZ(i, pz + (ppz - pz) * damping);

        ObjAoSoA8.positions.setX(i, newX);
        ObjAoSoA8.positions.setY(i, newY);
        ObjAoSoA8.positions.setZ(i, newZ);
        }
    }
    
