#ifndef PARTICLE_H
#define PARTICLE_H

#include "ofMain.h"

class Particle{
public:
    Particle(ofVec3f _pos, int _id, float _angle, float centerX, float centerY);
    void update();
    void draw();
    void drawLine(ofVec3f _pos);
    void setColor(ofColor c);
    ofVec2f force(ofVec3f _attractPoint, float _amt);

    /* Varibales */
    ofVec3f prevPos, pos, vel, otherPos, f, center;
    float angle, maxDist, friction;
    int id;
    ofColor col;
    float startFreq1, startFreq2, attractAmt1, attractAmt2, attractAmt3, attractAmt4, attractAmt5, attractAmt6;

};

#endif // PARTICLE_H
