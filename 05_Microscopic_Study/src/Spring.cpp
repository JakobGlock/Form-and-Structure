#include "Spring.h"

//--------------------------------------------------------------
Spring::Spring(ofVec2f _a, ofVec2f _p){
    /* Default values */
    anchor.set(_a.x, _a.y);
    weight.set(_p.x, _p.y);
    len = 0;
}

//--------------------------------------------------------------
/* This function returns a vector of the calculated force */
ofVec2f Spring::update(ofVec2f _p){

    /* Update the current position of the end of the spring */
    weight.set(_p.x, _p.y);

    /* get the different between the anchor point of the spring and the other end */
    ofVec2f newForce = weight - anchor;

    /* Get the length of that vector */
    float d = newForce.length();

    /* Calculate the difference between that and the length of the spring */
    float stretched = d - len;

    /* Normalize the newForce vector */
    newForce.normalize();

    /* Multiply that vector by the amount stretched, also reverse it and scale it */
    newForce *= (-0.01 * stretched);

    /* Return the newForce */
    return newForce;
}

//--------------------------------------------------------------
/* For debugging */
void Spring::draw(){
    ofSetColor(255);
    ofDrawLine(anchor, weight);
}
