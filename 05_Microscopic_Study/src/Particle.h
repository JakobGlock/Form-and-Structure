#ifndef PARTICLE_H
#define PARTICLE_H

#include "ofMain.h"
#include "Spring.h"

/* This is my particle class */

class Particle
{
public:
    Particle(ofVec2f _p, ofVec2f _v);
    void update();
    void draw();
    void dampenForce();
    void resetForce();
    void addForce(ofVec2f _f);

    /* Getters and Setters */
    ofVec2f getPosition();

    /* variables */
    ofVec2f *p;
    ofVec2f pos, vel, frc;
    float radius, friction;

    /* Create a spring */
    Spring mySpring;
};

#endif // PARTICLE_H
