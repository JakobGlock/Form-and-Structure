#ifndef BOX_H
#define BOX_H

#include "ofMain.h"

/* This is my box class */

class Box{
public:
    
    /* Methods */
    Box(bool _isMoving);
    void update();
    void draw(ofColor _c);
    bool checkCollision(ofVec3f _pos, float _halfSize);
    void setDirection(int _chooseDir);
    bool outOfScreen();
    ofVec3f randomEdgeStart(float maxRadius);
    bool increaseNeighbours(ofVec3f _nP);

    /* Variables */
    ofVec3f pos, vel;
    float size, halfSize, life;
    bool isMoving;
    float col;
    int numNeighbours;
    float maxEdge;
};

#endif // BOX_H
