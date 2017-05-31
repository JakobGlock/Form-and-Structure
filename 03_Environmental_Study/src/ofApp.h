#pragma once

#include "ofMain.h"
#include "Agent.h"

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);

    /* Vector to store objects */
    vector<Agent *> agents;

    /* ofEasyCam */
    ofEasyCam cam;

};
