//Vector 2
// I will be implementing an AoS and SoA system for this physics engine. 
// I might add an AoSoA function later but for now lets focus on the top two
//    -- Checklist --
//1. AoS
//2. SoA
//3. AoSoA
//4. implement SIMD 

/*

Utility functions: Distance between two vectors. Maybe angle between vectors if relevant.
Clamp, lerp (linear interpolation) if useful for your game physics.

Performance considerations: Keep all functions small and inline-able. Pass vectors by value or const reference based on size and usage.
Avoid unnecessary copying or heap allocations.

Testing: Write unit tests for each operation (add, subtract, dot, length, normalize). Verify edge cases (zero vector normalization, etc.).*/
#pragma once
#include <vector>

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

    bool operator==(const AoS_Vec2& other) const {
        return x == other.x && y == other.y;
    }

    bool operator!=(const AoS_Vec2& other) const {
        return !(*this == other);
    }

    AoS_Vec2 operator-() const {
        return AoS_Vec2(-x, -y);
    }

    float magnitude() const {
        return sqrt_approx(x * x + y * y);
    }

    float magnitudesqr() const {
        return (x * x + y * y);
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

float distancesqr(const AoS_Vec2& lhs, const AoS_Vec2& rhs) {
    return sqrt_approx((lhs.x - rhs.x) * (lhs.x - rhs.x) + (lhs.y - rhs.y) * (lhs.y - rhs.y));
}

float distance(const AoS_Vec2& lhs, const AoS_Vec2& rhs) {
    return (lhs.x - rhs.x) * (lhs.x - rhs.x) + (lhs.y - rhs.y) * (lhs.y - rhs.y);
}

float lerp(const Aos_Vec2& start, const Aos_Vec2& end, float t) {
    return start + t * (end - start);
}

float clamp(float value, float minVal, float maxVal) {
    if (value < minVal) return minVal;
    if (value > maxVal) return maxVal;
}


//Structure of arrays
class SoA_Vec2 {
public:
    float getX(int index) const {
        return x[index];
    }

    float getY(int index) const {
        return y[index];
    }

    void setX(int index, float value) {
        x[index] = value;
    }

    void setY(int index, float value) {
        y[index] = value;
    }

    int getSize() const {
        return size;
    }

    int getCapacity() const {
        return capacity;
    }


    SoA_Vec2() : size(0), capacity(0) {}

    SoA_Vec2(int vsize, int vcapacity) : size(vsize), capacity(vcapacity) {
        x.resize(vcapacity);
        y.resize(vcapacity);
    }

    SoA_Vec2(const SoA_Vec2& vec2) : size(vec2.size), capacity(vec2.capacity) {
        x = vec2.x;
        y = vec2.y;
    }

    SoA_Vec2& operator=(const SoA_Vec2& vec2) {
        if (this != &vec2) {
            x = vec2.x;
            y = vec2.y;
            size = vec2.size;
            capacity = vec2.capacity;
        }
        return *this;
    }

    void addVector(float xVal, float yVal) {
        if (size >= capacity) {
            capacity = (capacity == 0) ? 1 : capacity * 2;
            x.resize(capacity);
            y.resize(capacity);
        }
		x[size] = xVal;
		y[size] = yVal;
		size++;
    }

    void removeVector(int index) {
		if (index < 0 || index >= size) return;
		x[index] = x[size - 1];
		y[index] = y[size - 1];
		size--;
	}

    float magnitude(int i) const {
        return sqrt_approx(x[i] * x[i] + y[i] * y[i]);
    }

    float magnitudesqr(int i) const {
        return (x[i] * x[i] + y[i] * y[i]);
    }

    float normalize(int i) {
        float mag = magnitude(i);
        if (mag > 0.0f) {
            x[i] /= mag;
            y[i] /= mag;
        }
        return mag;
    }

    AoS_Vec2 normalized(int i) const {
        float mag = magnitude(i);
        if (mag == 0) return AoS_Vec2(0, 0);
        return AoS_Vec2(x[i] / mag, y[i] / mag);
    }

private:
    std::vector<float> x;
    std::vector<float> y;
    int size;
    int capacity;
};


