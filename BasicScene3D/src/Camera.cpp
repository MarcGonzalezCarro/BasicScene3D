#include "Camera.hpp"
#include <cmath>

Matrix4x4 Camera::GetViewMatrix() const
{
    // La View Matrix es la inversa de la transform de la cámara
    // (no debe tener escala)
    return transform.GetLocalMatrix().InverseTR();
}

Matrix4x4 Camera::GetProjectionMatrix() const
{
    const double halfWidth = nearPlane * std::tan(fovHorizontal * 0.5);
    const double halfHeight = halfWidth / aspectRatio;

    const double left = -halfWidth;
    const double right = halfWidth;
    const double bottom = -halfHeight;
    const double top = halfHeight;

    return Matrix4x4::Perspective(left, right, bottom, top, nearPlane, farPlane);
}