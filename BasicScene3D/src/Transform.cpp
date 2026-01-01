#include "Transform.hpp"

Matrix4x4 Transform::GetLocalMatrix() const
{
    return Matrix4x4::FromTRS(position, rotation, scale);
}

void Transform::SetEulerRotation(const Vec3& euler)
{
    eulerRotation = euler;

    // Usamos el orden ZYX (yaw, pitch, roll) que implementa tu Quat
    rotation = Quat::FromEulerZYX(
        euler.x,   // yaw
        euler.y,   // pitch
        euler.z    // roll
    );
}