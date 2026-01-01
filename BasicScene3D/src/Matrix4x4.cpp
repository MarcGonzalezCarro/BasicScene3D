#include "Matrix4x4.hpp"
#include <cmath>
#include <stdexcept>

#define TOL 1e-6

Matrix4x4 Matrix4x4::Identity()
{
    Matrix4x4 I;
    I.At(0, 0) = 1; I.At(1, 1) = 1; I.At(2, 2) = 1; I.At(3, 3) = 1;
    return I;
}

Matrix4x4 Matrix4x4::Multiply(const Matrix4x4& B) const
{
    Matrix4x4 C{};
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            double sum = 0.0;
            for (int k = 0; k < 4; ++k) {
                sum += At(i, k) * B.At(k, j);
            }
            C.At(i, j) = sum;
        }
    }
    return C;
}

Vec4 Matrix4x4::Multiply(const Vec4& v) const
{
    Vec4 res;
    res.x = At(0, 0) * v.x + At(0, 1) * v.y + At(0, 2) * v.z + At(0, 3) * v.w;
    res.y = At(1, 0) * v.x + At(1, 1) * v.y + At(1, 2) * v.z + At(1, 3) * v.w;
    res.z = At(2, 0) * v.x + At(2, 1) * v.y + At(2, 2) * v.z + At(2, 3) * v.w;
    res.w = At(3, 0) * v.x + At(3, 1) * v.y + At(3, 2) * v.z + At(3, 3) * v.w;
    return res;
}

// --------------------------------------------------------------------------
// TODO LAB 3
// --------------------------------------------------------------------------

bool Matrix4x4::IsAffine() const
{
    if (this->At(3, 0) != 0) return false;
    if (this->At(3, 1) != 0) return false;
    if (this->At(3, 2) != 0) return false;
    if (this->At(3, 3) != 1) return false;

    return true;
}

Vec3 Matrix4x4::TransformPoint(const Vec3& p) const
{
    Vec4 temp;
    Vec3 res;

    temp.x = p.x;
    temp.y = p.y;
    temp.z = p.z;
    temp.w = 1;

    temp = Multiply(temp);

    res.x = temp.x;
    res.y = temp.y;
    res.z = temp.z;

    return res;
}

Vec3 Matrix4x4::TransformVector(const Vec3& v) const
{
    Vec4 temp;
    Vec3 res;

    temp.x = v.x;
    temp.y = v.y;
    temp.z = v.z;
    temp.w = 0;

    temp = Multiply(temp);

    res.x = temp.x;
    res.y = temp.y;
    res.z = temp.z;

    return res;
}

Matrix4x4 Matrix4x4::Translate(const Vec3& t)
{
    Matrix4x4 M;
    M.At(0, 0) = 1;
    M.At(0, 1) = 0;
    M.At(0, 2) = 0;
    M.At(0, 3) = t.x;
    M.At(1, 0) = 0;
    M.At(1, 1) = 1;
    M.At(1, 2) = 0;
    M.At(1, 3) = t.y;
    M.At(2, 0) = 0;
    M.At(2, 1) = 0;
    M.At(2, 2) = 1;
    M.At(2, 3) = t.z;
    M.At(3, 0) = 0;
    M.At(3, 1) = 0;
    M.At(3, 2) = 0;
    M.At(3, 3) = 1;

    return M;
}

Matrix4x4 Matrix4x4::Scale(const Vec3& s)
{
    Matrix4x4 M;

    M.At(0, 0) = s.x;
    M.At(0, 1) = 0;
    M.At(0, 2) = 0;
    M.At(0, 3) = 0;
    M.At(1, 0) = 0;
    M.At(1, 1) = s.y;
    M.At(1, 2) = 0;
    M.At(1, 3) = 0;
    M.At(2, 0) = 0;
    M.At(2, 1) = 0;
    M.At(2, 2) = s.z;
    M.At(2, 3) = 0;
    M.At(3, 0) = 0;
    M.At(3, 1) = 0;
    M.At(3, 2) = 0;
    M.At(3, 3) = 1;
    return M;
}

Matrix4x4 Matrix4x4::Rotate(const Matrix3x3& R)
{
    Matrix4x4 M;
    M.At(0, 0) = R.At(0, 0);
    M.At(0, 1) = R.At(0, 1);
    M.At(0, 2) = R.At(0, 2);
    M.At(0, 3) = 0;
    M.At(1, 0) = R.At(1, 0);
    M.At(1, 1) = R.At(1, 1);
    M.At(1, 2) = R.At(1, 2);
    M.At(1, 3) = 0;
    M.At(2, 0) = R.At(2, 0);
    M.At(2, 1) = R.At(2, 1);
    M.At(2, 2) = R.At(2, 2);
    M.At(2, 3) = 0;
    M.At(3, 0) = 0;
    M.At(3, 1) = 0;
    M.At(3, 2) = 0;
    M.At(3, 3) = 1;
    return M;
}

Matrix4x4 Matrix4x4::Rotate(const Quat& q)
{
    Matrix4x4 M;
    Matrix3x3 R;

    R = q.ToMatrix3x3();

    M.At(0, 0) = R.At(0, 0);
    M.At(0, 1) = R.At(0, 1);
    M.At(0, 2) = R.At(0, 2);
    M.At(0, 3) = 0;
    M.At(1, 0) = R.At(1, 0);
    M.At(1, 1) = R.At(1, 1);
    M.At(1, 2) = R.At(1, 2);
    M.At(1, 3) = 0;
    M.At(2, 0) = R.At(2, 0);
    M.At(2, 1) = R.At(2, 1);
    M.At(2, 2) = R.At(2, 2);
    M.At(2, 3) = 0;
    M.At(3, 0) = 0;
    M.At(3, 1) = 0;
    M.At(3, 2) = 0;
    M.At(3, 3) = 1;

    return M;
}

Matrix4x4 Matrix4x4::FromTRS(const Vec3& t, const Matrix3x3& R, const Vec3& s)
{
    Matrix4x4 M = Matrix4x4::Identity();

    
    M.At(0, 0) = R.At(0, 0) * s.x;
    M.At(1, 0) = R.At(1, 0) * s.x;
    M.At(2, 0) = R.At(2, 0) * s.x;

    
    M.At(0, 1) = R.At(0, 1) * s.y;
    M.At(1, 1) = R.At(1, 1) * s.y;
    M.At(2, 1) = R.At(2, 1) * s.y;

    
    M.At(0, 2) = R.At(0, 2) * s.z;
    M.At(1, 2) = R.At(1, 2) * s.z;
    M.At(2, 2) = R.At(2, 2) * s.z;

    
    M.At(0, 3) = t.x;
    M.At(1, 3) = t.y;
    M.At(2, 3) = t.z;

    return M;
}

Matrix4x4 Matrix4x4::FromTRS(const Vec3& t, const Quat& q, const Vec3& s)
{
    return FromTRS(t, q.ToMatrix3x3(), s);
}

Matrix4x4 Matrix4x4::InverseTR() const
{
    if (!IsAffine())
        throw std::runtime_error("La matriz no es afín");

    Matrix3x3 R = GetRotationScale();
    Vec3 t = GetTranslation();

    Matrix3x3 Rt = R.Transposed();

    Vec3 tInv = Rt * Vec3{ -t.x, -t.y, -t.z };

    Matrix4x4 M = Matrix4x4::Identity();
    M.SetRotation(Rt);
    M.SetTranslation(tInv);

    return M;
}

Matrix4x4 Matrix4x4::InverseTRS() const
{
    if (!IsAffine())
        throw std::runtime_error("La matriz no es afín");

    Vec3 s = GetScale();
    Matrix3x3 RS = GetRotationScale();
    Vec3 t = GetTranslation();

    Matrix3x3 SInv;
    SInv.At(0, 0) = 1.0 / s.x;
    SInv.At(1, 1) = 1.0 / s.y;
    SInv.At(2, 2) = 1.0 / s.z;

    Matrix3x3 R = RS * SInv;
    Matrix3x3 Rt = R.Transposed();

    Matrix3x3 RSInv = SInv * Rt;
    Vec3 tInv = RSInv * Vec3{ -t.x, -t.y, -t.z };

    Matrix4x4 M = Matrix4x4::Identity();
    M.SetRotationScale(RSInv);
    M.SetTranslation(tInv);

    return M;
}

Vec3 Matrix4x4::GetTranslation() const
{
    Vec3 res;
    res.x = At(0, 3);
    res.y = At(1, 3);
    res.z = At(2, 3);
    return res;
}

Matrix3x3 Matrix4x4::GetRotationScale() const
{
    Matrix3x3 M;
    M.At(0, 0) = At(0, 0);
    M.At(0, 1) = At(0, 1);
    M.At(0, 2) = At(0, 2);
    M.At(1, 0) = At(1, 0);
    M.At(1, 1) = At(1, 1);
    M.At(1, 2) = At(1, 2);
    M.At(2, 0) = At(2, 0);
    M.At(2, 1) = At(2, 1);
    M.At(2, 2) = At(2, 2);

    return M;
}

Vec3 Matrix4x4::GetScale() const
{
    Vec3 s;

    double c0x = At(0, 0), c0y = At(1, 0), c0z = At(2, 0);
    double c1x = At(0, 1), c1y = At(1, 1), c1z = At(2, 1);
    double c2x = At(0, 2), c2y = At(1, 2), c2z = At(2, 2);

    s.x = std::sqrt(c0x * c0x + c0y * c0y + c0z * c0z);
    s.y = std::sqrt(c1x * c1x + c1y * c1y + c1z * c1z);
    s.z = std::sqrt(c2x * c2x + c2y * c2y + c2z * c2z);

    Matrix3x3 R;
    R.At(0, 0) = c0x / s.x; R.At(1, 0) = c0y / s.x; R.At(2, 0) = c0z / s.x;
    R.At(0, 1) = c1x / s.y; R.At(1, 1) = c1y / s.y; R.At(2, 1) = c1z / s.y;
    R.At(0, 2) = c2x / s.z; R.At(1, 2) = c2y / s.z; R.At(2, 2) = c2z / s.z;

    double det = R.At(0, 0) * (R.At(1, 1) * R.At(2, 2) - R.At(1, 2) * R.At(2, 1)) - R.At(0, 1) * (R.At(1, 0) * R.At(2, 2) - R.At(1, 2) * R.At(2, 0)) + R.At(0, 2) * (R.At(1, 0) * R.At(2, 1) - R.At(1, 1) * R.At(2, 0));
    
    //Miramos si la escala es negativa. Hemos escogido el eje X para corregir la rotación.
    if (det < 0) {
        s.x = -s.x;
    }

    return s;
}

Matrix3x3 Matrix4x4::GetRotation() const
{
    Vec3 s = GetScale();
    Matrix3x3 R;

    R.At(0, 0) = At(0, 0) / s.x;
    R.At(1, 0) = At(1, 0) / s.x;
    R.At(2, 0) = At(2, 0) / s.x;

    R.At(0, 1) = At(0, 1) / s.y;
    R.At(1, 1) = At(1, 1) / s.y;
    R.At(2, 1) = At(2, 1) / s.y;

    R.At(0, 2) = At(0, 2) / s.z;
    R.At(1, 2) = At(1, 2) / s.z;
    R.At(2, 2) = At(2, 2) / s.z;

    return R;
}

Quat Matrix4x4::GetRotationQuat() const
{
    Matrix3x3 R = GetRotation();
    return Quat::FromMatrix3x3(R);
}

void Matrix4x4::SetTranslation(const Vec3& t)
{
    At(0, 3) = t.x;
    At(1, 3) = t.y;
    At(2, 3) = t.z;
}

void Matrix4x4::SetScale(const Vec3& s)
{
    Matrix3x3 R = GetRotation();

    At(0, 0) = R.At(0, 0) * s.x;
    At(1, 0) = R.At(1, 0) * s.x;
    At(2, 0) = R.At(2, 0) * s.x;

    At(0, 1) = R.At(0, 1) * s.y;
    At(1, 1) = R.At(1, 1) * s.y;
    At(2, 1) = R.At(2, 1) * s.y;

    At(0, 2) = R.At(0, 2) * s.z;
    At(1, 2) = R.At(1, 2) * s.z;
    At(2, 2) = R.At(2, 2) * s.z;
}

void Matrix4x4::SetRotation(const Matrix3x3& R)
{
    Vec3 s = GetScale();

    At(0, 0) = R.At(0, 0) * s.x;
    At(1, 0) = R.At(1, 0) * s.x;
    At(2, 0) = R.At(2, 0) * s.x;

    At(0, 1) = R.At(0, 1) * s.y;
    At(1, 1) = R.At(1, 1) * s.y;
    At(2, 1) = R.At(2, 1) * s.y;

    At(0, 2) = R.At(0, 2) * s.z;
    At(1, 2) = R.At(1, 2) * s.z;
    At(2, 2) = R.At(2, 2) * s.z;
}

void Matrix4x4::SetRotation(const Quat& q)
{
    SetRotation(q.ToMatrix3x3());
}

void Matrix4x4::SetRotationScale(const Matrix3x3& RS)
{
    At(0, 0) = RS.At(0, 0);
    At(0, 1) = RS.At(0, 1);
    At(0, 2) = RS.At(0, 2);

    At(1, 0) = RS.At(1, 0);
    At(1, 1) = RS.At(1, 1);
    At(1, 2) = RS.At(1, 2);

    At(2, 0) = RS.At(2, 0);
    At(2, 1) = RS.At(2, 1);
    At(2, 2) = RS.At(2, 2);
}

Matrix4x4 Matrix4x4::Perspective(double left, double right, double bottom, double top, double nearPlane, double farPlane)
{
    Matrix4x4 M{};

    M.At(0, 0) = (2.0 * nearPlane) / (right - left);
    M.At(1, 1) = (2.0 * nearPlane) / (top - bottom);

    M.At(0, 2) = (right + left) / (right - left);
    M.At(1, 2) = (top + bottom) / (top - bottom);

    M.At(2, 2) = -(farPlane + nearPlane) / (farPlane - nearPlane);
    M.At(2, 3) = -(2.0 * farPlane * nearPlane) / (farPlane - nearPlane);

    M.At(3, 2) = -1.0;
    M.At(3, 3) = 0.0;

    return M;
}