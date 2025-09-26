//Vector 2
// I will be implementing an AoS and SoA system for this physics engine. 
// I might add an AoSoA function later but for now lets focus on the top two
//    -- Checklist --
//1. AoS
//2. SoA
//3. AoSoA
//4. implement SIMD 

/*
Operator overloads: Overload arithmetic operators (+, -, *, /) for syntactic sugar. 
Compound assignment operators (+=, -=, *=, /=). Comparison operators if needed (==, !=). 

Utility functions: Distance between two vectors. Maybe angle between vectors if relevant. 
Clamp, lerp (linear interpolation) if useful for your game physics. 

Performance considerations: Keep all functions small and inline-able. Pass vectors by value or const reference based on size and usage.
Avoid unnecessary copying or heap allocations. 

Testing: Write unit tests for each operation (add, subtract, dot, length, normalize). Verify edge cases (zero vector normalization, etc.).*/

//square root finder
float sqrt_approx(float number) {
    if (number <= 0) return 0;

    float x = number;
    float y = 1.0f;
    const float epsilon = 0.00001f;  // precision

    while (x - y > epsilon) {
        x = (x + y) * 0.5f;
        y = number / x;
    }
    return x;
}

//Array of structures
class AoS_Vec2 {
public:
    float x;
    float y;

    AoS_Vec2() : x(0), y(0) {}

    AoS_Vec2(float xVal, float yVal) : x(xVal), y(yVal) {}

    AoS_Vec2(const AoS_Vec2& vec2) : x(vec2.x), y(vec2.y) {}

    AoS_Vec2& operator=(const AoS_Vec2& vec2) {
        if (this != &vec2) {
            x = vec2.x;
            y = vec2.y;
        }
        return *this;
    }

    AoS_Vec2& operator+=(const AoS_Vec2& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    AoS_Vec2& operator-=(const AoS_Vec2& other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    AoS_Vec2& cwiseMultiply(const AoS_Vec2& other) {
        x *= other.x;
        y *= other.y;
        return *this;
    }

    AoS_Vec2& cwiseDivide(const AoS_Vec2& other) {
        x /= other.x;
        y /= other.y;
        return *this;
    }

    AoS_Vec2& operator*=(float scalar) {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    AoS_Vec2& operator/=(float scalar) {
        x /= scalar;
        y /= scalar;
        return *this;
    }

    AoS_Vec2 operator-() const {
        return AoS_Vec2(-x, -y);
    }
    
    float magnitude() const {
        return sqrt_approx(x*x + y*y);
    }
    
    float magnitudesqr() const {
        return (x*x + y*y);
    }
    
    float normalize() {
        float mag = magnitude();
        if (mag > 0.0f) {
            x /= mag;
            y /= mag;
        }
        return mag;
    }
    
    AoS_Vec2 normalized() const {
        float mag = magnitude();
        if (mag == 0) return AoS_Vec2(0, 0);
        return AoS_Vec2(x / mag, y / mag);
    }
    
    bool isequal(const AoS_Vec2& other) {
        if (AoS_Vec2& == other) {
            return true;
        }
        else {
            return false;
        }
    }
    
    bool isdifferent(const AoS_Vec2& other) {
        if (AoS_Vec2& != other) {
            return true;
        }
        else {
            return false;
        }
    }
    
};

inline AoS_Vec2 operator+(const AoS_Vec2& lhs, const AoS_Vec2& rhs) {
    return AoS_Vec2(lhs.x + rhs.x, lhs.y + rhs.y);
}

inline AoS_Vec2 operator-(const AoS_Vec2& lhs, const AoS_Vec2& rhs) {
    return AoS_Vec2(lhs.x - rhs.x, lhs.y - rhs.y);
}

inline AoS_Vec2 operator*(const AoS_Vec2& vec, float scalar) {
    return AoS_Vec2(vec.x * scalar, vec.y * scalar);
}

inline AoS_Vec2 operator*(float scalar, const AoS_Vec2& vec) {
    return vec * scalar;
}

inline AoS_Vec2 operator/(const AoS_Vec2& vec, float scalar) {
    return AoS_Vec2(vec.x / scalar, vec.y / scalar);
}

float dot(const AoS_Vec2& lhs, const AoS_Vec2& rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y;
}
