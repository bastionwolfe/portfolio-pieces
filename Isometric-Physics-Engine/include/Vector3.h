//Vector 3
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
class AoS_Vec3 {
public:
    float x;
    float y;
    float z;

    AoS_Vec3() : x(0), y(0), z(0){}
    
    AoS_Vec3(float xVal, float yVal, float zVal) : x(xVal), y(yVal), z(zVal) {}

    AoS_Vec3(const AoS_Vec3& vec3) : x(vec3.x), y(vec3.y), z(vec3.z) {}

    AoS_Vec3& operator=(const AoS_Vec3& vec3) {
        if (this != &vec3) {
            x = vec3.x;
            y = vec3.y;
            z = vec3.z;
        }
        return *this;
    }

    AoS_Vec3& operator+=(const AoS_Vec3& other) {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    AoS_Vec3& operator-=(const AoS_Vec3& other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }

    AoS_Vec3& cwiseMultiply(const AoS_Vec3& other) {
        x *= other.x;
        y *= other.y;
        z *= other.z;
        return *this;
    }

    AoS_Vec3& cwiseDivide(const AoS_Vec3& other) {
        x /= other.x;
        y /= other.y;
        z /= other.z;
        return *this;
    }

    AoS_Vec3& operator*=(float scalar) {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        return *this;
    }

    AoS_Vec3& operator/=(float scalar) {
        x /= scalar;
        y /= scalar;
        z /= scalar;
        return *this;
    }

    bool operator==(const AoS_Vec3& other) const {
        return x == other.x && y == other.y && z == other.z;
    }

    bool operator!=(const AoS_Vec3& other) const {
        return !(*this == other);
    }

    AoS_Vec3 operator-() const {
        return AoS_Vec3(-x, -y, -z);
    }

    float magnitude() const {
        return sqrt_approx(x * x + y * y + z * z);
    }

    float magnitudesqr() const {
        return (x * x + y * y + z* z);
    }

    float normalize() {
        float mag = magnitude();
        if (mag > 0.0f) {
            x /= mag;
            y /= mag;
            z /= mag;
        }
        return mag;
    }

    AoS_Vec3 normalized() const {
        float mag = magnitude();
        if (mag == 0) return AoS_Vec2(0, 0);
        return AoS_Vec3(x / mag, y / mag, z / mag);
    }

};

inline AoS_Vec3 operator+(const AoS_Vec3& lhs, const AoS_Vec3& rhs) {
    return AoS_Vec3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
}

inline AoS_Vec3 operator-(const AoS_Vec3& lhs, const AoS_Vec3& rhs) {
    return AoS_Vec3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
}

inline AoS_Vec3 operator*(const AoS_Vec3& vec, float scalar) {
    return AoS_Vec3(vec.x * scalar, vec.y * scalar, vec.z * scalar);
}

inline AoS_Vec3 operator*(float scalar, const AoS_Vec3& vec) {
    return vec * scalar;
}

inline AoS_Vec3 operator/(const AoS_Vec3& vec, float scalar) {
    return AoS_Vec3(vec.x / scalar, vec.y / scalar, vec.z / scalar);
}

float dot(const AoS_Vec3& lhs, const AoS_Vec3& rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

float distancesqr(const AoS_Vec3& lhs, const AoS_Vec3& rhs) {
    return (lhs.x - rhs.x) * (lhs.x - rhs.x) + (lhs.y - rhs.y) * (lhs.y - rhs.y) + (lhs.z - rhs.z) * (lhs.z - rhs.z);
}

float distance(const AoS_Vec3& lhs, const AoS_Vec3& rhs) {
    return sqrt_approx(distancesqr(lhs, rhs));
}

AoS_Vec3 lerp(const AoS_Vec3& start, const AoS_Vec3& end, float t) {
    return start + t * (end - start);
}

float clamp(float value, float minVal, float maxVal) {
    if (value < minVal) return minVal;
    if (value > maxVal) return maxVal;
}


//Structure of arrays
class SoA_Vec3 {
public:
    float getX(int index) const {
        return x[index];
    }

    float getY(int index) const {
        return y[index];
    }
    
    float getZ(int index) const {
        return z[index];
    }

    void setX(int index, float value) {
        x[index] = value;
    }

    void setY(int index, float value) {
        y[index] = value;
    }
    
    void setZ(int index, float value) {
        z[index] = value;
    }

    int getSize() const {
        return size;
    }

    int getCapacity() const {
        return capacity;
    }


    SoA_Vec3() : size(0), capacity(0) {}

    SoA_Vec3(int vsize, int vcapacity) : size(vsize), capacity(vcapacity) {
        x.resize(vcapacity);
        y.resize(vcapacity);
        z.resize(vcapacity);
    }

    SoA_Vec3(const SoA_Vec3& vec3) : size(vec3.size), capacity(vec3.capacity) {
        x = vec3.x;
        y = vec3.y;
        z = vec3.z;
    }

    SoA_Vec3& operator=(const SoA_Vec3& vec3) {
        if (this != &vec3) {
            x = vec3.x;
            y = vec3.y;
            z = vec3.z;
            size = vec3.size;
            capacity = vec3.capacity;
        }
        return *this;
    }

    void addVector(float xVal, float yVal, float zVal) {
        if (size >= capacity) {
            capacity = (capacity == 0) ? 1 : capacity * 2;
            x.resize(capacity);
            y.resize(capacity);
            z.resize(capacity);
        }
		x[size] = xVal;
		y[size] = yVal;
		z[size] = zVal;
		size++;
    }
    
    void addVectorAt(int index, float xVal, float yVal, float zVal) {
        if (index != size) {
            std::cout << "Invalid location";
            return;
        }
        if (size >= capacity) {
            capacity = (capacity == 0) ? 1 : capacity * 2;
            x.resize(capacity);
            y.resize(capacity);
            z.resize(capacity);
        }
    x[index] = xVal;
    y[index] = yVal;
    z[index] = zVal;
    size++;
    }
    
    void addAll(const SoA_Vec3& other) {
        int limit = (this->size < other.size) ? this->size : other.size;
        for (int i = 0; i < limit; i++) {
            this->x[i] += other.x[i];
            this->y[i] += other.y[i];
            this->z[i] += other.z[i];
        }
    }
    
    void subVectorAt(int index, float xVal, float yVal, float zVal) {
        if (index < 0 || index >= size) return;
        x[index] -= xVal;
        y[index] -= yVal;
        z[index] -= zVal;
    }

    void removeVector(int index) {
		if (index < 0 || index >= size) return;
		x[index] = x[size - 1];
		y[index] = y[size - 1];
		z[index] = z[size - 1];
		size--;
	}
	
	void setVectorAt(int index, float xVal, float yVal, float zVal) {
        if (index < 0 || index >= size) return;
        x[index] = xVal;
        y[index] = yVal;
        z[index] = zVal;
    }
    
    void scaleVectorAt(int index, float scalar) {
        if (index < 0 || index >= size) {
            std::cout << "Invalid index!";
            return;
        }
        x[index] *= scalar;
        y[index] *= scalar;
        z[index] *= scalar;
    }
    
    void negateAt(int index) {
        if (index < 0 || index >= size) {
            std::cout << "Invalid index!";
            return;
        }
        x[index] = -x[index];
        y[index] = -y[index];
        z[index] = -z[index];
    }

    float magnitude(int i) const {
        return sqrt_approx(x[i] * x[i] + y[i] * y[i] + z[i] * z[i]);
    }

    float magnitudesqr(int i) const {
        return (x[i] * x[i] + y[i] * y[i] + z[i] * z[i]);
    }

    float normalize(int i) {
        float mag = magnitude(i);
        if (mag > 0.0f) {
            x[i] /= mag;
            y[i] /= mag;
            z[i] /= mag;
        }
        return mag;
    }

    float normalized(int i) const {
        float mag = magnitude(i);
        if (mag == 0) return AoS_Vec3(0, 0, 0);
        return AoS_Vec3(x[i] / mag, y[i] / mag, z[i] / mag);
    }
    
    void normalizeAll() {
    for (int j = 0; j < size; ++j) {
        float mag = magnitude(j);
            if (mag > 0) {
                x[j] /= mag;
                y[j] /= mag;
                z[j] /= mag;
            }
        }
    }
    
    float distancesqr(int i, int j) {
        return (x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]) + (z[i] - z[j]) * (z[i] * z[j]);
    }

    float distance(int i, int j) {
        return sqrt_approx(distancesqr(i, j));
    }
    
    float dotinternal(int i, int j) {
        return x[i] * x[j] + y[i] * y[j] + z[i] * z[j];
    }

private:
    std::vector<float> x;
    std::vector<float> y;
    std::vector<float> z;
    int size;
    int capacity;
};

void scaleAll(float scalar) {
    for (int i = 0; i < size; ++i) {
        x[i] *= scalar;
        y[i] *= scalar;
        z[i] *= scalar;
    }
}

void dotAll(const SoA_Vec3& other, std::vector<float>& out) const {
    int limit = (this->size < other.getSize()) ? this->size : other.getSize();
    out.resize(limit);
    for (int i = 0; i < limit; i++) {
        out[i] = x[i] * other.x[i] + y[i] * other.y[i] + z[i] * other.z[i];
    }
}

float dotExternal(int i, const SoA_Vec3& other, int j) const {
    return x[i] * other.getX(j) + y[i] * other.getY(j) + z[i] * other.getZ(j);
}

void copyToAoS(std::vector<AoS_Vec3>& out) {
    out.resize(size);
    for (int i = 0; i < size; i++) {
        out[i].x = x[i];
        out[i].y = y[i];
        out[i].z = z[i];
    }
}

float distanceToExternal(const SoA_Vec3& other, int i) const {
    return sqrt_approx(
        (x[i] - other.getX(i)) * (x[i] - other.getX(i)) +
        (y[i] - other.getY(i)) * (y[i] - other.getY(i)) +
        (z[i] - other.getZ(i)) * (z[i] - other.getZ(i))
    );
}


//SoAoS8
struct Vec3_8 {
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
        
        float getZ(int i) const {
            if (i < 0 || i >= 8) {
                return 0.0f;
            }
            return z[i];
        }
        
        void setX(int i, float val) {
            if (i < 0 || i >= 8) return;
            x[i] = val;
        }
        
        void setY(int i, float val) {
            if (i < 0 || i >= 8) return;
            y[i] = val;
        }
        
        void setZ(int i, float val) {
            if (i < 0 || i >= 8) return;
            z[i] = val;
        }
    
    
    private:
        float x[8];
        float y[8];
        float z[8];
};

class SoAoS8 {
    public:
    /*
    Add normalize, magnitude, add, scale
    */
        
        SoAoS8() = default;
        
        SoAoS8(int initialsize) : size(intialsize) {
            int numBlocks = (initialSize + 7) / 8;
            blocks.resize(numBlocks);
            
            for (auto& block : blocks) {
                for (int i = 0; i < 8; ++i) {
                    block.x[i] = 0.00f;
                    block.y[i] = 0.00f;
                    block.z[i] = 0.00f;
                }
            }
        }
        
        SoAoS8(const SoAoS8& other) 
            : blocks(other.blocks), size(other.size) {}
            
        SoAoS8(SoAoS8&& other) noexcept
            : blocks(std::move(other.blocks)), size(other.size) {
            other.size = 0;
        }
        
        SoAoS8(const std::vector<AoS_Vec3>& input) {
            size = static_cast<int>(input.size());
            int numBlocks = (size + 7) / 8;
            blocks.resize(numBlocks);

            for (int i = 0; i < size; ++i) {
                int blockIndex = i / 8;
                int innerIndex = i % 8;
                blocks[blockIndex].x[innerIndex] = input[i].x;
                blocks[blockIndex].y[innerIndex] = input[i].y;
                blocks[blockIndex].z[innerIndex] = input[i].z;
            }
        }
        
        SoAoS8(const SoA_Vec3& soa) {
            size = soa.getSize();
            int numBlocks = (size + 7) / 8;
            blocks.resize(numBlocks);

            for (int i = 0; i < size; ++i) {
                int blockIndex = i / 8;
                int innerIndex = i % 8;
                blocks[blockIndex].x[innerIndex] = soa.getX(i);
                blocks[blockIndex].y[innerIndex] = soa.getY(i);
                blocks[blockIndex].z[innerIndex] = soa.getZ(i);
            }
        }

		int getSize() const {
    		return size;
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
        
        float getZ(int index) const {
            int blockIndex = index / 8;
            int innerIndex = index % 8;
            return blocks[blockIndex].getZ(innerIndex);
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
        
        float setZ(int index, float value) {
            int blockIndex = index / 8;
            int innerIndex = index % 8;
            return blocks[blockIndex].setZ(innerIndex, value);
            
        }
    
    private:
    
    std::vector<Vec3_8> blocks;
    int size = 0;
    
};
