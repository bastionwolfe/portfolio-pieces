//Vector 2
// I will be implementing an AoS and SoA system for this physics engine. 
// I might add an AoSoA function later but for now lets focus on the top two
//    -- Checklist --
//1. X AoS
//2. X SoA
//3. AoSoA - (Note: At this time AoSoA will only have setters and getters full functions will come later due to time constraints)

/*
                  Function defonition help:
 1.
*/
#pragma once
#include <vector>
#include <iostream>

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
    return (lhs.x - rhs.x) * (lhs.x - rhs.x) + (lhs.y - rhs.y) * (lhs.y - rhs.y);
}

float distance(const AoS_Vec2& lhs, const AoS_Vec2& rhs) {
    return sqrt_approx(distancesqr(lhs, rhs));
}

AoS_Vec2 lerp(const AoS_Vec2& start, const AoS_Vec2& end, float t) {
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
    
    void addVectorAt(int index, float xVal, float yVal) {
        if (index != size) {
            std::cout << "Invalid location";
            return;
        }
        if (size >= capacity) {
            capacity = (capacity == 0) ? 1 : capacity * 2;
            x.resize(capacity);
            y.resize(capacity);
        }
    x[index] = xVal;
    y[index] = yVal;
    size++;
    }
    
    void addAll(const SoA_Vec2& other) {
        int limit = (this->size < other.size) ? this->size : other.size;
        for (int i = 0; i < limit; i++) {
            this->x[i] += other.x[i];
            this->y[i] += other.y[i];
        }
    }
    
    void subVectorAt(int index, float xVal, float yVal) {
        if (index < 0 || index >= size) return;
        x[index] -= xVal;
        y[index] -= yVal;
    }

    void removeVector(int index) {
		if (index < 0 || index >= size) return;
		x[index] = x[size - 1];
		y[index] = y[size - 1];
		size--;
	}
	
	void setVectorAt(int index, float xVal, float yVal) {
        if (index < 0 || index >= size) return;
        x[index] = xVal;
        y[index] = yVal;
    }
    
    void scaleVectorAt(int index, float scalar) {
        if (index < 0 || index >= size) {
            std::cout << "Invalid index!";
            return;
        }
        x[index] *= scalar;
        y[index] *= scalar;
    }
    
    void negateAt(int index) {
        if (index < 0 || index >= size) {
            std::cout << "Invalid index!";
            return;
        }
        x[index] = -x[index];
        y[index] = -y[index];
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

    float normalized(int i) const {
        float mag = magnitude(i);
        if (mag == 0) return AoS_Vec2(0, 0);
        return AoS_Vec2(x[i] / mag, y[i] / mag);
    }
    
    void normalizeAll() {
    for (int j = 0; j < size; ++j) {
        float mag = magnitude(j);
            if (mag > 0) {
                x[j] /= mag;
                y[j] /= mag;
            }
        }
    }
    
    float distancesqr(int i, int j) {
        return (x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]);
    }

    float distance(int i int j) {
        return sqrt_approx(distancesqr(i, j));
    }
    
    float dotinternal(int i, int j) {
        return x[i] * x[j] + y[i] * y[j];
    }

private:
    std::vector<float> x;
    std::vector<float> y;
    int size;
    int capacity;
};

void scaleAll(float scalar) {
    for (int i = 0; i < size; ++i) {
        x[i] *= scalar;
        y[i] *= scalar;
    }
}

void dotAll(const SoA_Vec2& other, std::vector<float>& out) const {
    int limit = (this->size < other.getSize()) ? this->size : other.getSize();
    out.resize(limit);
    for (int i = 0; i < limit; i++) {
        out[i] = x[i] * other.x[i] + y[i] * other.y[i];
    }
}

float dotExternal(int i, const SoA_Vec2& other, int j) const {
    return x[i] * other.getX(j) + y[i] * other.getY(j);
}

void copyToAoS(std::vector<AoS_Vec2>& out) {
    out.resize(size);
    for (int i = 0; i < size; i++) {
        out[i].x = x[i];
        out[i].y = y[i];
    }
}

float distanceToExternal(const SoA_Vec2& other, int i) const {
    return sqrt_approx((x[i] - other.getX(i)) * (x[i] - other.getX(i)) + (y[i] - other.getY(i)) * (y[i] - other.getY(i)));
}


//SoAoS8
struct Vec2_8 {
    public:
    /*
    Add normalize, magnitude, add, scale
    */
    
        float getX(int i) const {
            if (i < 0 || i >= 8) {
                return 0.0f;
            }
            return x[i];
        }   
        
        float getY(int i) const {
            if (i < 0 || i >= 8) {
                return 0.0f;
            }
            return y[i];
        }
        
        float setX(int i, float val) {
            if (i < 0 || i >=8) {
                return 0.0f;
            }
            x[i] = val;
        }
        
        float setY(int i, float val) {
            if (i < 0 || i >=8) {
                return 0.0f;
            }
            y[i] = val;
        }
    
    
    private:
        float x[8];
        float y[8];
}

class SoAoS8 {
    public:
    /*
    Add normalize, magnitude, add, scale
    */
        std::vector<Vec2_8> blocks;
        int size = 0;
        
        SoAoS8() = default;
        
        SoAoS8(int initialsize) : size(intiialsize) {
            int numBlocks = (initialSize + 7) 8;
            blocks.resize(numBlocks);
            
            for (auto& block : blocks) {
                for (int i - 0; i < 8; ++i) {
                    block.x[i] = 0.00f;
                    block.y[i] = 0.00f;
                }
            }
        }
        
        SoAoS8(const SoAoS8& other) 
            : blocks(other.blocks), size(other.size) {}
            
        SoAoS8(SoAoS8&& other) noexcept
            : blocks(std::move(other.blocks)), size(other.size) {
            other.size = 0;
        }
        
        SoAoS8(const std::vector<AoS_Vec2>& input) {
            size = static_cast<int>(input.size());
            int numBlocks = (size + 7) / 8;
            blocks.resize(numBlocks);

            for (int i = 0; i < size; ++i) {
                int blockIndex = i / 8;
                int innerIndex = i % 8;
                blocks[blockIndex].x[innerIndex] = input[i].x;
                blocks[blockIndex].y[innerIndex] = input[i].y;
            }
        }
        
        SoAoS8(const SoA_Vec2& soa) {
            size = soa.getSize();
            int numBlocks = (size + 7) / 8;
            blocks.resize(numBlocks);

            for (int i = 0; i < size; ++i) {
                int blockIndex = i / 8;
                int innerIndex = i % 8;
                blocks[blockIndex].x[innerIndex] = soa.getX(i);
                blocks[blockIndex].y[innerIndex] = soa.getY(i);
            }
        }
        
        float getX(int index) const {
            int blockIndex = index / 8;
            int innerIndex = index % 8;
            return blocks[blockIndex].getX(innerIndex);
        }
        
        float getY(int index) const {
            int blockIndex = index / 8;
            int innerIndex = index % 8;
            return blocks[blockIndex].getY(innerIndex);
        }
        
        float setX(int index, float value) {
            int blockIndex = index / 8;
            int innerIndex = index % 8;
            return blocks[blockIndex].setX(innerIndex, value);
            
        }
        
        float setY(int index, float value) {
            int blockIndex = index / 8;
            int innerIndex = index % 8;
            return blocks[blockIndex].setY(innerIndex, value);
            
        }
    
    private:
    
};
