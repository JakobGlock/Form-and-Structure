#include "Agent.h"

/* Inspired by chapter 8, 'Fractals' in 'Generative Art' by Matt Pearson */

//--------------------------------------------------------------
Agent::Agent(float _level, ofVec3f _origin, float _index, ofVec3f _followDir, ofVec2f angles){

    /* Max level and child */
    maxLevel = 7;
    maxChild = 4;

    /* Store current level and index */
    level = _level;
    index = _index;

    if(level == 1){
        /* If we are on the first level choose a random direction */
        dir = getRandomDirection();
    }
    else
    {
        /* If we are on any other level then follow the last levels direction */
        dir = _followDir;
    }

    /* Set the postion */
    pos.set(_origin);

    /* set the angles */
    phi = angles.x;
    theta = angles.y;

    /* Get a random length for the line */
    len = (1/float(level)) * (25 + ofRandom(25));

    /* Set amount of random offset for the direction and scale of the angle */
    branchOffset = 0.0625;
    scl = 1;

    /* Update the positon */
    update(pos);

    /* Create more, this creates the recursion structure */
    if(level < maxLevel) // this stops it going on forever
    {
        for(int i=0; i<maxChild; i++){
            index++; // Increase the index
            child.push_back(new Agent(level+1, endPos, index, dir, ofVec2f(phi + (PI/6), theta + (TWO_PI/7))));
        }
    }

}

//--------------------------------------------------------------
void Agent::update(ofVec3f _p){

    /* set the positon */
    pos = _p;

    /* Add a random offset to the direction for variation */
    dir.x += ofRandom(-branchOffset, branchOffset);
    dir.y += ofRandom(-branchOffset, branchOffset);
    dir.z += ofRandom(-branchOffset, branchOffset);

    /* Set the postion based on the angles and the index */
    /* This is a spherical rotation, it allows me to plot a point on a sphere in 3D, very useful!!!! */
    dir.x += (sin(theta * index) * cos(phi * index) * scl);
    dir.y += (sin(theta * index) * sin(phi * index) * scl);
    dir.z += (cos(theta * index) * scl);

    /* Set the end positon of the line based on the direction times the length */
    endPos = pos + (len * dir);

}

//--------------------------------------------------------------
void Agent::draw(){

    /* Set the line width, color and finally draw the line */
    ofSetLineWidth(ofMap(level, 1, maxLevel, 3, 0.5));
    ofSetColor(255, 255, 255, ofMap(level, 0, maxLevel, 200, 50));
    ofDrawLine(pos, endPos);

    /* Also draw the children */
    for(int i=0; i<child.size(); i++){
        child[i]->draw();
    }
}

//--------------------------------------------------------------
/* This returns a random 3D vector */
ofVec3f Agent::getRandomDirection(){
    ofVec3f d;
    d.set(ofRandom(-1, 1), ofRandom(-1, 1), ofRandom(-1, 1));
    return d;
}

//--------------------------------------------------------------
void Agent::setDirection(int chooseDir){
    int index = 0;
    for(int x=-1; x<=1; x++){
        for(int y=-1; y<=1; y++){
            for(int z=-1; z<=1; z++){
                index++;
                if(chooseDir == index && index != 0)
                {
                    dir.set(x, y, z);
                }
            }
        }
    }
}
