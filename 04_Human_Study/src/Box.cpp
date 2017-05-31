#include "Box.h"

//--------------------------------------------------------------
Box::Box(bool _isMoving){

    /* Max distance squares are allowed from the center */
    maxEdge = 400;

    /* get a random starting postiion */
    pos = randomEdgeStart(maxEdge);

    /* Get  a random direction to travel in */
    int rDir = int(ofRandom(0, 28));
    setDirection(rDir);

    /* Choose a new direction if all velocitiesare equal to zero */
    while(vel.x == 0 && vel.y == 0 && vel.z == 0)
    {
        int rDir = int(ofRandom(0, 28));
        setDirection(rDir);
    }

    /* Setting varibales */
    size = 10;
    halfSize = size / 2;
    isMoving = _isMoving;
    col = 0;
    numNeighbours = 0;
}

//--------------------------------------------------------------
void Box::update(){

    /* If moving is true do the update */
    if(isMoving)
    {
        /* Get a random direction to move each frame */
        int rDir = int(ofRandom(0, 28));
        setDirection(rDir);

        /* Choose a new direction if all velocities are equal to zero */
        while(vel.x == 0 && vel.y == 0 && vel.z == 0)
        {
            int rDir = int(ofRandom(0, 28));
            setDirection(rDir);
        }

        /* Update position */
        pos += (vel * size);
    }
}

//--------------------------------------------------------------
void Box::draw(ofColor _c){
    ofSetColor(_c);
    ofDrawBox(pos, size);
}

//--------------------------------------------------------------
bool Box::checkCollision(ofVec3f _pos, float _halfSize){
    //check the X axis
    if(abs(pos.x - _pos.x) < halfSize + _halfSize)
    {
        //check the Y axis
        if(abs(pos.y - _pos.y) < halfSize + _halfSize)
        {
            //check the Z axis
            if(abs(pos.z - _pos.z) < halfSize + _halfSize)
            {
                return true;
            }
        }
    }
    return false;
}

//--------------------------------------------------------------
/* Calculate a direction in 3D space */
void Box::setDirection(int _chooseDir){
    int index = 0;
    for(int x=-1; x<=1; x++){
        for(int y=-1; y<=1; y++){
            for(int z=-1; z<=1; z++){
                index++;
                if(_chooseDir == index)
                {
                    vel.set(x, y, z);
                }
            }
        }
    }
}

//--------------------------------------------------------------
bool Box::outOfScreen(){
    /* Check to see if the particle is out the set range, if it is return true */
    if(pos.x < -maxEdge || pos.x > maxEdge || pos.y < -maxEdge || pos.y > maxEdge || pos.z < -maxEdge || pos.z > maxEdge)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//--------------------------------------------------------------
ofVec3f Box::randomEdgeStart(float maxRadius){

    /* Calculate a random start position around the edge of the defined space */
    int side = int(ofRandom(6));
    if(side == 0)
    {
        ofVec3f p = ofVec3f(-maxRadius, int(ofRandom(-maxRadius, maxRadius)) * size, int(ofRandom(-maxRadius, maxRadius)) * size);
        return p;
    }
    else if(side == 1)
    {
        ofVec3f p = ofVec3f(maxRadius, int(ofRandom(-maxRadius, maxRadius)) * size, int(ofRandom(-maxRadius, maxRadius)) * size);
        return p;
    }
    else if(side == 2)
    {
        ofVec3f p = ofVec3f(int(ofRandom(-maxRadius, maxRadius)) * size, -maxRadius, int(ofRandom(-maxRadius, maxRadius)) * size);
        return p;
    }
    else if(side == 3)
    {
        ofVec3f p = ofVec3f(int(ofRandom(-maxRadius, maxRadius)) * size, maxRadius, int(ofRandom(-maxRadius, maxRadius)) * size);
        return p;
    }
    else if(side == 4)
    {
        ofVec3f p = ofVec3f(int(ofRandom(-maxRadius, maxRadius)) * size, int(ofRandom(-maxRadius, maxRadius)) * size, -maxRadius);
        return p;
    }
    else if(side == 5)
    {
        ofVec3f p = ofVec3f(int(ofRandom(-maxRadius, maxRadius)) * size, int(ofRandom(-maxRadius, maxRadius)) * size, maxRadius);
        return p;
    }

}

//--------------------------------------------------------------
bool Box::increaseNeighbours(ofVec3f _nP){

    /* Count how many neighbours each cube has */

    numNeighbours = 0;

    for(int i=-1; i<=1; i++){
        for(int j=-1; j<=1; j++){
            for(int k=-1; k<=1; k++){
                if(ofVec3f(i*2, j*2, k*2) == _nP)
                {
                    numNeighbours++;
                }
            }
        }
    }

    /* if the number is over 4 return true */
    if(numNeighbours > 4)
    {
        return true;
    }
    else
    {
        return false;
    }

}
