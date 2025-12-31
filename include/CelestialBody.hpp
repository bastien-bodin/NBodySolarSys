#ifndef CELESTIALBODY_HPP
#define CELESTIALBODY_HPP

#include <string>
#include "Vector3D.hpp"

class CelestialBody {
public:
    std::string name;
    double mass;
    Vector3D position;
    Vector3D velocity;
    Vector3D acceleration;
    double softening;

    // Constructor
    CelestialBody(
        std::string name, double mass,
        Vector3D pos, Vector3D vel,
        double soft = 1000.0 // default softening to 1 km
    );

    // Physics methods
    void resetAcceleration();
    void addGravity(const CelestialBody& other);
    void update(double dt);
};

#endif