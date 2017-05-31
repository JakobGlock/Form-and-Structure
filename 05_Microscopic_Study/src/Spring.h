#ifndef SPRING_H
#define SPRING_H

#include "ofMain.h"

/* this is my spring class */

class Spring
{
public:
    /* Methods */
    Spring(ofVec2f _a, ofVec2f _p);
    ofVec2f update(ofVec2f _p);
    void draw();

    /* Variables */
    ofVec2f anchor, weight;
    float len;
};

#endif // SPRING_H
