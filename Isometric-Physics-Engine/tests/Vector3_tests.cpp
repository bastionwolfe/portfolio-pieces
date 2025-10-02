#include "Vector3.h"
#include <iostream>

int main() {
    std::cout << "=== AoS_Vec3 Tests ===\n";
    
    AoS_Vec3 a(3.0f, 4.0f, 0.0f);
    std::cout << "Vector a: (" << a.x << ", " << a.y << ", " << a.z << ")\n";
    std::cout << "Magnitude of a: " << a.magnitude() << "\n";  // Expect ~5
    std::cout << "Normalized a: ";
    AoS_Vec3 a_norm = a.normalized();
    std::cout << "(" << a_norm.x << ", " << a_norm.y << ", " << a_norm.z << ")\n";

    AoS_Vec3 b(1.0f, 2.0f, 3.0f);
    AoS_Vec3 c = a + b;
    std::cout << "a + b = (" << c.x << ", " << c.y << ", " << c.z << ")\n";

    std::cout << "Distance a to b: " << distance(a, b) << "\n";

    std::cout << "\n=== SoA_Vec3 Tests ===\n";
    
    SoA_Vec3 soa(0, 0);
    soa.addVector(3.0f, 4.0f, 0.0f);  // index 0
    soa.addVector(1.0f, 2.0f, 3.0f);  // index 1

    std::cout << "SoA size: " << soa.getSize() << "\n";
    std::cout << "Vector at index 0: (" << soa.getX(0) << ", " << soa.getY(0) << ", " << soa.getZ(0) << ")\n";
    std::cout << "Vector at index 1: (" << soa.getX(1) << ", " << soa.getY(1) << ", " << soa.getZ(1) << ")\n";

    float mag0 = soa.magnitude(0);
    std::cout << "Magnitude at index 0: " << mag0 << "\n";  // Expect ~5

    soa.normalizeAll();

    std::cout << "After normalization, vector at index 0: ("
              << soa.getX(0) << ", " << soa.getY(0) << ", " << soa.getZ(0) << ")\n";

    float dist01 = soa.distance(0, 1);
    std::cout << "Distance between vectors 0 and 1: " << dist01 << "\n";

    std::cout << "\n=== AoSoA8 Tests ===\n";

    std::vector<AoS_Vec3> vecs = {a, b};
    AoSoA8 aosoa(vecs);

    std::cout << "AoSoA size: " << aosoa.getSize() << "\n";

    for (int i = 0; i < aosoa.getSize(); ++i) {
        std::cout << "AoSoA vector " << i << ": ("
                  << aosoa.getX(i) << ", "
                  << aosoa.getY(i) << ", "
                  << aosoa.getZ(i) << ")\n";
    }

    // Modify a value and read back
    aosoa.setX(0, 7.0f);
    std::cout << "After setting aosoa x[0] to 7, vector 0: ("
              << aosoa.getX(0) << ", "
              << aosoa.getY(0) << ", "
              << aosoa.getZ(0) << ")\n";

    return 0;
}
