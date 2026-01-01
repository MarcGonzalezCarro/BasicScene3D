#pragma once

#include "Transform.hpp"
#include <cmath>

#ifndef DEGTORAD
#define DEGTORAD 0.017453292519943295
#endif

struct Camera
{
    Transform transform;

    double fovHorizontal = 90.0 * DEGTORAD;
    double aspectRatio = 16.0 / 9.0;
    double nearPlane = 0.1;
    double farPlane = 100.0;

    Matrix4x4 GetViewMatrix() const;


    Matrix4x4 GetProjectionMatrix() const;

};
