//AABB collision detection
#include <vector>
#include "Vector3.h"

//dimensions help
//X = width
//y = height
//z = depth

class AoSCollisionShape{
    AoS_Vec3 position;
    AoS_Vec3 dimensions;
    
    AoSCollisionShape(AoS_Vec3 pos, AoS_Vec3 dim) {
        position = pos;
        dimensions = dim;
    }
    
    AoSCollisionShape(const AoSCollisionShape& AoSShape) {
        position = AoSShape.position;
        dimensions = AoSShape.dimensions;
    }
    
    AoSCollisionShape& operator =(const AoSCollisionShape& AoSShape( {
        if (this != &AoSShape) {
            position = AoSShape.position;
            dimensions = AoSShape.dimensions;
        }
        return *this;
    }
    
    AoS_Vec3 getMin() const {
        return AoS_Vec3 {
            position.x - dimensions.x  / 2.0f,
            position.y,
            position.z - dimensions.z / 2.0f
        };
    }
    AoS_Vec3 getMax() const {
        return AoS_Vec3 {
            position.x + dimensions.x  / 2.0f,
            position.y + dimensions.y,
            position.z + dimensions.z / 2.0f
        };
    }
}

bool AoSAABBOverlap(const AoSCollisionShape& a, const AoSCollisionShape& b) {
    AoS_Vec3 aMin = a.getMin();
    AoS_Vec3 aMax = a.getMax();
    AoS_Vec3 bMin = b.getMin();
    AoS_Vec3 bMax = b.getMax();

    return (
        aMax.x >= bMin.x && aMin.x <= bMax.x &&
        aMax.y >= bMin.y && aMin.y <= bMax.y &&
        aMax.z >= bMin.z && aMin.z <= bMax.z
    );
}

class SoACollisionShape {
    std::vector<SoA_Vec3> positions;
    std::vector<SoA_Vec3> dimensions;
    
    SoACollisionShape(int numObjects) {
        positions.resize(numObjects);
        dimensions.resize(numObjects);
    }
    
    SoACollisionShape(const SoACollisionShape& SoAShape) {
        positions = SoAShape.positions;
        dimensions = SoAShape.dimensions;
    }
    
    SoACollisionsShape& operator =(const SoACollisionShape& SoAShape) {
        if (this != &SoAShape) {
            positions = SoAShape.positions;
        dimensions = SoAShape.dimensions;
        }
        return *this;
    }
    
    SoA_Vec3 getMin(int i) const {
        return SoA_Vec3 {
            positions[i].x - dimensions[i].x  / 2.0f,
            positions[i].y,
            positions[i].z - dimensions[i].z / 2.0f
        };
    }
    
    SOA_Vec3 getMax(int i) const {
        return SoA_Vec3 {
            positions[i].x + dimensions[i].x  / 2.0f,
            positions[i].y + dimensions[i].y,
            positions[i].z + dimensions[i].z / 2.0f
        };
    }
    
    bool SoAAABBOverlapInternal() {
        if (positions.size() != dimensions.size()) {
            return false;
        }
        int numObjects = positions.size();
        for (int i = 0; i < numObjects; ++i) {
            for (int j = i + 1; j < numObjects; ++j) {
                SoA_Vec3 aMin = getMin(i);
                SoA_Vec3 aMax = getMax(i);
                SoA_Vec3 bMin = getMin(j);
                SoA_Vec3 bMax = getMax(j);
                bool overlapX = aMax.x >= bMin.x && aMin.x <= bMax.x;
                bool overlapY = aMax.y >= bMin.y && aMin.y <= bMax.y;
                bool overlapZ = aMax.z >= bMin.z && aMin.z <= bMax.z;

                if (overlapX && overlapY && overlapZ) {
                    return true;
                }
            }
        }
        return false;
    }
}

bool SoAAABBExternal(const SoACollisionShape& a, const SoACollisionShape& b) {
    if (a.positions.size() != a.dimensions.size() || b.positions.size() != b.dimensions.size()) {
        return false;
    }
    int numObjectsa = a.positions.size();
    int numObjectsb = b.positions.size();
    for (int i = 0; i < numObjectsa; ++i) {
        for (int j = 0; j < numObjectsb; ++j) {
            SoA_Vec3 aMin = a.getMin(i);
            SoA_Vec3 aMax = a.getMax(i);
            SoA_Vec3 bMin = b.getMin(j);
            SoA_Vec3 bMax = b.getMax(j);
            bool overlapX = aMax.x >= bMin.x && aMin.x <= bMax.x;
            bool overlapY = aMax.y >= bMin.y && aMin.y <= bMax.y;
            bool overlapZ = aMax.z >= bMin.z && aMin.z <= bMax.z;
            if (overlapX && overlapY && overlapZ) {
                return true;
            }
        }
    }
    return false;
}

class AoSoA8CollisionShape() {
    AoSoA8 positions;
    AoSoA8 dimensions;
    
    AoSoA8CollisionShape(int numObjects) {
        positions.resize(numObjects);
        dimensions.resize(numObjects);
    }
    
    AoSoA8CollisionShape(const AoSoA8CollisionShape& AoSoA8Shape) {
        positions = AoSoA8Shape.positions;
        dimensions = AoSoA8Shape.dimensions;
    }
    
    AoSoA8CollisionShape& operator =(const AoSoA8CollisionShape& AoSoA8Shape) {
        if (this != AoSoA8Shape) {
            positions = AoSoA8Shape.positions;
            dimensions = AOSoA8Shape.dimensions;
        }
        return *this;
    }
    
    Vec3_8 getMin(int i) const {
        float minX = positions.getX(i) - (dimensions.getX(i) / 2.0f);
        float minY = positions.getY(i);  // assuming y is bottom
        float minZ = positions.getZ(i) - (dimensions.getZ(i) / 2.0f);
    
        return Vec3_8{ minX, minY, minZ };
    }

    Vec3_8 getMax(int i) const {
        float maxX = positions.getX(i) + (dimensions.getX(i) / 2.0f);
        float maxY = positions.getY(i) + dimensions.getY(i);  // y + height
        float maxZ = positions.getZ(i) + (dimensions.getZ(i) / 2.0f);
    
        return Vec3_8{ minX, minY, minZ };
    }
    
    bool AoSoA8AABBInternal() const {
        int size = positions.getSize();
        if (dimensions.getSize() != size) {
            return false;
        }
        for (int i = 0; i < size; ++i) {
            float aMinX = positions.getX(i) - dimensions.getX(i) / 2.0f;
            float aMaxX = positions.getX(i) + dimensions.getX(i) / 2.0f;
            float aMinY = positions.getY(i);
            float aMaxY = positions.getY(i) + dimensions.getY(i);
            float aMinZ = positions.getZ(i) - dimensions.getZ(i) / 2.0f;
            float aMaxZ = positions.getZ(i) + dimensions.getZ(i) / 2.0f;
            for (int j = i + 1; j < size; ++j) {
                float bMinX = positions.getX(j) - dimensions.getX(j) / 2.0f;
                float bMaxX = positions.getX(j) + dimensions.getX(j) / 2.0f;
                float bMinY = positions.getY(j);
                float bMaxY = positions.getY(j) + dimensions.getY(j);
                float bMinZ = positions.getZ(j) - dimensions.getZ(j) / 2.0f;
                float bMaxZ = positions.getZ(j) + dimensions.getZ(j) / 2.0f;
                bool overlapX = (aMaxX >= bMinX) && (aMinX <= bMaxX);
                bool overlapY = (aMaxY >= bMinY) && (aMinY <= bMaxY);
                bool overlapZ = (aMaxZ >= bMinZ) && (aMinZ <= bMaxZ);
                if (overlapX && overlapY && overlapZ) {
                    return true;
                }
            }
        }
        return false;
    }
}

bool AoSoA8AABBExternal(const AoSoA8CollisionShape a, const AoSoA8CollisionShape b) {
    if (a.positions.getSize() != a.dimensions.getSize() || b.positions.getSize() != b.dimensions.getSize()) {
        return false;
    }
    
    int numObjectsA = a.positions.getSize();
    int numObjectsB = b.positions.getSize();
    for (int i = 0; i < numObjectsA; ++i) {
        float aMinX = positions.getX(i) - dimensions.getX(i) / 2.0f;
        float aMaxX = positions.getX(i) + dimensions.getX(i) / 2.0f;
        float aMinY = positions.getY(i);
        float aMaxY = positions.getY(i) + dimensions.getY(i);
        float aMinZ = positions.getZ(i) - dimensions.getZ(i) / 2.0f;
        float aMaxZ = positions.getZ(i) + dimensions.getZ(i) / 2.0f;
        for (int j = 0; j < numObjectsB; ++j) {
            float bMinX = positions.getX(j) - dimensions.getX(j) / 2.0f;
            float bMaxX = positions.getX(j) + dimensions.getX(j) / 2.0f;
            float bMinY = positions.getY(j);
            float bMaxY = positions.getY(j) + dimensions.getY(j);
            float bMinZ = positions.getZ(j) - dimensions.getZ(j) / 2.0f;
            float bMaxZ = positions.getZ(j) + dimensions.getZ(j) / 2.0f;
            bool overlapX = (aMaxX >= bMinX) && (aMinX <= bMaxX);
            bool overlapY = (aMaxY >= bMinY) && (aMinY <= bMaxY);
            bool overlapZ = (aMaxZ >= bMinZ) && (aMinZ <= bMaxZ);
            if (overlapX && overlapY && overlapZ) {
                return true;
            }
        }
    }
    return false;
}
