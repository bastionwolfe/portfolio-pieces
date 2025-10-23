/*
 * Not really sure how to start it so posting an outline for now and will learn more about BVH and implenting it before doing more
 *
 * Broad-Phase Collision Detection System - Design Overview
 *
 * This module implements a modular and efficient broad-phase collision detection system
 * for an isometric open-world physics engine. It supports both Axis-Aligned Bounding Boxes (AABB)
 * and circular collision shapes, designed to work seamlessly with multiple data layouts:
 * - AoS (Array of Structures)
 * - SoA (Structure of Arrays)
 * - AoSoA8 (Array of Structure of Arrays, 8-wide SIMD friendly)
 *
 * Key Features:
 * -------------
 * 1. Dual-Phase Simulation:
 *    - On-Screen Simulation:
 *      - Uses a dynamic Bounding Volume Hierarchy (BVH)
 *        to provide accurate and high-performance collision broad-phase.
 *      - Supports fast insertion, removal, and updating of moving objects.
 *      - Enables precise collision detection suitable for visible and active objects.
 *      - Leverages SIMD vectorization to process multiple objects and queries in parallel.
 *
 *    - Off-Screen Simulation:
 *      - Employs a lightweight coarse spatial grouping system (e.g., chunk-based buckets or spatial hash)
 *        for off-screen objects.
 *      - Simplified physics: no rotation simulation, uses appointed facing direction based on velocity.
 *      - Minimizes CPU overhead, allowing scalable simulation of large open worlds.
 *      - Ensures believable object behavior with less precision.
 *
 * 2. Smooth Transitioning Between On-Screen and Off-Screen:
 *    - Objects track simulation state (ONSCREEN_BVH or OFFSCREEN_COARSE).
 *    - When entering screen proximity, objects transition from coarse to BVH simulation,
 *      enabling full physics and rotation.
 *    - When moving off-screen, objects transition back to the coarse system,
 *      disabling detailed physics to save computation.
 *    - Hysteresis zones prevent frequent toggling of simulation state near screen edges.
 *
 * 3. Data Layout Agnostic API:
 *    - Broad-phase collision detection algorithms operate on generic interfaces,
 *      enabling support for AoS, SoA, and AoSoA8 without code duplication.
 *    - Data is stored and processed in SIMD-friendly layouts (SoA/AoSoA8) for maximum performance.
 *
 * 4. Collision Shape Support:
 *    - Handles multiple collision shapes, primarily AABB and circles.
 *    - Broad-phase queries use bounding volumes expanded for object velocities (temporal expansion).
 *
 */


 #include "Vector3.h"
 #include "circularCollisionDectection.h"
 #include "AABBCollisionDectection.h"
 
 struct BVH_BroadPhase {
 }
 
 struct CoarseGrid_BroadPhase {
 }
 
 struct broadPahse_Manager {
     
    addAoS() {
    }
    
    removeAoS(id) {
    }
    
    addSoA() {
    }
    
    removeSoA(id) {
    }
    
    addAoSoA8() {
    }
    
    removeAoSoA8(id) {
    }
    
    getObjID(id) {
    }
 }
