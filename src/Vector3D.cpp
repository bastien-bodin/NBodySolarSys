#include "Vector3D.hpp"

// --------------------------
// Constructors
// --------------------------
// Default constructor
Vector3D::Vector3D() : x(0.0), y(0.0), z(0.0) {}

// Parameterized constructor
Vector3D::Vector3D(double x, double y, double z) : x(x), y(y), z(z) {}

// --------------------------
// Operators
// --------------------------
// Vector addition
Vector3D Vector3D::operator+(const Vector3D& other) const {
    return Vector3D(x + other.x, y + other.y, z + other.z);
}

// Vector substraction
Vector3D Vector3D::operator-(const Vector3D& other) const {
    return Vector3D(x - other.x, y - other.y, z - other.z);
}

// In-place addition (useful for position += velocity * dt)
Vector3D& Vector3D::operator+=(const Vector3D& other) {
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

// Multiplication by a scalar
Vector3D Vector3D::operator*(double scalar) const {
    return Vector3D(x * scalar, y * scalar, z * scalar);
}

// --------------------------
// Methods
// --------------------------
// Euclidean norm
double Vector3D::norm() const {
    return std::sqrt(x * x + y * y + z * z);
}

// Squared distance
double Vector3D::distSquared(const Vector3D& other) const {
    double dx = x - other.x;
    double dy = y - other.y;
    double dz = z - other.z;
    return dx * dx + dy * dy + dz * dz;
}