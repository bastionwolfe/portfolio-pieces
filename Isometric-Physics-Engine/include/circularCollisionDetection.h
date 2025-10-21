// circular collison detection
#include "Vector3.h"

struct AoSSphere { 
    AoS_Vec3 AoSCir
    float radius;
    
    AoSSphere(float x, float y, float z, float radi) {
        radius = radi;
        AoSCir = AoS_Vec3(x, y, z);
    }
    
    AoSSphere(const AoSSphere& Sphere) {
        radius = AoSSphere.radius;
        AoSCir = AoSSphere.AoSCir;
    }
    
    AoSSphere operator =(const AoSSphere& Sphere) {
        if (this != Sphere) {
            radius = AoSSphere.radius;
            AoSCir = AoSSphere.AoSCir;
        }
        return *this;
    }

}

bool isColliding(const Sphere& s1, const Sphere& s2) {
    float dx = s2.AoSSphere.x - s1.AoSSphere.x;
    float dy = s2.AoSSphere.y - s1.AoSSphere.y;
    float dz = s2.AoSSphere.z - s1.AoSSphere.z;
    float distanceSquared = dx * dx + dy * dy + dz * dz;
    float radiiSumSquared = (s1.radius + s2.radius) * (s1.radius + s2.radius);
    return distanceSquared <= radiiSumSquared;
}


struct SoASphere {
    SoA_Vec3 centers;
    std::vector<float> radii;

    SoASphere(int size, int capacity) {
        Centers = SoA_Vec3(size, capacity);
        Radii.resize(capacity);
    }

    SoASphere() {
        Centers = SoA_Vec3();
        Radii = std::vector<float>();
    }

    SoASphere(const SoASphere& Sphere) {
        Centers = Sphere.Centers;
        Radii = Sphere.Radii;
    }

    SoASphere operator=(const SoASphere& Sphere) {
        if (this != &Sphere) {
            Centers = Sphere.Centers;
            Radii = Sphere.Radii;
        }
        return *this;
    }

    void addSphere(float x, float y, float z, float r) {
        centers.addVector(x, y, z);
        if (radii.size() <= centers.getSize()) {
            int newCap = std::max(2 * (int)radii.size(), 1);
            radii.resize(newCap);
        }
        radii[centers.getSize() - 1] = r;
    }

    int getSize() const {
        return centers.getSize();
    }
};

bool isColliding(const SoASphere& spheres, int i, int j) {
    float dx = spheres.centers.getX(j) - spheres.centers.getX(i);
    float dy = spheres.centers.getY(j) - spheres.centers.getY(i);
    float dz = spheres.centers.getZ(j) - spheres.centers.getZ(i);
    float distanceSquared = dx * dx + dy * dy + dz * dz;
    float radiiSum = spheres.radii[i] + spheres.radii[j];
    return distanceSquared <= radiiSum * radiiSum;
}

struct Radius_8 {
    float r[8];

    float get(int i) const {
        if (i < 0 || i >= 8) return 0.0f;
        return r[i];
    }

    void set(int i, float val) {
        if (i < 0 || i >= 8) return;
        r[i] = val;
    }
};

struct AoSoA8Sphere {
    AoSoA8 centers;
    std::vector<Radius_8> radiusBlocks;
    int size;

    AoSoA8Sphere(int initialSize) {
        size = initialSize;
        int numBlocks = (initialSize + 7) / 8;
        radiusBlocks.resize(numBlocks);
        centers = AoSoA8(initialSize);

        for (int i = 0; i < numBlocks; ++i) {
            for (int j = 0; j < 8; ++j) {
                radiusBlocks[i].r[j] = 0.0f;
            }
        }
    }

    AoSoA8Sphere(float x, float y, float z, float r) {
        size = 1;
        radiusBlocks.resize(1);
        centers = AoSoA8(1);
        centers.setX(0, x);
        centers.setY(0, y);
        centers.setZ(0, z);
        radiusBlocks[0].r[0] = r;
    }

    AoSoA8Sphere(const AoSoA8Sphere& other) {
        centers = other.centers;
        radiusBlocks = other.radiusBlocks;
        size = other.size;
    }

    AoSoA8Sphere operator=(const AoSoA8Sphere& other) {
        if (this != &other) {
            centers = other.centers;
            radiusBlocks = other.radiusBlocks;
            size = other.size;
        }
        return *this;
    }

    int getSize() const {
        return size;
    }

    float getRadius(int index) const {
        int blockIndex = index / 8;
        int innerIndex = index % 8;
        return radiusBlocks[blockIndex].get(innerIndex);
    }

    void setRadius(int index, float value) {
        int blockIndex = index / 8;
        int innerIndex = index % 8;
        radiusBlocks[blockIndex].set(innerIndex, value);
    }

    void addSphere(float x, float y, float z, float r) {
        int index = size;
        int blockIndex = index / 8;
        int innerIndex = index % 8;

        if (innerIndex == 0) {
            Vec3_8 newVecBlock;
            Radius_8 newRadBlock;

            for (int i = 0; i < 8; ++i) {
                newVecBlock.setX(i, 0.0f);
                newVecBlock.setY(i, 0.0f);
                newVecBlock.setZ(i, 0.0f);
                newRadBlock.set(i, 0.0f);
            }

            centers.blocks.push_back(newVecBlock);
            radiusBlocks.push_back(newRadBlock);
        }

        centers.setX(index, x);
        centers.setY(index, y);
        centers.setZ(index, z);
        radiusBlocks[blockIndex].set(innerIndex, r);

        size++;
    }
};

bool iscolliding(const AoSoA8Sphere& spheres, int i, int j) {
    float dx = spheres.centers.getX(j) - spheres.centers.getX(i);
    float dy = spheres.centers.getY(j) - spheres.centers.getY(i);
    float dz = spheres.centers.getZ(j) - spheres.centers.getZ(i);

    float distanceSquared = dx * dx + dy * dy + dz * dz;

    float r1 = spheres.getRadius(i);
    float r2 = spheres.getRadius(j);
    float radiiSum = r1 + r2;

    return distanceSquared <= radiiSum * radiiSum;
}
