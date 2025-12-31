#include <iostream>
#include <vector>
#include <fstream>
#include "Vector3D.hpp"
#include "CelestialBody.hpp"

int main() {
    std::vector<CelestialBody> solarSystem;
    
    // 10km softening for stability
    double eps = 10000.0; 

    // Creating Bodies for the Solar System
    CelestialBody Sun(
        "Sun",
        1.989e30,
        Vector3D(0, 0, 0),
        Vector3D(0,0,0),
        eps
    );
    CelestialBody Mercury(
        "Mercury",
        3.301e23,
        Vector3D(5.791e10, 0, 0),
        Vector3D(0, 47360, 0),
        eps
    );
    CelestialBody Venus(
        "Venus",
        4.867e24,
        Vector3D(1.082e11, 0, 0),
        Vector3D(0, 35020, 0),
        eps
    );
    CelestialBody Earth(
        "Earth",
        5.972e24,
        Vector3D(1.496e11, 0, 0),
        Vector3D(0, 29780, 0),
        eps
    );             
    CelestialBody Mars(
        "Mars",
        6.390e23,
        Vector3D(2.279e11, 0, 0),
        Vector3D(0, 24070, 0),
        eps
    );
    CelestialBody Jupiter(
        "Jupiter",
        1.898e27,
        Vector3D(7.785e11, 0, 0),
        Vector3D(0, 13070, 0),
        eps
    );         
    CelestialBody Saturn(
        "Saturn",
        5.683e26,
        Vector3D(1.433e12, 0, 0),
        Vector3D(0, 9680, 0),
        eps
    );           
    CelestialBody Uranus(
        "Uranus",
        8.681e25,
        Vector3D(2.871e12, 0, 0),
        Vector3D(0, 6810, 0),
        eps
    );
                         
    CelestialBody Neptune(
        "Neptune",
        1.024e26,
        Vector3D(4.495e12, 0, 0),
        Vector3D(0, 5430, 0),
        eps
    );

    // 2. Add them to the simulation vector
    solarSystem.push_back(Sun);
    solarSystem.push_back(Mercury);
    solarSystem.push_back(Venus);
    solarSystem.push_back(Earth);
    solarSystem.push_back(Mars);
    solarSystem.push_back(Jupiter);
    solarSystem.push_back(Saturn);
    solarSystem.push_back(Uranus);
    solarSystem.push_back(Neptune);

    // 3. Simulation Parameters
    double time_step_seconds = 3600.0 * 24.0; // 1 day step
    int total_years = 165; // Sufficient for one Neptune orbit
    int total_steps = 365 * total_years;

    // 4. Output file setup
    std::ofstream dataFile("solar_system_atlas.csv");
    dataFile << "step,name,x,y,z\n";

    std::cout << "Starting Solar System Simulation for " << total_years << " years..." << std::endl;

    // 5. Main Simulation Loop
    for (int step=0; step < total_steps; ++step) {
        // A. Reset acceleration vector \vec{a} for all bodies
        for (auto& body : solarSystem) {
            body.resetAcceleration();
        }

        // B. N-Body Gravitational Interactions
        // We compute how each "source" affects each "target"
        for (auto& targetBody : solarSystem) {
            for (const auto& sourceBody : solarSystem) {
                // A body doesn't exert gravity on itself
                if (&targetBody == &sourceBody) continue;

                targetBody.addGravity(sourceBody);
            }
        }

        // C. Numerical Integration: Update vel and pos
        for (auto& body : solarSystem) {
            body.update(time_step_seconds);
        }

        // D. Data Export (Every 10 days)
        if (step % 10 == 0) {
            for (const auto& body : solarSystem) {
                dataFile << step << "," << body.name << ","
                         << body.position.x << ","
                         << body.position.y << ","
                         << body.position.z << "\n";
            }
        }
    }

    dataFile.close();

    std::cout << "Simulation successfully completed. Output: solar_system_atlas.csv" << std::endl;

    return 0;
}