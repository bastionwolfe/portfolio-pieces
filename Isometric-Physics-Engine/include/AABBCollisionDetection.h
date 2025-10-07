//AABB collision detection

class AoScollisionshape{
    AoS_Vec3 position;
    float width;
    float depth;
    float height;
    
    vec3 getMin() const {
        return Vec3{
            position.x - width  / 2.0f,
            position.y,
            position.z - depth / 2.0f
        };
    }
    Vec3 getMax() const {
        return Vec3{
            position.x + width  / 2.0f,
            position.y + height,
            position.z + depth / 2.0f
        };
    }
}

bool AoSAABBOverlap(const AoSCollisionShape& a, const AoSCollisionShape& b) {
    Vec3 aMin = a.getMin();
    Vec3 aMax = a.getMax();
    Vec3 bMin = b.getMin();
    Vec3 bMax = b.getMax();

    return (
        aMax.x >= bMin.x && aMin.x <= bMax.x &&
        aMax.y >= bMin.y && aMin.y <= bMax.y &&
        aMax.z >= bMin.z && aMin.z <= bMax.z
    );
}
