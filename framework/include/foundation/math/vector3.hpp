#pragma once

namespace Sampo
{
    class Vector2
    {
    public:
        float x, y;
    public:
        Vector2(float x, float y) 
        { 
            this->x = x; this->y = y; 
        }

        // Operator Overloads //
        Vector2 operator+ (float addition)          { return Vector2{ x + addition, y + addition }; }
        Vector2 operator- (float addition)          { return Vector2{ x - addition, y - addition }; }
        Vector2 operator* (float scalar)            { return Vector2{ x * scalar,   y * scalar   }; }
        Vector2 operator/ (float scalar)            { return Vector2{ x / scalar,   y / scalar }; }
        Vector2 operator+ (const Vector2& other)    { return Vector2{ x + other.x,  y + other.y  }; }
        Vector2 operator- (const Vector2& other)    { return Vector2{ x - other.x,  y - other.y }; }
        Vector2 operator* (const Vector2& other)    { return Vector2{ x * other.x,  y * other.y  }; }
        Vector2 operator/ (const Vector2& other)    { return Vector2{ x / other.x,  y / other.y }; }

        void operator+= (float addition)            { x += addition; y += addition; }

        // Operations //
        inline void Inverse() 
        {
            x = -x; 
            y = -y;
        }
        inline void Inverse(Vector2& out)
        {
            out.x = -out.x; 
            out.y = -out.y;
        }

        inline Vector2 Inverse(const Vector2& v) { return Vector2{ -v.x, -v.y }; }
        
    };
    
    class Vector3
    {
    public:
        float x, y, z;
    public:
        Vector3(float x, float y, float z) { this->x = x; this->y = y; this->z = z; }
    };
}