//
//  Particle.cpp
//  PE
//
//  Created by Sagar Mohite on 10/18/14.
//
//

#include "Particle.h"
#include "cinder/gl/Light.h"

using namespace ci;
using namespace ci::app;
using namespace std;

Particle::Particle() : pos(Vec3f::zero()), vel(Vec3f::zero()), acc(Vec3f::zero()), radius(1), mass(1) {};

Particle::Particle( Vec3f _pos, Vec3f _vel, float _radius, float _mass ){
    pos   =  _pos;
    vel   =  _vel;
    acc   =  Vec3f::zero();
    radius=  _radius;
    mass  =  _mass;
}

Particle::Particle( Vec3f _pos, Vec3f _vel, float _radius, float _mass , bool _ils){
    pos   =  _pos;
    vel   =  _vel;
    acc   =  Vec3f::zero();
    radius=  _radius;
    mass  =  _mass;
    isLightSource = _ils;
}

void Particle::update()
{
    vel += acc;
    pos += vel;
    vel *= decay;
    acc = Vec3f::zero();
}

void Particle::draw(int size)
{
    if(isLightSource){

    }
    int resolution = 8;
    if(size < 50 || radius >= 7)
        resolution = 32;
    gl::drawSphere( pos, radius, resolution );
//    gl::drawSolidCircle(Vec2f(pos.x, pos.y), 1);
}