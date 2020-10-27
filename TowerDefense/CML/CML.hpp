#pragma once

#include <cmath>
#include <random>

namespace CML
{
const float Pi = 3.1415926535f;

inline float ToDegrees(float radians) noexcept { return radians * 180.f / Pi; }

inline bool CloseToZero(float value, float epsilon = 0.001f) noexcept { return fabs(value) < epsilon; }

inline float Cos(float angle) { return cosf(angle); }

inline float Sin(float angle) { return sinf(angle); }

class Vector2D
{
public:
    float X;
    float Y;
    
    Vector2D(float x, float y) : X(x), Y(y) {}
    
    friend Vector2D operator+(const Vector2D& a, const Vector2D& b) { return Vector2D(a.X + b.X, a.Y - b.Y); }
    
    friend Vector2D operator-(const Vector2D& a, const Vector2D& b) { return Vector2D(a.X - b.X, a.Y - b.Y); }
    
    friend Vector2D operator*(const Vector2D& a, const Vector2D& b) { return Vector2D(a.X * b.X, a.Y * b.Y); }
    
    friend Vector2D operator*(const Vector2D& vector, float scalar) { return Vector2D(vector.X * scalar, vector.Y * scalar); }
    
    friend Vector2D operator/(const Vector2D& vector, float scalar) { return Vector2D(vector.X / scalar, vector.Y / scalar); }
    
    Vector2D& operator+=(const Vector2D& right) { X += right.X; Y += right.Y; return *this; }
    
    Vector2D& operator-=(const Vector2D& right) { X -= right.X; Y -= right.Y; return *this; }
    
    float LengthSquared() const noexcept { return X * X + Y * Y; }
};

class Random
{
public:
    static void Init();
    
    static void Seed(unsigned int seed);
    
    static float GetRandomFloat(float min, float max);
    
    static Vector2D GetRandomVector2D(const Vector2D& min, const Vector2D& max);
    
private:
    static std::mt19937 sGenerator;
};
}
