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

struct AoSoA8Sphere {
    
}
