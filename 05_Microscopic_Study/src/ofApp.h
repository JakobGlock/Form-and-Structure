#pragma once

/* Includes */
#include "ofMain.h"
#include "Particle.h"
#include "ofxVoro.h"

class ofApp : public ofBaseApp{

public:

    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);

    /* Vectors */
    vector<Particle *> myParticles;
    vector<ofVboMesh>  cellMeshWireframes;

    /* ofFbo to draw my scene */
    ofFbo scene;

    /* Variables */
    bool mouseDown, saveScreen;
    float time;

};
