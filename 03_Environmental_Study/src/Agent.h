#ifndef AGENT_H
#define AGENT_H

#include "ofMain.h"

class Agent
{
public:
    Agent(float _level, ofVec3f _origin, float _index, ofVec3f _followDir, ofVec2f angles);
    void draw();
    void update(ofVec3f _p);
    void setDirection(int chooseDir);
    ofVec3f getRandomDirection();

    /* Variables */
    int chooseDir, level, maxLevel, maxChild;
    float len, branchOffset, scl, index;
    float phi, theta;
    ofVec3f pos, endPos, dir;

    /* Vector to store children */
    vector<Agent *> child;
};

#endif // AGENT_H
