//
//  Particle.h
//  PE
//
//  Created by Sagar Mohite on 10/18/14.
//
//

#ifndef __PE__Particle__
#define __PE__Particle__

#include <stdio.h>

using namespace ci;
using namespace ci::app;
using namespace std;

class Particle {
public:
    Particle();
    Particle(Vec3f _pos, Vec3f _vel, float _radius, float _mass);
    Particle(Vec3f _pos, Vec3f _vel, float _radius, float _mass, bool _ils);
    
    void draw(int resolution, int size);
    void update();
    
    Vec3f   pos, vel, acc;
    float   mass, radius;
    float   decay = 1.0f;
    bool    isLightSource = false;
};

#endif /* defined(__PE__Particle__) */
