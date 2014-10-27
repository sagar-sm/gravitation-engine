//
//  ParticleSystem.cpp
//  PE
//
//  Created by Sagar Mohite on 10/11/14.
//
//

#include "ParticleSystem.h"
#include "Particle.h"
#include "cinder/Rand.h"

#define G 2

ParticleSystem::ParticleSystem() {}

ParticleSystem::ParticleSystem(bool _isClosed) {
    isClosed = _isClosed;
}

void ParticleSystem::add(int N){
    for( int i=0; i < N; i++ )
    {
        Vec3f pos = Rand::randVec3f() * Rand::randFloat( 50.0f, 250.0f);
        Vec3f vel = Rand::randVec3f() * 1.0f;
        float radius = 3.0f, mass = randFloat(5.0f, 30.0f);
        bodies.push_back( Particle( pos, vel, radius, mass) );
    }
}

void ParticleSystem::add(Particle p){
    bodies.push_back(p);
}


void ParticleSystem::update()
{
    applyForces();
    for( list<Particle>::iterator p = bodies.begin(); p != bodies.end(); ++p ){
        p->update();
    }
}


void ParticleSystem::applyForces()
{
    for( list<Particle>::iterator p1 = bodies.begin(); p1 != bodies.end(); ++p1 ){
        
        list<Particle>::iterator p2 = p1;
        for( ++p2; p2 != bodies.end(); ++p2 ) {
            Vec3f dir = p1->pos - p2->pos;
            float distSqrd = dir.lengthSquared();
            
            //TO USE after implementing e=mc2 and Einstein's EFEs;
            int flip = 1;
            
            double minDist = pow(p1->radius - p2->radius, 2);
            if(distSqrd >= minDist){
                float F = (G * p1->mass * p2->mass)/distSqrd;
            
                dir.normalize();
                dir *= F;
                
                //NOTE: flip is defunct
                p1->acc -= flip * dir / p1->mass;
                p2->acc += flip * dir / p2->mass;
            }
            else {
                if(p1->mass >= p2->mass){
                    //CONSERVATION OF MASS
                    p1->mass += p2->mass;
                    //CONSERVATION OF MOMENTUM
                    p1->vel += p2->vel/p1->mass;
                    bodies.erase(p2);
                    
                }
                else {
                    //CONSERVATION OF MASS
                    p2->mass += p1->mass;
                    //CONSERVATION OF MOMENTUM
                    p2->vel += p1->vel/p2->mass;
                    bodies.erase(p1);

                    
                }
            }

        }
        //cout<<p1->pos;
    }
}

void ParticleSystem::draw()
{
    gl::color( ColorA( 1.0f, 1.0f, 1.0f, 1.0f ) );
    for( list<Particle>::iterator p = bodies.begin(); p != bodies.end(); ++p ){
        p->draw(resolution, bodies.size());
    }
}

void ParticleSystem::setResolution(int res) {
    resolution = res;
}
