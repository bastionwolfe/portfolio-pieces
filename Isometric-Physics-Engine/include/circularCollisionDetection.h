// circular collison detection

struct Sphere { //for testing purposes
    float x;
    float y;
    float z;
    float radius;
}

bool iscolliding(const Sphere& s1, const Sphere& s2) {
    float dx = s2.x - s1.x;
    float dy = s2.y - s1.y;
    float dz = s2.z - s1.z;
    float distanceSquared = dx * dx + dy * dy + dz * dz;
    float radiiSumSquared = (s1.radius + s2.radius) * (s1.radius + s2.radius);
    return distanceSquared <= radiiSumSquared;
}
