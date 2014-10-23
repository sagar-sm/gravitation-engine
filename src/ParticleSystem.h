//
//  ParticleSystem.h
//  PE
//
//  Created by Sagar Mohite on 10/11/14.
//
//

#ifndef __PE__ParticleSystem__
#define __PE__ParticleSystem__

#include <stdio.h>
#include "Particle.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class ParticleSystem {
public:
    ParticleSystem();
    ParticleSystem(bool _isClosed);
    
    void add(int N);
    void add(Particle p);
    void draw();
    void update();
    void applyForces();
    
    list<Particle>  bodies;
    bool isClosed = false;
    int resolution = -1;
    
    
};

#endif /* defined(__PE__ParticleSystem__) */
