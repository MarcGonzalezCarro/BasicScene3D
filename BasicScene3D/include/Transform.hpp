#pragma once

#include "Matrix4x4.hpp"
#include "Quat.hpp"
#include "Matrix3x3.hpp"

struct Transform
{
    Vec3 position{ 0.0, 0.0, 0.0 };
    Vec3 scale{ 1.0, 1.0, 1.0 };

    
    Quat rotation;

    
    Vec3 eulerRotation{ 0.0, 0.0, 0.0 };

    Matrix4x4 GetLocalMatrix() const;

    void SetEulerRotation(const Vec3& euler);
};