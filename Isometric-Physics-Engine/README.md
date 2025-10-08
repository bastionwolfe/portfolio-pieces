# Isometric Physics Engine

> A standalone C++ physics simulation engine designed for isometric 2D games or applications.  
> Focused purely on physics calculations and state updates — no rendering or input handling included.

---

## Overview

This project implements a **physics-only engine** that simulates fundamental physical behaviors for isometric-style 2D environments. It provides a minimal, old-school C++ API for creating and managing physics objects, applying forces, and performing stable fixed-timestep updates.

Key features:
- Vector math primitives with manual memory management
- Force accumulation and integration (Euler, Verlet)
- Collision detection and resolution for circles and AABBs
- Impulse-based collision response with restitution and friction
- Coordinate conversion between Cartesian and isometric spaces
- Fully deterministic fixed timestep simulation

This engine is intended as a showcase of **low-level C++ programming, physics simulation, and math skills**, built from scratch without STL containers and in core logic.

---

## Table of Contents

- [Getting Started](#getting-started)
- [Building the Project](#building-the-project)
- [Usage](#usage)
- [Core Components](#core-components)
- [Testing](#testing)
- [Roadmap](#roadmap)
- [Contributing](#contributing)
- [License](#license)

---

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

### Prerequisites

- C++17 compatible compiler (GCC, Clang, MSVC)
- CMake 3.10 or later (or modify for your build system)

### Clone the Repository

```bash
git clone https://github.com/bastionwolfe/Isometric-Physics-Engine.git
cd Isometric-Physics-Engine
```

### Building the Project

Build with CMake:
```bash
mkdir build && cd build
cmake ..
make
```

This will build the core physics engine and example simulations.

### Usage - WIP p

Include the engine headers in your C++ project:
```bash

```


Run example binaries in the build/examples directory to see the engine in action:

```bash

```

## Core Components

- Vec3 (Vector 3D)

- Represents 2D vectors with x, y and z coordinates

- Provides operations: addition, subtraction, multiplication, dot product, normalization, length

- PhysicsObject

- Represents a physical entity with position, velocity, mass, forces

- Supports applying forces, impulses

- Tracks state for fixed timestep updates

- PhysicsWorld

- Manages a collection of PhysicsObjects

- Runs a fixed timestep update loop

- Applies forces, integrates motion, detects and resolves collisions

- Collision Detection

- Supports Circle and AABB shapes

- Provides overlap detection algorithms

- Efficient broad-phase collision checks

- Collision Resolution

- Impulse-based response

- Incorporates restitution (bounciness) and friction

- Handles velocity and position corrections

- Isometric Conversion

- Utilities to convert coordinates between Cartesian (physics space) and isometric (rendering space)

## Testing

- Automated tests cover:

- Vector math correctness

- Physics integration accuracy

- Collision detection precision

- Collision response stability

Run tests with:

```bash
make test 
```
or 
```bash
ctest
```

## Roadmap

### Completed

- Vector math primitives
  
- Physics integration (Euler, Verlet)
  
- Force accumulation and damping

- Circle and AABB collision detection (Partial)

### In Progress / Planned

- Impulse-based collision response with friction and restitution

- Cartesian to isometric coordinate conversion

- Fixed timestep simulation loop

- Spatial partitioning for broad-phase collision optimization

- Joints and constraints (e.g., springs, rods)

- Continuous collision detection (CCD) improvements

- Serialization and state save/load support

- Performance benchmarks and profiling

- Extensive example scenes with varying complexity

### Contributing

Contributions, bug reports, and feature requests are welcome! Please open an issue or submit a pull request.

### License

This project is licensed under the MIT License — see the LICENSE
 file for details.

## About

Built with care by Zachary Music to demonstrate mastery of low-level C++ programming and physics simulation.
