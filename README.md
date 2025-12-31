# N-Body Solar System Simulation

This project is a **C++ N-Body simulator** designed to model the orbital dynamics of the Solar System. It serves as a pedagogical implementation of Newtonian physics and numerical methods, providing a foundation for more complex simulations like Smoothed Particle Hydrodynamics (SPH).

## 🌌 Physics & Numerical Methods

### 1. Gravitational Softening
In a pure Newtonian model, the force becomes infinite as the distance between two bodies approaches zero ($1/r^2$). In a discrete numerical simulation, a close encounter can lead to a "numerical singularity," where a body is ejected from the system at unphysical speeds due to an extreme acceleration spike.

To prevent this, we implement **Gravitational Softening**:

$$
\vec{a}_i = \sum_{j \neq i} G \frac{M_j}{(\|\vec{r}_{ij}\|^2 + \epsilon^2)^{3/2}} \vec{r}_{ij}
$$

The parameter $\epsilon$ (softening length) ensures the denominator never reaches zero. This technique is not only a stability trick for N-Body systems but is also a core concept in **SPH (Smoothed Particle Hydrodynamics)**, where it defines the interaction scale between fluid particles.

### 2. Time Integration: Semi-Implicit Euler
The simulation currently uses the **Semi-Implicit Euler** scheme (also known as Euler-Cromer). Unlike the standard explicit Euler, it updates velocity first and then uses the *new* velocity to update the position:

1. $ \vec{v}_{n+1} = \vec{v}_n + \vec{a}_n \Delta t $
2. $ \vec{r}_{n+1} = \vec{r}_n + \vec{v}_{n+1} \Delta t $

**Limitations:** While this method is symplectic (it conserves phase-space volume better than explicit Euler), it remains a **first-order integrator**. It is relatively simplistic and can lead to energy drift over very long timescales (centuries). For higher precision, higher-order schemes like **Runge-Kutta 4 (RK4)** or **Velocity Verlet** would be preferred.

## 🛠 Technical Stack
* **Language:** C++17
* **Vector Algebra:** Custom `Vector3D` class with operator overloading.
* **Architecture:** Modular design with `CelestialBody` objects managed in `std::vector`.
* **Visualization:** Python 3 (Pandas/Matplotlib) converting data to Astronomical Units (AU).

## 🚀 How to Run

### 1. Build the C++ Simulation
```bash
mkdir build && cd build
cmake ..
make
./nbody_sim
```

### 2. Python Visualization

Ensure you are in your virtual environment (or create one)
```bash
source .venv/bin/activate
pip install pandas matplotlib
python3 plot_solar_system.py
```

## 📂 Project Structure
```
NBodyProject/
├── include/             # Header files (.hpp)
├── src/                 # Source files (.cpp)
├── main.cpp             # Simulation setup and main loop
├── plot_solar_system.py # Python visualization script
├── CMakeLists.txt       # Build configuration
└── .gitignore           # Keeps the repo clean (ignores build/ and .csv)
```

* `include/` & `src/`: Core simulation engine and vector math.
* `main.cpp`: System setup (Sun to Neptune) and temporal evolution loop.
* `plot_solar_system.py`: Visualization tool with AU scaling and origin tracking.
* `CMakeLists.txt`: Build configuration for the C++ project.

## 🔬 Scientific Context & Future Improvements

This simulator is developed as a foundational tool for studying numerical astrophysics. While the current model accurately replicates planetary orbits, it also highlights the inherent challenges of computational physics:

### 1. Numerical Stability & Softening
The implementation of **Gravitational Softening** ($\epsilon$) is a critical bridge to **Smoothed Particle Hydrodynamics (SPH)**. In SPH, the interaction between particles is governed by a **smoothing kernel** ($W$), which, like our softening parameter, ensures that forces remain finite and differentiable at short distances, allowing for stable modeling of continuous media like the cryolava flows studied in my doctoral research.

### 2. Integrator Precision
The current **Semi-Implicit Euler** scheme is a simplistic, first-order method. While it demonstrates the basic principles of symplectic integration, it is prone to long-term energy drift. This makes it an ideal case study for transitioning toward more robust algorithms used in research-grade simulations.

### 🚀 Planned Improvements
* **Advanced Integration:** Implementing the **Velocity Verlet** algorithm to achieve second-order accuracy and better energy conservation.
* **Real-Time Visualization (Raylib):** Shifting from offline data processing to a high-performance, real-time rendering engine using **Raylib**. This will allow for:
    * Interactive camera controls to explore the system in 3D.
    * Live parameter tuning (e.g., adjusting simulation speed or gravitational constants on the fly).
    * Visualizing orbital trails and stability in real-time.
* **Algorithm Optimization:** Moving beyond $O(N^2)$ by implementing an **Octree (Barnes-Hut)** structure to handle a larger number of bodies (e.g., asteroid belts).

---
**Author:** Bastien Bodin  
* PhD in Astrophysics - Modeling cryolava flows on Europa using SPH (in prep).
* **Email:** [bastien.bodin@proton.me](mailto:bastien.bodin@proton.me)