#include "Particle.h"

//--------------------------------------------------------------
Particle::Particle(ofVec3f _pos, int _id, float _angle, float centerX, float centerY){

    /* Initialize variables */
    startFreq1 = 3;
    startFreq2 = 3;
    attractAmt1 = 1.5;
    attractAmt2 = 0.2;
    attractAmt3 = 0.2;
    attractAmt4 = 0.25;
    attractAmt5 = 0.25;
    attractAmt6 = -0.125;

    center.set(centerX, centerY, 0);
    pos.set(_pos.x, _pos.y);
    prevPos.set(_pos.x + cos(_angle * _id * startFreq1), _pos.y + sin(_angle * _id * startFreq2));
    vel.set(0, 0);
    id = _id;
    angle = _angle;
    maxDist = ofRandom(30, 100);
    col = ofColor(255);
    friction = ofRandom(0.25, 0.9);
}

//--------------------------------------------------------------
void Particle::update(){

    /* Here I am using Verlet Intergration for my physics */

    /* Add up all the forces */
    f += force(ofVec3f(center.x, center.y, 0), attractAmt1);
    f += force(ofVec3f(center.x+200, center.y, 0), attractAmt2);
    f += force(ofVec3f(center.x-200, center.y, 0), attractAmt3);
    f += force(ofVec3f(center.x, center.y+200, 0), attractAmt4);
    f += force(ofVec3f(center.x, center.y-200, 0), attractAmt5);
    f += force(ofVec3f(center.x, center.y, 0), attractAmt6);

    /* Divide by the number of attractors to get an average */
    f /= 6;

    /* Add the force to the positon */
    pos.x += f.x;
    pos.y += f.y;

    /* Subtract the postion from the previous postion to get the velocity */
    vel.x = pos.x - prevPos.x;
    vel.y = pos.y - prevPos.y;

    /* Save the current position */
    prevPos.set(pos);

    /* Add the velocity to the position */
    pos += vel;

}

//--------------------------------------------------------------
ofVec2f Particle::force(ofVec3f _attractPoint, float _amt){

    /* Here I am calculating a force, this function returns a 2d vector */

    /* Create a 2d vector to store my force amount */
    ofVec2f f;

    /* Get the distance from the point to the attract point */
    float distX = _attractPoint.x - pos.x;
    float distY = _attractPoint.y - pos.y;

    /* Pythagorean theorum */
    float distance = sqrt(distX * distX + distY * distY) * _amt;

    /* Save force */
    f.x = distX / distance / 50;
    f.y = distY / distance / 50;

    /* return force */
    return f;

}

//--------------------------------------------------------------
void Particle::drawLine(ofVec3f _pos){

    /* Get distance from current point to the other point */
    float d = ofDist(pos.x, pos.y, _pos.x, _pos.y);

    /* Get distance from current point to the center of the screen */
    float c = ofDist(pos.x, pos.y, center.x, center.y);

    if(d < 30 && d > 10 && id%2 == 0)
    {
        ofSetColor(ofColor(ofMap(c, 0, 300, 150, 255, true)), col.a);
        ofSetLineWidth(0.125);
        ofDrawLine(pos.x, pos.y, _pos.x, _pos.y);
    }
    else if(d < 70 && d > 30 && id%2 == 1)
    {
        float k = ofMap(c, 0, 300, 7, 6, true);
        ofSetColor(0, 0, 25, k);

        ofSetLineWidth(1);
        ofDrawLine(pos.x, pos.y, _pos.x, _pos.y);
    }
    else if(d < 90 && d > 70 && c < 40)
    {
        float k = ofMap(c, 0, 300, 7, 6, true);
        ofSetColor(25, 25, 0, k);

        ofSetLineWidth(1);
        ofDrawLine(pos.x, pos.y, _pos.x, _pos.y);
    }

}

//--------------------------------------------------------------
void Particle::setColor(ofColor c){
    col = ofColor(c);
}
