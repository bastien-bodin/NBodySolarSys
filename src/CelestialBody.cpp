#include "CelestialBody.hpp"
#include <cmath>

// Gravitational constant
const double G = 6.67430e-11;


// --------------------------
// Constructors
// --------------------------
// Default constructor
CelestialBody::CelestialBody(
    std::string name, double mass, Vector3D pos, Vector3D vel, double soft
) :
name(name), mass(mass),
position(pos), velocity(vel),
acceleration(0.0, 0.0, 0.0),
softening(soft) {}

// --------------------------
// Methods
// --------------------------
void CelestialBody::resetAcceleration() {
    acceleration = Vector3D(0.0, 0.0, 0.0);
}

void CelestialBody::addGravity(const CelestialBody& other) {
    double r2 = position.distSquared(other.position);

    // using the softening factor
    double eps2 = softening * softening;

    // softened denominator: (r^2 + eps^2)^(3/2)
    double dist_softened = std::pow(r2 + eps2, 1.5);

    Vector3D diff = other.position - position;

    // Newton's law with softening G * m * r/(r^2+e^2)^3/2
    double accelerationMagnitude = (G * other.mass) / dist_softened;

    acceleration += diff * accelerationMagnitude;
}

void CelestialBody::update(double dt) {
    // Semi-implicit Euler
    velocity += acceleration * dt;
    position += velocity * dt;
}