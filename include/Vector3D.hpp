#ifndef VECTOR3D_HPP
#define VECTOR3D_HPP

#include <cmath>

class Vector3D {
public:
    double x, y, z;

    // constructors
    Vector3D();
    Vector3D(double x, double y, double z);

    // Basic Vector operations
    Vector3D operator+(const Vector3D& other) const;
    Vector3D operator-(const Vector3D& other) const;
    Vector3D& operator+=(const Vector3D& other);
    Vector3D operator*(double scalar) const;

    // Physics-related methods
    double norm() const;
    double distSquared(const Vector3D& other) const;
};

#endif