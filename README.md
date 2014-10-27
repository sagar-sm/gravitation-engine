#OpenGL Particle Simulator to demo gravitation

##Usage:
Include "ParticleSystem.h"

```
//Create a New System
ParticleSystem system;
```
###Resolution
By default the resolution of each sphere is automatically computed to optimize performance.
However you can set the resolution of the sphere using the following method. 

```
//Set resolution of each particle. By default it is automatic.
system.setResolution(int res);
```

To switch back to auto-resolution run `system.setResolution(-1);`

###Ways to add particles
```
//1 Random
system.add(int NUMBER_OF_PARTICLES); 

//2 Custom
system.add(Particle p);
```

###Ways to create particles
```
Particle p1 = Particle(); //random

Particle p2 = Particle(Vec3f position, Vec3f initial_velocity, float radius, float mass);

Particle p3 = Particle(Vec3f position, Vec3f initial_velocity, float radius, float mass, bool isLightSource);
```

###Update
```
system.update();
system.draw();
```

Implemented using Newton's law of universal gravitation and Cinder.

**TODOs:** 

1. Add conservation of energy and use Einstein's Field Equations.
2. Make system account for object geometries and shapes.
