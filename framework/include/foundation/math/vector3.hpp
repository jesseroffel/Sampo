#pragma once

namespace Sampo
{
    class Vector2
    {
    public:
        float x, y;
    public:
        // Constructors
        Vector2(float value) 
        {
            this->x = value;
            this->y = value;
        }

        Vector2(float x, float y) 
        { 
            this->x = x; 
            this->y = y; 
        }
        ~Vector2();

        // Operator Overloads //
        Vector2 operator+ (float addition)          { return { x + addition, y + addition }; }
        Vector2 operator- (float addition)          { return { x - addition, y - addition }; }
        Vector2 operator* (float scalar)            { return { x * scalar,   y * scalar }; }
        Vector2 operator/ (float scalar)            { return { x / scalar,   y / scalar }; }
        Vector2 operator+ (const Vector2& other)    { return { x + other.x,  y + other.y }; }
        Vector2 operator- (const Vector2& other)    { return { x - other.x,  y - other.y }; }
        Vector2 operator* (const Vector2& other)    { return { x * other.x,  y * other.y }; }
        Vector2 operator/ (const Vector2& other)    { return { x / other.x,  y / other.y }; }

        void operator+= (float addition)            { x += addition; y += addition; }

        // Operations //
        inline bool Zero() { return (x == 0 && y == 0); }


        inline Vector2 Inverse() 
        {
            return { -x, -y };
        }

        inline float Magnitude()
        {
            float ax = std::fabs(x);
            float ay = std::fabs(y);
            return std::sqrt((ax * ax) + (ay * ay));
        }


        inline Vector2 Normalised()
        {
            if (Zero())
            {
                return Vector2{0};
            }
            auto mag = Magnitude();

            return { (x / mag), (y / mag) };
        }

        inline void Normalise()
        {
            if (!Zero())
            {
                auto mag = Magnitude();

                x = (x / mag);
                y = (y / mag);
            }
        }

        inline Vector2 DotProduct(const Vector2& other)
        {
            return { (x * other.x), (y * other.y) };
        }


    };
    
    class Vector3
    {
    public:
        float x, y, z;
    public:
        Vector3(float x, float y, float z) { this->x = x; this->y = y; this->z = z; }
    };
}